//
// Created by robin on 25.03.19.
//

#include "IniFile.h"

ebox::IniFile::IniFile() : JsonFile()
{
    #if APPLE
    m_path = getMacApplicationFolder();
    #else
    m_path = fs::current_path();
    #endif
}

void ebox::IniFile::load()
{
    std::string filepath = fmt::format("{0}/{1}", m_path.u8string(), FILENAME);
    fs::path path(filepath);
    ebox::SystemLog::get()->addInfo(fmt::format("Searching for ebox.ini at: {0}", path.u8string()));
    if(fs::exists(path))
    {
        createByFile(path.u8string());
        parseData();
        ebox::SystemLog::get()->addSuccess("Settings successfully loaded from ebox.ini! ");
    }
    else
        ebox::SystemLog::get()->addInfo("Could not find ebox.ini");
}

void ebox::IniFile::write()
{
    Font *font = m_fonts.getChosenFont();
    m_currentFont = (font == nullptr) ? "" : font->getName();

    std::string filepath = fmt::format("{0}/{1}", m_path.u8string(), FILENAME);
    m_data["last_folder"] = tools::string::Wstring2String(m_lastOpenedFolder.wstring());
    m_data["last_file"] = tools::string::Wstring2String(m_lastOpenedFile.wstring());
    m_data["last_item_is_folder"] = m_lastItemIsFolder;
    m_data["current_font"] = m_currentFont;
    m_data["loop_forever"] = m_loopPreviewTracksForever;
    m_data["open_last_item_on_startup"] = m_openLastOpenedItemOnStartup;
    m_data["open_last_playlist_on_startup"] = m_openLastPlaylistOnStartup;
    m_data["bg_color"] = {m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a};
    m_data["volume"] = m_lastVolume;
    m_data["theme"] = m_currentTheme;
    m_data["no_of_repeats"] = m_numberOfRepeats;

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

void ebox::IniFile::setCurrentFont(const std::string &currentFont)
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

const std::string &ebox::IniFile::getCurrentFont() const
{
    return m_currentFont;
}

void ebox::IniFile::parseData()
{
    if(m_data.count("last_folder") > 0) m_lastOpenedFolder = fs::path(tools::string::String2Wstring(m_data["last_folder"].get<std::string>()));
    if(m_data.count("last_file") > 0) m_lastOpenedFile = fs::path(tools::string::String2Wstring(m_data["last_file"].get<std::string>()));
    if(m_data.count("last_item_is_folder") > 0) m_lastItemIsFolder = m_data["last_item_is_folder"].get<bool>();
    if(m_data.count("current_font") > 0) m_currentFont = m_data["current_font"].get<std::string>();
    if(m_data.count("loop_forever") > 0) m_loopPreviewTracksForever = m_data["loop_forever"].get<bool>();
    if(m_data.count("open_last_item_on_startup") > 0) m_openLastOpenedItemOnStartup = m_data["open_last_item_on_startup"].get<bool>();
    if(m_data.count("open_last_playlist_on_startup") > 0) m_openLastPlaylistOnStartup = m_data["open_last_playlist_on_startup"].get<bool>();
    if(m_data.count("theme") > 0) m_currentTheme = m_data["theme"].get<std::string>();
    if(m_data.count("no_of_repeats") > 0) m_numberOfRepeats = m_data["no_of_repeats"].get<int>();

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

const std::string &ebox::IniFile::getCurrentTheme() const
{
    return m_currentTheme;
}

void ebox::IniFile::setCurrentTheme(const std::string &currentTheme)
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

int ebox::IniFile::getNumberOfRepeats() const
{
    return m_numberOfRepeats;
}

void ebox::IniFile::setNumberOfRepeats(int numberOfRepeats)
{
    m_numberOfRepeats = numberOfRepeats;
}

void ebox::IniFile::reset()
{
    m_currentFont = "imgui_default";
    m_fonts.setCurrentFontByName(m_currentFont);
    m_loopPreviewTracksForever = true;
    m_openLastOpenedItemOnStartup = false;
    m_openLastPlaylistOnStartup = true;
    m_numberOfRepeats = 0;
    m_backgroundColor = {35, 65, 90, 255};
    setCurrentTheme("dark");
    applyTheme();
}

#if APPLE
fs::path ebox::IniFile::getMacApplicationFolder()
{
    char buf [PATH_MAX];
    uint32_t bufsize = PATH_MAX;
    if(!_NSGetExecutablePath(buf, &bufsize))
        puts(buf);

    fs::path path {buf};
    //Using parent_path several times to get to the part of the .app file where we are allowed to
    //produce a file. It is still inside the .app-file, which makes it possible to move preferences
    //with the file itself.
    return path.parent_path().parent_path().parent_path();
}
#endif