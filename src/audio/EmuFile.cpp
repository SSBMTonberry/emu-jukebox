//
// Created by robin on 20.04.19.
//

#include "EmuFile.h"

ebox::EmuFile::EmuFile()
{

}

ebox::EmuFile::EmuFile(const std::string &filename, int track, uint32_t channelCount, uint32_t sampleRate)
{
    initialize(filename, track, channelCount, sampleRate);
}

ebox::EmuFile::~EmuFile()
{
    if(m_emu != nullptr)
    {
        delete m_emu;
        m_emu = nullptr;
    }
}

bool ebox::EmuFile::initialize(const std::string &filename, int track, uint32_t channelCount, uint32_t sampleRate, bool printAsDebug)
{
    m_channelCount = channelCount;
    m_sampleRate = sampleRate;
    m_filename = filename;
    m_track = track;

    //m_samples.resize((m_sampleRate * m_channelCount) / 7);

    m_isValid = initializeEmu();
    if(m_isValid)
    {
        if(printAsDebug)
            SystemLog::get()->addDebug(fmt::format("EmuFile ({0}) - Successfully loaded!", m_filename));
        else
            SystemLog::get()->addSuccess(fmt::format("EmuFile ({0}) - Successfully loaded!", m_filename));
        return true;
    }

    return false;
}

bool ebox::EmuFile::initializeEmu(float tempo)
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

    if(handleError( gme_identify_file( m_filename.c_str(), &file_type ) )) return false;


    if ( !file_type )
        return !handleError( "Unsupported music type" );

    // Create emulator and set sample rate
    m_emu = file_type->new_emu();

    if ( !m_emu )
        return !handleError( "Out of memory" );

    if(handleError( m_emu->set_sample_rate( m_sampleRate ))) return false;

    if(handleError(m_emu->load_file(m_filename.c_str()))) return false;

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

    tempo = (tempo < 0) ? m_tracks[m_track].getTempo() : tempo;
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
            //m_voices[m_voices.size()-1].setTooltip(fmt::format("Hotkey: <Alt>+{0}", i+1));
            ++i;
        }
        else
            break;
    }

    m_equalizer.initialize(m_emu);

    return true;
}

bool ebox::EmuFile::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        SystemLog::get()->addError(fmt::format("EmuFile ({0}) - {1}", m_filename, m_errorText));
        return true;
    }

    return false;
}

void ebox::EmuFile::muteChannel(int channelNo, bool mute)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].setMuted(mute);
        m_emu->mute_voice(channelNo, mute);
    }
}

void ebox::EmuFile::toggleMuteChannel(int channelNo)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].toggleMute();
        m_emu->mute_voice(channelNo, m_voices[channelNo].isMuted());
    }
}

void ebox::EmuFile::unmuteAllChannels()
{
    m_emu->mute_voices(0);
    for(auto const &channel : m_voices)
    {
        muteChannel(channel.getChannelNo(), false);
    }
}

void ebox::EmuFile::setTempo(float tempo)
{
    if(m_emu != nullptr)
    {
        m_tracks[m_track].setTempo(tempo);
        m_emu->set_tempo(tempo);
    }
}

void ebox::EmuFile::setTrack(int track)
{
    m_track = track;
    if(m_emu != nullptr)
    {
        handleError(m_emu->start_track(m_track));
    }
}

size_t ebox::EmuFile::getNumberOfVoices()
{
    return m_voices.size();
}

std::vector<ebox::Voice> *ebox::EmuFile::getVoices()
{
    return &m_voices;
}

ebox::EmuTrackInfo *ebox::EmuFile::getInfoFromCurrentTrack()
{
    return (m_numberOfTracks > 0) ? &m_tracks[m_track] : &m_emptyTrack;
}

const std::vector<ebox::EmuTrackInfo> &ebox::EmuFile::getTracks() const
{
    return m_tracks;;
}

ebox::EmuEqualizer *ebox::EmuFile::getEqualizer()
{
    return &m_equalizer;
}

const std::string &ebox::EmuFile::getFilename() const
{
    return m_filename;
}

int ebox::EmuFile::getTrack() const
{
    return m_track;
}

uint32_t ebox::EmuFile::getChannelCount() const
{
    return m_channelCount;
}

uint32_t ebox::EmuFile::getEmuSampleRate() const
{
    return m_sampleRate;
}

int ebox::EmuFile::getNumberOfTracks() const
{
    return m_numberOfTracks;
}

bool ebox::EmuFile::isValid() const
{
    return m_isValid;
}

bool ebox::EmuFile::createSamplesAndFillBuffer(uint64_t startPos, float tempo)
{
    m_samples.clear();
    m_emu->seek(startPos);
    int i = 1;
    size_t sampleSize = m_sampleRate * 2;
    m_samples.resize(sampleSize);

    EmuTrackInfo *info = getInfoFromCurrentTrack();
    long songLength = 0;
    while ((songLength = m_emu->tell()) > -1 && songLength <= (info->getPlayLength() / tempo))
    {
        m_samples.resize(i * sampleSize);
        m_emu->play(sampleSize, &m_samples[0]+(sampleSize*(i-1)));
        ++i;
    }

    m_buffer.loadFromSamples(&m_samples[0], m_samples.size(), m_channelCount, m_sampleRate);

    return true;
}

bool ebox::EmuFile::exportToSoundFile(const std::string &path)
{
    return m_buffer.saveToFile(path);
}

void ebox::EmuFile::reload(uint32_t sampleRate, float tempo)
{
    std::vector<bool> voicesMuted;
    for(auto &voice : m_voices)
        voicesMuted.push_back(voice.isMuted());

    m_sampleRate = sampleRate;
    initializeEmu(tempo);

    for(int i = 0; i < m_voices.size(); ++i)
    {
        m_voices[i].setMuted(voicesMuted[i]);
        m_voices[i].getCheckbox()->setChecked(!voicesMuted[i]);
    }
}

Music_Emu *ebox::EmuFile::getEmu()
{
    return m_emu;
}
