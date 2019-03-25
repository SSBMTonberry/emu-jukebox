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
}
