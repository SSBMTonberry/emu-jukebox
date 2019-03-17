//
// Created by robin on 17.03.19.
//

#include "Hotkey.h"

ebox::Hotkey::Hotkey(const std::initializer_list<sf::Keyboard::Key> &keys)
{
    create(keys);
}

void ebox::Hotkey::create(const std::initializer_list<sf::Keyboard::Key> &keys)
{
    m_keys.clear();
    for(auto const key : keys)
    {
        m_keys.emplace_back(key);
    }
}

bool ebox::Hotkey::isPressed()
{
    bool isPressed = true;
    for(auto const key : m_keys)
    {
        if(!sf::Keyboard::isKeyPressed(key))
            isPressed = false;
    }

    return isPressed;
}
