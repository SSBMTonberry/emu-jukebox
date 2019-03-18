//
// Created by robin on 06.01.19.
//


#include "EmuStream.h"

ebox::EmuStream::EmuStream()
{

}

ebox::EmuStream::EmuStream(const ebox::EmuStream &other)
{
    SystemLog::get()->addDebug(fmt::format("EmuStream - Copy-constructor called"));
    copy(other);
}

ebox::EmuStream::EmuStream(ebox::EmuStream &&other)
{
    SystemLog::get()->addDebug(fmt::format("EmuStream - Move-constructor called"));
    move(std::move(other));
}

void ebox::EmuStream::move(ebox::EmuStream &&other)
{
    if(other.getLoadMode() == Mode::File)
    {
        initializeFile(other.getFilename(), other.getTrack(), other.getChannelCount(), other.getEmuSampleRate(), true);
    }
    else if(other.getLoadMode() == Mode::Memory)
    {
        initializeMemory(other.getData(), other.getDataSize(), other.getTrack(), other.getChannelCount(), other.getEmuSampleRate(), true);
    }
}

void ebox::EmuStream::copy(const EmuStream &other)
{
    if(other.getLoadMode() == Mode::File)
    {
        initializeFile(other.getFilename(), other.getTrack(), other.getChannelCount(), other.getEmuSampleRate(), true);
    }
    else if(other.getLoadMode() == Mode::Memory)
    {
        initializeMemory(other.getData(), other.getDataSize(), other.getTrack(), other.getChannelCount(), other.getEmuSampleRate(), true);
    }
}

ebox::EmuStream &ebox::EmuStream::operator=(const ebox::EmuStream &other)
{
    SystemLog::get()->addDebug(fmt::format("EmuStream - operator= called"));
    copy(other);
    return *this;
}


/*!
 *
 * @param channelCount 1 = mono, 2 = stereo.
 * @param sampleRate Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
   also get worse quality on the sound.
 */
ebox::EmuStream::EmuStream(const std::string &filename, int track, uint32_t channelCount, uint32_t sampleRate)
{
    initializeFile(filename, track, channelCount, sampleRate);
}


ebox::EmuStream::EmuStream(void *data, size_t size, int track, uint32_t channelCount, uint32_t sampleRate)
{
    initializeMemory(data, size, track, channelCount, sampleRate);
}

void ebox::EmuStream::initializeFile(const std::string &filename, int track, uint32_t channelCount, uint32_t sampleRate, bool printAsDebug)
{
    m_loadMode = Mode::File;
    m_channelCount = channelCount;
    m_sampleRate = sampleRate;
    m_filename = filename;
    m_track = track;

    // Resize the internal buffer so that it can contain 1/7 second of audio samples
    m_samples.resize((m_sampleRate * m_channelCount) / 7);

    SoundStream::initialize(m_channelCount, m_sampleRate);
    m_isValid = initializeEmu();
    if(m_isValid)
    {
        if(printAsDebug)
            SystemLog::get()->addDebug(fmt::format("EmuStream ({0}) - Successfully loaded!", m_filename));
        else
            SystemLog::get()->addSuccess(fmt::format("EmuStream ({0}) - Successfully loaded!", m_filename));
    }
}

void ebox::EmuStream::initializeMemory(void *data, size_t size, int track, uint32_t channelCount, uint32_t sampleRate, bool printAsDebug)
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
    m_isValid = initializeEmu();
    if(m_isValid)
    {
        if(printAsDebug)
            SystemLog::get()->addDebug(fmt::format("EmuStream ({0}) - Successfully loaded!", m_filename));
        else
            SystemLog::get()->addSuccess(fmt::format("EmuStream ({0}) - Successfully loaded!", m_filename));
    }
}

