//
// Created by robin on 03.01.18.
//

#include "ImageButton.h"

ebox::ImageButton::ImageButton(const std::string &id, const std::optional<sf::Vector2<int>> &size)
        : Button(id, "", {16, 16}), m_customSize {size}
{
    m_type = ControlType::ImageButton;
}

ebox::ImageButton::ImageButton(const std::string &id, const void *imageData, const size_t imageDataSize,
                              const std::optional<sf::Vector2<int>> &size) : Button(id, "", {16, 16}),
                                                                             m_customSize {size}
{
    m_type = ControlType::ImageButton;
    create(imageData, imageDataSize);
}

bool ebox::ImageButton::process()
{
    if(Control::process())
    {

        m_isPressed = false;
        bool popColors = false;
        bool toReturn = false;
        if (m_colorIsChanged && !m_useDefaultColor)
        {
            assignColors();
            popColors = true;
        }

        if (ImGui::ImageButton(m_sprite))
        {
            m_isPressed = true;
            toReturn = true;
        }

        if (popColors && !m_useDefaultColor)
        {
            ImGui::PopStyleColor(3);
        }
        return toReturn;
    }

    return false;
}

void ebox::ImageButton::create(const void *imageData, const size_t imageDataSize)
{
    if(m_customSize.has_value())
        m_texture.loadFromMemory(imageData, imageDataSize, {{0,0}, {m_customSize.value().x, m_customSize.value().y}});
    else
        m_texture.loadFromMemory(imageData, imageDataSize);

    m_sprite.setTexture(m_texture);//*m_texture
    m_sprite.setOrigin((float)m_texture.getSize().x / 2, (float)m_texture.getSize().y / 2);
    m_size = {(int)m_texture.getSize().x, (int)m_texture.getSize().y};
}

sf::Sprite *ebox::ImageButton::getImage()
{
    return &m_sprite;
}

