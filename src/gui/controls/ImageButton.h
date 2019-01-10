//
// Created by robin on 03.01.18.
//

#ifndef EMU_JUKEBOX_IMAGEBUTTON_H
#define EMU_JUKEBOX_IMAGEBUTTON_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Button.h"
#include <optional>

namespace ebox
{
    class ImageButton : public Button
    {
        public:
            ImageButton(const std::string &id, const std::optional<sf::Vector2<int>> &size = std::nullopt);
            ImageButton(const std::string &id, const void *imageData, const size_t imageDataSize, const std::optional<sf::Vector2<int>> &size = std::nullopt);

            void create(const void *imageData, const size_t imageDataSize);

            bool process() override;

        public:
            sf::Texture m_texture;
            sf::Sprite m_sprite;
            std::optional<sf::Vector2<int>> m_customSize = std::nullopt;
    };
}

#endif //EMU_JUKEBOX_IMAGEBUTTON_H
