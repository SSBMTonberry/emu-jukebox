//
// Created by robin on 03.02.19.
//

#include "PlaylistForm.h"

const std::string ebox::PlaylistForm::ID = "PlaylistForm";

ebox::PlaylistForm::PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId) : Form(id, title, imguiId)
{
    initialize();
}

ebox::PlaylistForm::PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                 const std::string &imguiId) : Form(position, size, id, title, imguiId)
{
    initialize();
}

bool ebox::PlaylistForm::customDraw()
{
    return true;
}

void ebox::PlaylistForm::initialize()
{

}

void ebox::PlaylistForm::handleEvents()
{

}

void ebox::PlaylistForm::add(const ebox::EmuFileInfo &fileInfo, int trackNumber)
{
    m_playlist.emplace_back(fileInfo, trackNumber);
}

std::string ebox::PlaylistForm::getId(const std::pair<EmuFileInfo, int> &item)
{
    return fmt::format("{0}_{1}", item.first.getGameName(), item.first.getTracks()[item.second]);
}
