//
// Created by robin on 18.04.19.
//

#include "PlaylistFile.h"

ebox::PlaylistFile::PlaylistFile(const fs::path &path) : JsonFile(), m_path {path}
{

}

void ebox::PlaylistFile::load()
{
    if(fs::exists(m_path) && fs::is_regular_file(m_path))
    {
        createByFile(m_path.u8string());
        parseData();
    }
}

void ebox::PlaylistFile::write()
{
    m_data["name"] = m_name;
    std::vector<json> files;
    for(auto const & data : m_playlistData)
    {
        files.push_back(data.getAsJson());
    }
    m_data["files"] = files;
    writeToFile(m_path.u8string());
}

void ebox::PlaylistFile::parseData()
{
    if(m_data.count("name") > 0) m_name = m_data["name"].get<std::string>();
    if(m_data.count("files") > 0)
    {
        json files = m_data["files"];
        for(auto const & file : files)
        {
            PlaylistData data { fs::path(file["path"].get<std::string>()), file["name"].get<std::string>(), file["track_no"].get<int>(), false };
            if(data.loadEmuFile())
            {
                m_playlistData.push_back(data);
            }
        }
    }
}

void ebox::PlaylistFile::clearPlaylist()
{
    m_playlistData.clear();
}

void ebox::PlaylistFile::add(const fs::path &path, const std::string &name, int trackNumber)
{
    m_playlistData.emplace_back(path, name, trackNumber, false);
}

const std::string &ebox::PlaylistFile::getName() const
{
    return m_name;
}

void ebox::PlaylistFile::setName(const std::string &name)
{
    m_name = name;
}

const std::vector<ebox::PlaylistData> &ebox::PlaylistFile::getPlaylistData() const
{
    return m_playlistData;
}
