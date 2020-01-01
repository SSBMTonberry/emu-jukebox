//
// Created by robin on 01.01.2020.
//

#include "AboutPopup.h"

ebox::AboutPopup::AboutPopup(const std::string &id, const std::string &title) : Popup(id, title)
{

}

ebox::AboutPopup::AboutPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title) : Popup(
        position, size, id, title)
{

}

void ebox::AboutPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);
}

bool ebox::AboutPopup::onDraw()
{
    ImGui::Text("Work in progress!");
    return true;
}

