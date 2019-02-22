//
// Created by robin on 22.02.19.
//

#include "EmuFileInfo.h"

ebox::EmuFileInfo::EmuFileInfo()
{

}

ebox::EmuFileInfo::EmuFileInfo(const fs::path &path, bool runLoadEmu)
{
    if(loadFile(path) && runLoadEmu)
    {
        loadEmuData();
    }
}

bool ebox::EmuFileInfo::loadFile(const fs::path &path)
{
    if(fs::is_regular_file(m_path))
    {
        m_path = path;
        m_filename = m_path.filename().string();
        return true;
    }

    return false;
}

bool ebox::EmuFileInfo::loadEmuData()
{
    m_tracks.clear();
    Music_Emu *emu;

    gme_type_t file_type;

    if(handleError( gme_identify_file( m_filename.c_str(), &file_type ) )) return false;
    if ( !file_type ) return !handleError( "Unsupported music type" );

    emu = file_type->new_emu();

    if ( !emu ) return !handleError( "Out of memory" );

    if(handleError( emu->set_sample_rate( 44100 ))) return false;
    if(handleError( emu->load_file(m_path.string().c_str()))) return false;

    m_numberOfTracks = gme_track_count(emu);

    //Load tracks
    for(int i = 0; i < m_numberOfTracks; ++i)
    {
        gme_info_t* info;
        if(handleError(gme_track_info( emu, &info, i)))
            return false;

        std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
        std::string song = info->song;


        if(song.empty())
            m_tracks.emplace_back(fmt::format("Track {0}", i + 1));
        else
            m_tracks.emplace_back(fmt::format("{0} - {1}", trackNumber, info->song));

        gme_free_info( info );
    }

    if(emu != nullptr)
        delete emu;

    return true;
}

bool ebox::EmuFileInfo::handleError(const char *errorText)
{
    if(errorText)
    {
        SystemLog::get()->addError(fmt::format("EmuStream ({0}) - {1}", m_filename, errorText));
        return true;
    }

    return false;
}

