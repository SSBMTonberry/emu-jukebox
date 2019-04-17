//
// Created by robin on 25.03.19.
//

#include "IniFile.h"

ebox::IniFile::IniFile() : JsonFile()
{

}

void ebox::IniFile::load()
{
    std::string filepath = fmt::format("{0}/{1}", m_path.u8string(), FILENAME);
    filesystem::path path(filepath);
    if(filesystem::exists(path))
    {
        createByFile(path);
        parseData();
    }
}

void ebox::IniFile::write()
{
    std::string filepath = fmt::format("{0}/{1}", m_path.u8string(), FILENAME);
    m_data["last_folder"] = m_lastOpenedFolder.u8string();
    m_data["current_font"] = m_currentFont;
    m_data["loop_forever"] = m_loopPreviewTracksForever;
    m_data["open_last_folder_on_startup"] = m_openLastOpenedFolderOnStartup;
    m_data["bg_color"] = {m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a};

    writeToFile(filepath);
}

void ebox::IniFile::setPath(const filesystem::path &path)
{
    m_path = path;
}

void ebox::IniFile::setLastOpenedFolder(const filesystem::path &lastOpenedFolder)
{
    m_lastOpenedFolder = lastOpenedFolder;
}

void ebox::IniFile::setCurrentFont(const string &currentFont)
{
    m_currentFont = currentFont;
}

const filesystem::path &ebox::IniFile::getPath() const
{
    return m_path;
}

const filesystem::path &ebox::IniFile::getLastOpenedFolder() const
{
    return m_lastOpenedFolder;
}

const string &ebox::IniFile::getCurrentFont() const
{
    return m_currentFont;
}

void ebox::IniFile::parseData()
{
    if(m_data.count("last_folder") > 0) m_lastOpenedFolder = m_data["last_folder"].get<string>();
    if(m_data.count("current_font") > 0) m_currentFont = m_data["current_font"].get<string>();
    if(m_data.count("loop_forever") > 0) m_currentFont = m_data["loop_forever"].get<bool>();
    if(m_data.count("open_last_folder_on_startup") > 0) m_currentFont = m_data["open_last_folder_on_startup"].get<bool>();
    if(m_data.count("bg_color") > 0)
    {
        json bg_color = m_data["bg_color"];
        m_backgroundColor = {bg_color[0].get<uint8_t>(), bg_color[1].get<uint8_t>(), bg_color[2].get<uint8_t>(),
                             bg_color[3].get<uint8_t>()};
    }
}

bool ebox::IniFile::loopPreviewTracksForever() const
{
    return m_loopPreviewTracksForever;
}

void ebox::IniFile::setLoopPreviewTracksForever(bool loopPreviewTracksForever)
{
    m_loopPreviewTracksForever = loopPreviewTracksForever;
}

bool ebox::IniFile::openLastOpenedFolderOnStartup() const
{
    return m_openLastOpenedFolderOnStartup;
}

void ebox::IniFile::setOpenLastOpenedFolderOnStartup(bool openLastOpenedFolderOnStartup)
{
    m_openLastOpenedFolderOnStartup = openLastOpenedFolderOnStartup;
}

const sf::Color &ebox::IniFile::getBackgroundColor() const
{
    return m_backgroundColor;
}

void ebox::IniFile::setBackgroundColor(const sf::Color &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}


