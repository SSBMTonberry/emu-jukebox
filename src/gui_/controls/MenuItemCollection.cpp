//
// Created by robin on 24.01.18.
//

#include "MenuItemCollection.h"

ebox::MenuItemCollection::MenuItemCollection(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::MenuItemCollection;
}

bool ebox::MenuItemCollection::process()
{
    m_isPressed = false;
    if(Control::process())
    {
        if(ImGui::BeginMenu(m_label.c_str(), m_isEnabled))
        {
            m_isPressed = true;
            processMenuItems();
            ImGui::EndMenu();
        }
    }

    return m_isPressed;
}

bool ebox::MenuItemCollection::processMenuItems()
{
    bool anyItemActive = false;
    for(const auto &item : m_menuItems)
    {
        if(item->process())
        {
            anyItemActive = true;
        }
    }
    for(const auto &item : m_menuRefItems)
    {
        if(item->process())
        {
            anyItemActive = true;
        }
    }
    /*for(auto const & [pos, obj] : m_menuItems)
    {
        if(obj->process())
        {
            anyItemActive = true;
        }
    }*/

    return anyItemActive;
}

void ebox::MenuItemCollection::add(std::unique_ptr<ebox::Control> menuItem)
{
    m_menuItems.push_back(std::move(menuItem));
}

void ebox::MenuItemCollection::addRef(ebox::Control *menuItem)
{
    m_menuRefItems.push_back(menuItem);
}
