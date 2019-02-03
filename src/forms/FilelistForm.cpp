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