//
// Created by robin on 25.04.19.
//

#include "Font.h"

ebox::Font::Font(std::string name, ImFont *font, float fontSize) : m_name {std::move(name)}, m_imFont {font}, m_fontSize {fontSize}
{

}

void ebox::Font::setName(const std::string &name)
{
    m_name = name;
}

const std::string &ebox::Font::getName() const
{
    return m_name;
}

ImFont *ebox::Font::getImFont() const
{
    return m_imFont;
}

float ebox::Font::getFontSize() const
{
    return m_fontSize;
}

