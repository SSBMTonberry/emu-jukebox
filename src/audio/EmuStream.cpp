//
// Created by robin on 06.01.19.
//


#include "EmuStream.h"

ebox::EmuStream::EmuStream()
{

}

/*!
 *
 * @param channelCount 1 = mono, 2 = stereo.
 * @param sampleRate Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
   also get worse quality on the sound.
 */
ebox::EmuStream::EmuStream(const std::string &filename, int track, uint channelCount, uint sampleRate)
{
    initializeFile(filename, track, channelCount, sampleRate);
}


ebox::EmuStream::EmuStream(void *data, size_t size, int track, uint channelCount, uint sampleRate)
{
    initializeMemory(data, size, track, channelCount, sampleRate);
}

void ebox::EmuStream::initializeFile(const std::string &filename, int track, uint channelCount, uint sampleRate)
{
    m_loadMode = Mode::File;
    m_channelCount = channelCount;
    m_sampleRate = sampleRate;
    m_filename = filename;
    m_track = track;

    // Resize the internal buffer so that it can contain 1/7 second of audio samples
    m_samples.resize((m_sampleRate * m_channelCount) / 7);

    SoundStream::initialize(m_channelCount, m_sampleRate);
    initializeEmu();
}

void ebox::EmuStream::initializeMemory(void *data, size_t size, int track, uint channelCount, uint sampleRate)
{
    m_loadMode = Mode::Memory;
    m_channelCount = channelCount;
    m_sampleRate = sampleRate;
    m_data = data;
    m_dataSize = size;
    m_track = track;

    // Resize the internal buffer so that it can contain 1/7 second of audio samples
    m_samples.resize((m_sampleRate * m_channelCount) / 7);

    SoundStream::initialize(m_channelCount, m_sampleRate);
    initializeEmu();
}

ebox::EmuStream::~EmuStream()
{
    // We must stop before destroying the file
    stop();
    if(m_emu != nullptr)
    {
        delete m_emu;
        m_emu = nullptr;
    }

}


/*!
 * @brief Request a new chunk of audio samples from the stream source
 *
 * This function fills the chunk from the next samples
 * to read from the audio file.
 *
 * @param data Chunk of data to fill
 *
 * @return true to continue playback, false to stop
 */
bool ebox::EmuStream::onGetData(sf::SoundStream::Chunk &data)
{
    sf::Lock lock(m_mutex);

    m_emu->play(m_samples.size(), &m_samples[0]);
    m_timePlayed = m_emu->tell();
    // Fill the chunk parameters
    data.samples     = &m_samples[0];
    data.sampleCount = m_samples.size(); //static_cast<std::size_t>(m_file.read(&m_samples[0], m_samples.size()));

    if (!data.sampleCount)
    {
        // Check if we have reached the end of the audio file
        return data.sampleCount == m_samples.size();
    }

    return data.sampleCount == m_samples.size();
}

/*!
 * @brief Change the current playing position in the stream source
 * @param timeOffset New playing position, from the beginning of the music
 */

void ebox::EmuStream::onSeek(sf::Time timeOffset)
{
    sf::Lock lock(m_mutex);

    //sf::Uint64 sampleOffset = static_cast<sf::Uint64>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    //sampleOffset -= sampleOffset % getChannelCount();
    //m_loopCurrent = sampleOffset;
    if(m_emu != nullptr)// && timeOffset.asMilliseconds() > 0)
        m_emu->seek(timeOffset.asMilliseconds());
}

