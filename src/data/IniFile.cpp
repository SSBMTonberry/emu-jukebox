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
    fs::path path(filepath);
    if(fs::exists(path))
    {
        createByFile(path.u8string());
        parseData();
    }
}

void ebox::IniFile::write()
{
    std::string filepath = fmt::format("{0}/{1}", m_path.u8string(), FILENAME);
    m_data["last_folder"] = m_lastOpenedFolder.u8string();
    m_data["last_file"] = m_lastOpenedFile.u8string();
    m_data["last_item_is_folder"] = m_lastItemIsFolder;
    m_data["current_font"] = m_currentFont;
    m_data["loop_forever"] = m_loopPreviewTracksForever;
    m_data["open_last_item_on_startup"] = m_openLastOpenedItemOnStartup;
    m_data["open_last_playlist_on_startup"] = m_openLastPlaylistOnStartup;
    m_data["bg_color"] = {m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a};
    m_data["volume"] = m_lastVolume;
    m_data["theme"] = m_currentTheme;

    writeToFile(filepath);
}

void ebox::IniFile::setPath(const fs::path &path)
{
    m_path = path;
}

void ebox::IniFile::setLastOpenedFolder(const fs::path &lastOpenedFolder)
{
    m_lastOpenedFolder = lastOpenedFolder;
}

void ebox::IniFile::setCurrentFont(const string &currentFont)
{
    m_currentFont = currentFont;
}

const fs::path &ebox::IniFile::getPath() const
{
    return m_path;
}

const fs::path &ebox::IniFile::getLastOpenedFolder() const
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
    if(m_data.count("last_file") > 0) m_lastOpenedFile = m_data["last_file"].get<string>();
    if(m_data.count("last_item_is_folder") > 0) m_lastItemIsFolder = m_data["last_item_is_folder"].get<bool>();
    if(m_data.count("current_font") > 0) m_currentFont = m_data["current_font"].get<string>();
    if(m_data.count("loop_forever") > 0) m_loopPreviewTracksForever = m_data["loop_forever"].get<bool>();
    if(m_data.count("open_last_item_on_startup") > 0) m_openLastOpenedItemOnStartup = m_data["open_last_item_on_startup"].get<bool>();
    if(m_data.count("open_last_playlist_on_startup") > 0) m_openLastPlaylistOnStartup = m_data["open_last_playlist_on_startup"].get<bool>();
    if(m_data.count("theme") > 0) m_currentTheme = m_data["theme"].get<std::string>();
    if(m_data.count("bg_color") > 0)
    {
        json bg_color = m_data["bg_color"];
        m_backgroundColor = {bg_color[0].get<uint8_t>(), bg_color[1].get<uint8_t>(), bg_color[2].get<uint8_t>(),
                             bg_color[3].get<uint8_t>()};
    }
    if(m_data.count("volume") > 0) m_lastVolume = m_data["volume"].get<float>();
}

bool ebox::IniFile::loopPreviewTracksForever() const
{
    return m_loopPreviewTracksForever;
}

void ebox::IniFile::setLoopPreviewTracksForever(bool loopPreviewTracksForever)
{
    m_loopPreviewTracksForever = loopPreviewTracksForever;
}

bool ebox::IniFile::openLastOpenedItemOnStartup() const
{
    return m_openLastOpenedItemOnStartup;
}

void ebox::IniFile::setOpenLastOpenedItemOnStartup(bool openLastOpenedFolderOnStartup)
{
    m_openLastOpenedItemOnStartup = openLastOpenedFolderOnStartup;
}

const sf::Color &ebox::IniFile::getBackgroundColor() const
{
    return m_backgroundColor;
}

void ebox::IniFile::setBackgroundColor(const sf::Color &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

const fs::path &ebox::IniFile::getLastOpenedFile() const
{
    return m_lastOpenedFile;
}

void ebox::IniFile::setLastOpenedFile(const fs::path &lastOpenedFile)
{
    m_lastOpenedFile = lastOpenedFile;
}

bool ebox::IniFile::isLastItemFolder() const
{
    return m_lastItemIsFolder;
}

void ebox::IniFile::setLastItemIsFolder(bool lastItemIsFolder)
{
    m_lastItemIsFolder = lastItemIsFolder;
}

float ebox::IniFile::getLastVolume() const
{
    return m_lastVolume;
}

void ebox::IniFile::setLastVolume(float lastVolume)
{
    m_lastVolume = lastVolume;
}

bool ebox::IniFile::openLastPlaylistOnStartup() const
{
    return m_openLastPlaylistOnStartup;
}

void ebox::IniFile::setOpenLastPlaylistOnStartup(bool openLastPlaylistOnStartup)
{
    m_openLastPlaylistOnStartup = openLastPlaylistOnStartup;
}

void ebox::IniFile::setPlaylistData(const json &playlistData)
{
    m_data["playlist"] = playlistData;
}

json ebox::IniFile::getPlaylistData()
{
    return m_data["playlist"];
}

const string &ebox::IniFile::getCurrentTheme() const
{
    return m_currentTheme;
}

void ebox::IniFile::setCurrentTheme(const string &currentTheme)
{
    m_currentTheme = currentTheme;
}

void ebox::IniFile::applyTheme()
{
    if(m_currentTheme == "light")
        theme::SetLightTheme();
    else if(m_currentTheme == "classic")
        theme::SetClassicTheme();
    else if(m_currentTheme == "modern")
        theme::SetModernTheme();
    else
        theme::SetDarkTheme();
}

ebox::FontManager *ebox::IniFile::getFontManager()
{
    return &m_fonts;
}
