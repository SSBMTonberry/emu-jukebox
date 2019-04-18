//
// Created by robin on 18.04.19.
//

#include "PlaylistData.h"

ebox::PlaylistData::PlaylistData(const fs::path &path, const std::string &name, int trackNumber, bool loadFile) : m_path {path}, m_trackNumber {trackNumber}, m_name {name}
{
    if(loadFile)
        loadEmuFile();
}

bool ebox::PlaylistData::loadEmuFile()
{
    if(m_emuFileInfo.loadFile(m_path))
    {
        return m_emuFileInfo.loadEmuData();
    }

    return false;
}

int ebox::PlaylistData::getTrackNumber() const
{
    return m_trackNumber;
}

void ebox::PlaylistData::setTrackNumber(int trackNumber)
{
    m_trackNumber = trackNumber;
}

const fs::path &ebox::PlaylistData::getPath() const
{
    return m_path;
}

void ebox::PlaylistData::setPath(const fs::path &path)
{
    m_path = path;
}

const ebox::EmuFileInfo &ebox::PlaylistData::getEmuFileInfo() const
{
    return m_emuFileInfo;
}

const std::string &ebox::PlaylistData::getName() const
{
    return m_name;
}

void ebox::PlaylistData::setName(const std::string &name)
{
    m_name = name;
}

json ebox::PlaylistData::getAsJson() const
{
    json data;
    data["name"] = m_name;
    data["path"] = m_path.u8string();
    data["track_no"] = m_trackNumber;

    return data;
}