bool ebox::EmuStream::initializeEmu()
{
    if(m_emu != nullptr)
    {
        delete m_emu;
        m_emu = nullptr;
    }


    // Determine file type
    gme_type_t file_type;
    //std::string header = gme_identify_header(files_mapper::_SUPER_MARIO_BROS_NSFE); //
    //gme_type_t file_type = gme_identify_extension(header.c_str());

    if(m_loadMode == Mode::File)
    {
        handleError( gme_identify_file( m_filename.c_str(), &file_type ) );
    }
    else if(m_loadMode == Mode::Memory)
    {
        std::string header = gme_identify_header(m_data);
        file_type = gme_identify_extension(header.c_str());
    }

    if ( !file_type )
        handleError( "Unsupported music type" );

    // Create emulator and set sample rate
    m_emu = file_type->new_emu();

    if ( !m_emu )
        handleError( "Out of memory" );
    handleError( m_emu->set_sample_rate( m_sampleRate ) );

    if(m_loadMode == Mode::File)
    {
        handleError(m_emu->load_file(m_filename.c_str()));
    }
    else if(m_loadMode == Mode::Memory)
    {
        handleError(m_emu->load_mem(m_data, m_dataSize));
    }

    handleError( m_emu->start_track( m_track ) );
    m_info.load(m_emu, m_track);

    m_emu->ignore_silence(); //This makes sure the music doesn't stop when all channels are muted.

    const char **voice_names = m_emu->voice_names();
    int i = 0;
    m_voices.clear();
    while (*voice_names)
    {
        int hotkeyPos = (i < 9) ? static_cast<int>(sf::Keyboard::Key::Num1) + i : -1;

        sf::Keyboard::Key hotkey = (i == 9) ? sf::Keyboard::Key::Num0 : (sf::Keyboard::Key) hotkeyPos;
        int voices = m_emu->voice_count();
        if (i < voices)
        {
            m_voices.emplace_back(m_emu, i, *voice_names++, false, hotkey);
            ++i;
        }
        else
            break;
    }

    m_equalizer.initialize(m_emu);
}

bool ebox::EmuStream::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        return true;
    }

    return false;
}

void ebox::EmuStream::toggleMuteChannelByHotkey(sf::Keyboard::Key key)
{
    for(auto const &voice : m_voices)
    {
        //if(voice.hotkey == key)
        //{
        //    toggleMuteChannel(voice.channelNo);
        //}
    }
}

void ebox::EmuStream::muteChannel(int channelNo, bool mute)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].setMuted(mute);
        m_emu->mute_voice(channelNo, mute);
    }
}

void ebox::EmuStream::toggleMuteChannel(int channelNo)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].toggleMute();
        m_emu->mute_voice(channelNo, m_voices[channelNo].isMuted());
    }
}

void ebox::EmuStream::setTrack(int track)
{
    m_track = track;
    if(m_emu != nullptr)
    {
        handleError(m_emu->start_track(m_track));
        m_info.load(m_emu, m_track);
    }
}

void ebox::EmuStream::nextTrack()
{
    m_track = ((m_track + 1) > m_info.getNumberOfTracks() - 1) ? 0 : m_track + 1;
    setTrack(m_track);
}

void ebox::EmuStream::previousTrack()
{
    m_track = ((m_track-1 < 0) && m_info.getNumberOfTracks() > 0) ? m_info.getNumberOfTracks() - 1 : m_track - 1;
    setTrack(m_track);
}

std::vector<ebox::Voice> *ebox::EmuStream::getVoices()
{
    return &m_voices;
}

size_t ebox::EmuStream::getNumberOfChannels()
{
    return m_voices.size();
}

void ebox::EmuStream::unmuteAllChannels()
{
    m_emu->mute_voices(0);
    for(auto const &channel : m_voices)
    {
        muteChannel(channel.getChannelNo(), false);
    }
}

const ebox::EmuTrackInfo &ebox::EmuStream::getInfo() const
{
    return m_info;
}

ebox::EmuEqualizer *ebox::EmuStream::getEqualizer()
{
    return &m_equalizer;
}

int ebox::EmuStream::getTimePlayed() const
{
    return m_timePlayed;
}

int *ebox::EmuStream::getTimePlayedPtr()
{
    return &m_timePlayed;
}
