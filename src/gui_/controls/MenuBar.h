//
// Created by robin on 24.01.18.
//

#ifndef EMU_JUKEBOX_MENUBAR_H
#define EMU_JUKEBOX_MENUBAR_H

#include "Control.h"

namespace ebox
{
    class MenuBar : public Control
    {
        public:
            MenuBar(const std::string &id, bool isMainMenu);

            bool process() override;

            void add(std::unique_ptr<ebox::Control> menuItem);
            void addRef(ebox::Control * menuItem);
            template <typename T>
            T * getMenuItem(const std::string &id);
            template <typename T>
            T * getMenuRefItem(const std::string &id);

            const sf::Vector2<int> &getMenuSize() const;

        protected:
            bool processMenuItems();
            std::vector<std::unique_ptr<ebox::Control>> m_menuItems;
            std::vector<ebox::Control *> m_menuRefItems;

            sf::Vector2<int> m_menuSize = {0,0};

            bool m_isPressed = false;
            bool m_isMainMenu = false;
    };
}

template<typename T>
T * ebox::MenuBar::getMenuItem(const std::string &id)
{
    ebox::Control *control = nullptr;
    for(auto & item : m_menuItems)
    {
        if(item->getId() == id)
            control = item.get();
    }

    if(control == nullptr)
        return nullptr;

    T * reference = static_cast<T*>(control);
    return reference;
}

template<typename T>
T * ebox::MenuBar::getMenuRefItem(const std::string &id)
{
    ebox::Control *control = nullptr;
    for(auto item : m_menuRefItems)
    {
        if(item->getId() == id)
            control = item;
    }

    if(control == nullptr)
        return nullptr;

    T * reference = static_cast<T*>(control);
    return reference;
}

#endif //EMU_JUKEBOX_MENUBAR_H