ebox::EmuStream::~EmuStream()
{
    // We must stop before destroying the file
    //stop();
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
    m_timePlayed = m_emu->tell();// * m_info.getTempo();

    for (auto const& observer : m_sampleObservers) {
        observer(&m_samples[0], m_samples.size());
    }

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
    if(m_emu != nullptr)// && this->getStatus() == Status::Playing)
    {
        m_emu->seek(timeOffset.asMilliseconds());
    }
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
        if(handleError( gme_identify_file( m_filename.c_str(), &file_type ) )) return false;
    }
    else if(m_loadMode == Mode::Memory)
    {
        std::string header = gme_identify_header(m_data);
        file_type = gme_identify_extension(header.c_str());
    }

    if ( !file_type )
        return !handleError( "Unsupported music type" );

    // Create emulator and set sample rate
    m_emu = file_type->new_emu();

    if ( !m_emu )
        return !handleError( "Out of memory" );

    if(handleError( m_emu->set_sample_rate( m_sampleRate ))) return false;

    if(m_loadMode == Mode::File)
    {
        if(handleError(m_emu->load_file(m_filename.c_str()))) return false;
    }
    else if(m_loadMode == Mode::Memory)
    {
        if(handleError(m_emu->load_mem(m_data, m_dataSize))) return false;
    }

    m_numberOfTracks = gme_track_count(m_emu);

    if(handleError(m_emu->start_track( m_track ))) return false;

    //Load tracks
    for(int i = 0; i < m_numberOfTracks; ++i)
    {
        m_tracks.emplace_back();
        bool success = m_tracks[i].load(m_emu, i);
        if(!success)
            SystemLog::get()->addError(fmt::format("Error loading track: {0}: {1}", i, m_tracks[i].getErrorText()));
    }

    float tempo = m_tracks[m_track].getTempo();
    setTempo(tempo);
    m_emu->ignore_silence(); //This makes sure the music doesn't stop when all channels are muted.

    const char **voice_names = m_emu->voice_names();
    int i = 0;
    m_voices.clear();
    while (*voice_names)
    {
        //int hotkeyPos = (i < 9) ? static_cast<int>(sf::Keyboard::Key::Num1) + i : -1;
        //sf::Keyboard::Key hotkey = (i == 9) ? sf::Keyboard::Key::Num0 : (sf::Keyboard::Key) hotkeyPos;
        int voices = m_emu->voice_count();
        if (i < voices)
        {
            auto item = m_voices.emplace_back(m_emu, i, *voice_names++, false); //, hotkey);
            m_voices[m_voices.size()-1].setTooltip(fmt::format("Hotkey: <Alt>+{0}", i+1));
            ++i;
        }
        else
            break;
    }

    m_equalizer.initialize(m_emu);
    this->pause();

    return true;
}

bool ebox::EmuStream::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        SystemLog::get()->addError(fmt::format("EmuStream ({0}) - {1}", m_filename, m_errorText));
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

void ebox::EmuStream::setTempo(float tempo)
{
    if(m_emu != nullptr)
    {
        m_tracks[m_track].setTempo(tempo);
        m_emu->set_tempo(tempo);
    }
}

void ebox::EmuStream::setTrack(int track)
{
    m_track = track;
    if(m_emu != nullptr)
    {
        handleError(m_emu->start_track(m_track));
    }
}

void ebox::EmuStream::nextTrack()
{
    m_track = ((m_track + 1) > m_numberOfTracks - 1) ? 0 : m_track + 1;
    setTrack(m_track);
}

void ebox::EmuStream::previousTrack()
{
    m_track = ((m_track-1 < 0) && m_numberOfTracks > 0) ? m_numberOfTracks - 1 : m_track - 1;
    setTrack(m_track);
}

std::vector<ebox::Voice> *ebox::EmuStream::getVoices()
{
    return &m_voices;
}

size_t ebox::EmuStream::getNumberOfVoices()
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

const ebox::EmuTrackInfo &ebox::EmuStream::getInfoFromCurrentTrack() const
{
    return (m_numberOfTracks > 0) ? m_tracks[m_track] : m_emptyTrack;
}

ebox::EmuEqualizer *ebox::EmuStream::getEqualizer()
{
    return &m_equalizer;
}

int ebox::EmuStream::getTimePlayed() const
{

    return m_timePlayed; //(m_info.getTempo() == 0) ? m_timePlayed : m_timePlayed * m_info.getTempo();
}

int *ebox::EmuStream::getTimePlayedPtr()
{
    return &m_timePlayed;
}

ebox::EmuStream::Mode ebox::EmuStream::getLoadMode() const
{
    return m_loadMode;
}

const std::string &ebox::EmuStream::getFilename() const
{
    return m_filename;
}

int ebox::EmuStream::getTrack() const
{
    return m_track;
}

uint32_t ebox::EmuStream::getChannelCount() const
{
    return m_channelCount;
}

uint32_t ebox::EmuStream::getEmuSampleRate() const
{
    return m_sampleRate;
}

void *ebox::EmuStream::getData() const
{
    return m_data;
}

size_t ebox::EmuStream::getDataSize() const
{
    return m_dataSize;
}


void ebox::EmuStream::registerSampleObserver(func_sampleObserver callback) {
    m_sampleObservers.emplace_back(std::move(callback));
}

bool ebox::EmuStream::isValid() const
{
    return m_isValid;
}

int ebox::EmuStream::getNumberOfTracks() const
{
    return m_numberOfTracks;
}

const std::vector<ebox::EmuTrackInfo> &ebox::EmuStream::getTracks() const
{
    return m_tracks;
}

void ebox::EmuStream::setId(const std::string &id)
{
    m_id = id;
}

const std::string &ebox::EmuStream::getId() const
{
    return m_id;
}
