//
// Created by robin on 24.01.18.
//

#ifndef EMU_JUKEBOX_MENUITEMCOLLECTION_H
#define EMU_JUKEBOX_MENUITEMCOLLECTION_H

#include "Control.h"
namespace ebox
{
    class MenuItemCollection : public Control
    {
        public:
            MenuItemCollection(const std::string &id, const std::string &label);

            bool process() override;

            void add(std::unique_ptr<ebox::Control> menuItem);
            void addRef(ebox::Control * menuItem);
            template <typename T>
            T * getMenuItem(const std::string &id);
            template <typename T>
            T * getMenuRefItem(const std::string &id);
        public:
            bool processMenuItems();
            std::vector<std::unique_ptr<ebox::Control>> m_menuItems;
            std::vector<ebox::Control *> m_menuRefItems;

            bool m_isPressed = false;
            bool m_isEnabled = true;
    };
}

template<typename T>
T * ebox::MenuItemCollection::getMenuItem(const std::string &id)
{
    ebox::Control *control = nullptr;
    for(auto & item : m_menuItems)
    {
        if(item->getId().compare(id) == 0)
            control = item.get();
    }

    if(control == nullptr)
        return nullptr;

    T * reference = static_cast<T*>(control);
    return reference;
}

template<typename T>
T * ebox::MenuItemCollection::getMenuRefItem(const std::string &id)
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

#endif //EMU_JUKEBOX_MENUITEMCOLLECTION_H
