//
// Created by robin on 13.01.19.
//

#include "EmuTrackInfo.h"

ebox::EmuTrackInfo::EmuTrackInfo()
{

}

ebox::EmuTrackInfo::EmuTrackInfo(Music_Emu *emu, int trackNumber)
{
    load(m_emu, m_trackNumber);
}

bool ebox::EmuTrackInfo::load(Music_Emu *emu, int trackNumber)
{
    m_emu = emu;
    m_trackNumber = trackNumber;

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
    //m_numberOfTracks = gme_track_count(m_emu);
    m_tempo = 1.f;

    if(m_song.empty())
        m_song = fmt::format("Track {0}", m_trackNumber + 1);

    gme_free_info( info );
    return true;
}

const std::string &ebox::EmuTrackInfo::getSystem() const
{
    return m_system;
}

void ebox::EmuTrackInfo::setSystem(const std::string &system)
{
    m_system = system;
}

const std::string &ebox::EmuTrackInfo::getGame() const
{
    return m_game;
}

void ebox::EmuTrackInfo::setGame(const std::string &game)
{
    m_game = game;
}

const std::string &ebox::EmuTrackInfo::getAuthor() const
{
    return m_author;
}

void ebox::EmuTrackInfo::setAuthor(const std::string &author)
{
    m_author = author;
}

const std::string &ebox::EmuTrackInfo::getCopyright() const
{
    return m_copyright;
}

void ebox::EmuTrackInfo::setCopyright(const std::string &copyright)
{
    m_copyright = copyright;
}

const std::string &ebox::EmuTrackInfo::getComment() const
{
    return m_comment;
}

void ebox::EmuTrackInfo::setComment(const std::string &comment)
{
    m_comment = comment;
}

const std::string &ebox::EmuTrackInfo::getDumper() const
{
    return m_dumper;
}

void ebox::EmuTrackInfo::setDumper(const std::string &dumper)
{
    m_dumper = dumper;
}

int ebox::EmuTrackInfo::getLength() const
{
    return m_length;
}

void ebox::EmuTrackInfo::setLength(int length)
{
    m_length = length;
}

int ebox::EmuTrackInfo::getPlayLength() const
{
    return m_playLength; //(m_tempo != 0) ? m_playLength / m_tempo : m_playLength;
}

void ebox::EmuTrackInfo::setPlayLength(int playLength)
{
    m_playLength = playLength;
}

bool ebox::EmuTrackInfo::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        return true;
    }

    return false;
}

int ebox::EmuTrackInfo::getTrackNumber() const
{
    return m_trackNumber;
}

void ebox::EmuTrackInfo::setTrackNumber(int trackNumber)
{
    m_trackNumber = trackNumber;
}

const std::string &ebox::EmuTrackInfo::getSong() const
{
    return m_song;
}

void ebox::EmuTrackInfo::setSong(const std::string &song)
{
    m_song = song;
}

int ebox::EmuTrackInfo::getIntroLength() const
{
    return m_introLength;
}

void ebox::EmuTrackInfo::setIntroLength(int introLength)
{
    m_introLength = introLength;
}

int ebox::EmuTrackInfo::getLoopLength() const
{
    return m_loopLength;
}

void ebox::EmuTrackInfo::setLoopLength(int loopLength)
{
    m_loopLength = loopLength;
}

//int ebox::EmuTrackInfo::getNumberOfTracks() const
//{
//    return m_numberOfTracks;
//}

float ebox::EmuTrackInfo::getTempo() const
{
    return m_tempo;
}

void ebox::EmuTrackInfo::setTempo(float tempo)
{
    m_tempo = tempo;
}

const std::string &ebox::EmuTrackInfo::getErrorText() const
{
    return m_errorText;
}
