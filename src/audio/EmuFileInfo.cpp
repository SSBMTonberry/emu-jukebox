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
    bool isValid = false;
    m_path = path;
    if(fs::is_regular_file(m_path))
    {
        m_path = path;
        m_filename = m_path.filename().string();
        isValid = isValidFileType();
    }
    m_isValid = isValid;
    return m_isValid;
}

/*!
 * Checks if the path contains a valid file type
 * @return if the file is a valid emu file
 */
bool ebox::EmuFileInfo::isValidFileType()
{
    gme_type_t file_type;

    if(handleError( gme_identify_file( m_filename.c_str(), &file_type ) )) return false;
    if ( !file_type ) return !handleError( "Unsupported music type" );

    return true;
}

/*!
 *
 * @return true if emu data is loaded. false if it already has been loaded.
 */
bool ebox::EmuFileInfo::loadEmuDataIfNotLoaded()
{
    if(!m_emuDataLoaded)
    {
        m_emuDataLoaded = true;
        return loadEmuData();
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
    m_extension = file_type->extension_;

    if ( !emu )
    {
        freeEmu(emu);
        return !handleError( "Out of memory" );
    }

    if(handleError( emu->set_sample_rate( 44100 )))
    {
        freeEmu(emu);
        return false;
    }

    if(handleError( emu->load_file(m_path.string().c_str())))
    {
        freeEmu(emu);
        return false;
    }

    m_numberOfTracks = gme_track_count(emu);

    //Load tracks
    for(int i = 0; i < m_numberOfTracks; ++i)
    {
        gme_info_t* info;
        if(handleError(gme_track_info( emu, &info, i)))
        {
            freeEmu(emu);
            gme_free_info( info );
            return false;
        }

        std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
        std::string song = info->song;
        m_gameName = info->game;

        if(song.empty())
            m_tracks.emplace_back(fmt::format("Track {0}", i + 1));
        else
            m_tracks.emplace_back(fmt::format("{0} - {1}", trackNumber, info->song));

        gme_free_info( info );
    }
    m_displayName = fmt::format("{0} ({1})", m_gameName, m_extension);

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

const std::filesystem::path &ebox::EmuFileInfo::getPath() const
{
    return m_path;
}

const std::string &ebox::EmuFileInfo::getFilename() const
{
    return m_filename;
}

const std::string &ebox::EmuFileInfo::getGameName() const
{
    return m_gameName;
}

const std::string &ebox::EmuFileInfo::getExtension() const
{
    return m_extension;
}

int ebox::EmuFileInfo::getNumberOfTracks() const
{
    return m_numberOfTracks;
}

const std::string &ebox::EmuFileInfo::getDisplayName() const
{
    return m_displayName;
}

const std::vector<std::string> &ebox::EmuFileInfo::getTracks() const
{
    return m_tracks;
}

bool ebox::EmuFileInfo::isValid() const
{
    return m_isValid;
}

void ebox::EmuFileInfo::freeEmu(Music_Emu *emu)
{
    if(emu != nullptr)
        delete emu;
}

bool ebox::EmuFileInfo::exists()
{
    return fs::exists(m_path);
}

const std::string &ebox::EmuFileInfo::getId() const
{
    return m_id;
}

void ebox::EmuFileInfo::setId(const std::string &id)
{
    m_id = id;
}
