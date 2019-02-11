//
// Created by robin on 03.02.19.
//

#include "FilelistForm.h"

const std::string ebox::FilelistForm::ID = "FilelistForm";

ebox::FilelistForm::FilelistForm(const std::string &id, const std::string &title, const std::string &imguiId) : Form(id, title, imguiId)
{
    initialize();
}

ebox::FilelistForm::FilelistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                 const std::string &imguiId) : Form(position, size, id, title, imguiId)
{
    initialize();
}

bool ebox::FilelistForm::customDraw()
{
    return true;
}

void ebox::FilelistForm::initialize()
{

}

void ebox::FilelistForm::handleEvents()
{

}

void ebox::FilelistForm::loadFile(const fs::path &path)
{
    if(fs::is_regular_file(path))
    {
        m_filemap.insert(path.filename().string(), {path.string()});
        //m_filemap.emplace({path.filename()}, std::make_unique<EmuStream>(path.string()));//m_filemap.insert(path.filename(), {path.string()});
    }
}

void ebox::FilelistForm::loadAllFilesInFolder(const fs::path &folder)
{
    if(fs::is_directory(folder))
    {
        for (const auto &entry : fs::directory_iterator(folder))
        {
            if (fs::is_regular_file(entry.status()))
            {
                m_filemap.insert(entry.path().filename().string(), {entry.path().string()});
            }
        }
    }
}
