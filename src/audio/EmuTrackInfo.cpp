//
// Created by robin on 13.01.19.
//

#include "EmuTrack.h"

ebox::EmuTrack::EmuTrack()
{

}

ebox::EmuTrack::EmuTrack(Music_Emu *emu, int trackNumber, long sampleRate)
{
    load(m_emu, m_trackNumber, sampleRate);
}

bool ebox::EmuTrack::load(Music_Emu *emu, int trackNumber, long sampleRate)
{
    m_emu = emu;
    m_trackNumber = trackNumber;
    m_sampleRate = sampleRate;

    gme_info_t* info;
    if(handleError(gme_track_info( m_emu, &info, m_trackNumber)))
        return false;

    m_system = info->system;
    m_game = info->game;
    m_author = info->author;
    m_copyright = info->copyright;
    m_comment = info->comment;
    m_dumper = info->dumper;
    m_song = info->song;
    m_length = info->length;
    m_playLength = info->play_length;
    m_introLength = info->intro_length;
    m_loopLength = info->loop_length;

    gme_free_info( info );

    int song_length = 0;

    m_samples.clear();

    while ((song_length = m_emu->tell()) > -1 && song_length <= m_playLength)
    {
        bool ended = emu->track_ended();
        const long size = 1024; // can be any multiple of 2
        short buf [size];
        // Fill buffer
        if(handleError(emu->play(size, buf)))
            return false;

        for(int i = 0; i < size; ++i)
        {
            m_samples.push_back(buf[i]);
        }
    }

    m_soundBuffer.loadFromSamples(&m_samples[0], m_samples.size(), 2, m_sampleRate);
    m_sound.setBuffer(m_soundBuffer);
    return true;
}

const std::string &ebox::EmuTrack::getSystem() const
{
    return m_system;
}

void ebox::EmuTrack::setSystem(const std::string &system)
{
    m_system = system;
}

const std::string &ebox::EmuTrack::getGame() const
{
    return m_game;
}

void ebox::EmuTrack::setGame(const std::string &game)
{
    m_game = game;
}

const std::string &ebox::EmuTrack::getAuthor() const
{
    return m_author;
}

void ebox::EmuTrack::setAuthor(const std::string &author)
{
    m_author = author;
}

const std::string &ebox::EmuTrack::getCopyright() const
{
    return m_copyright;
}

void ebox::EmuTrack::setCopyright(const std::string &copyright)
{
    m_copyright = copyright;
}

const std::string &ebox::EmuTrack::getComment() const
{
    return m_comment;
}

void ebox::EmuTrack::setComment(const std::string &comment)
{
    m_comment = comment;
}

const std::string &ebox::EmuTrack::getDumper() const
{
    return m_dumper;
}

void ebox::EmuTrack::setDumper(const std::string &dumper)
{
    m_dumper = dumper;
}

int ebox::EmuTrack::getLength() const
{
    return m_length;
}

void ebox::EmuTrack::setLength(int length)
{
    m_length = length;
}

int ebox::EmuTrack::getPlayLength() const
{
    return m_playLength;
}

void ebox::EmuTrack::setPlayLength(int playLength)
{
    m_playLength = playLength;
}

bool ebox::EmuTrack::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        return true;
    }

    return false;
}

int ebox::EmuTrack::getTrackNumber() const
{
    return m_trackNumber;
}

void ebox::EmuTrack::setTrackNumber(int trackNumber)
{
    m_trackNumber = trackNumber;
}

const std::string &ebox::EmuTrack::getSong() const
{
    return m_song;
}

void ebox::EmuTrack::setSong(const std::string &song)
{
    m_song = song;
}

int ebox::EmuTrack::getIntroLength() const
{
    return m_introLength;
}

void ebox::EmuTrack::setIntroLength(int introLength)
{
    m_introLength = introLength;
}

int ebox::EmuTrack::getLoopLength() const
{
    return m_loopLength;
}

void ebox::EmuTrack::setLoopLength(int loopLength)
{
    m_loopLength = loopLength;
}
