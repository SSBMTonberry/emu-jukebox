//
// Created by robin on 21.01.18.
//

#ifndef EMU_JUKEBOX_IMAGE_H
#define EMU_JUKEBOX_IMAGE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Control.h"

namespace ebox
{
    class Image : public Control
    {
        public:
            Image();
            //Image(const Image& img);
            explicit Image(const sf::Texture &texture, const sf::Vector2<int> &size = {-1, -1});
            explicit Image(const std::string &id, bool hasZoomTooltip = false);
            Image(const std::string &id, const void *imageData, size_t imageDataSize, bool hasZoomTooltip = false);

            Image& operator=(const Image &img);

            void create(const void *imageData, size_t imageDataSize);
            void create(const sf::Image &img, const sf::IntRect& rectangle = sf::IntRect());
            void create(const sf::Texture &texture, const sf::Vector2<int> &size = {-1, -1});
            void create(const sf::Sprite &sprite, const sf::IntRect& rectangle = sf::IntRect());
            void create(unsigned int width, unsigned int height, const sf::Color &color);
            bool process() override;

            void setColor(const sf::Color &color);
            void setSpriteScale(const sf::Vector2f &scale);
            void setRotation(float angle);
            void setZoomTooltipScaleRatio(float zoomTooltipScaleRatio);
            void setHasZoomTooltip(bool hasZoomTooltip);
            void setScale(const sf::Vector2f &scale);

            bool hasZoomTooltip() const;

            float getZoomTooltipScaleRatio() const;
            const sf::Vector2f &getSpriteScale() const;
            const sf::Vector2f &getScale() const;
            const sf::Texture &getTexture() const;
            const sf::Sprite &getSprite() const;
            const sf::Vector2<int> &getSize() const;
            sf::Sprite *getSpritePtr();


        protected:
            Image& copy(const Image &s);

            void showZoomTooltip();

            sf::Texture m_texture;
            sf::Sprite m_sprite;
            sf::Vector2<int> m_size;
            sf::Vector2f m_scale = {1.f, 1.f};

            bool m_hasZoomTooltip = false;
            float m_zoomTooltipScaleRatio = 4.f;
    };
}

#endif //EMU_JUKEBOX_IMAGE_H
