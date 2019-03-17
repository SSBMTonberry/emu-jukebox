//
// Created by robin on 17.03.19.
//

#ifndef EMU_JUKEBOX_HOTKEY_H
#define EMU_JUKEBOX_HOTKEY_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "SFML/System.hpp"

namespace ebox
{
    class Hotkey
    {
        public:
            Hotkey() = default;
            Hotkey(const std::initializer_list<sf::Keyboard::Key> &keys);

            void create(const std::initializer_list<sf::Keyboard::Key> &keys);

            bool isPressed();

        protected:
            std::vector<sf::Keyboard::Key> m_keys;
    };
}

#endif //EMU_JUKEBOX_HOTKEY_H
