//
// Created by robin on 26.04.19.
//

#include "FontManager.h"

void ebox::FontManager::initialize()
{
    createFonts();
}

bool ebox::FontManager::process()
{
    bool fontChosen = false;
    if (ImGui::BeginCombo("Fonts", m_currentFont))
    {
        for (int i = 0; i < m_fonts.size(); i++)
        {
            bool is_selected = (m_currentFont == nullptr) ? false : (m_fonts[i].getName().compare(m_currentFont) == 0);
            if (ImGui::Selectable(m_fonts[i].getName().c_str(), is_selected))
            {
                m_currentFont = m_fonts[i].getName().c_str();
                m_fontHasBeenChosen = true;
                m_chosenFont = &m_fonts[i];
                fontChosen = true;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    //if (ImGui::SmallButton("Set as default"))
    //{
    //    setChosenFontAsDefaultFont();
    //}

    for(int i = 0; i < 5; ++i)
        ImGui::Spacing();

    if(m_chosenFont != nullptr)
    {
        ImGui::PushFont(m_chosenFont->getImFont());
        ImGui::TextWrapped(PREVIEW_TEXT.c_str());
        ImGui::PopFont();
    }
    else
    {
        ImGui::TextWrapped(PREVIEW_TEXT.c_str());
    }

    for(int i = 0; i < 5; ++i)
        ImGui::Spacing();

    return fontChosen;
}

void ebox::FontManager::createFonts()
{
    m_fonts.clear();
    ImGui::GetIO().Fonts->Clear();

    createDefaultFont("imgui_default", 13);
    createDefaultFont("imgui_default_big", 26);
    createDefaultFont("imgui_16", 16);
    createDefaultFont("imgui_24", 24);
    createDefaultFont("imgui_32", 32);
    createFont("cousine_16", (void *)files_mapper::gui::fonts::_COUSINE_REGULAR_TTF, files_mapper::gui::fonts::_COUSINE_REGULAR_TTF_SIZE, 16);
    createFont("cousine_24", (void *)files_mapper::gui::fonts::_COUSINE_REGULAR_TTF, files_mapper::gui::fonts::_COUSINE_REGULAR_TTF_SIZE, 24);
    createFont("cousine_32", (void *)files_mapper::gui::fonts::_COUSINE_REGULAR_TTF, files_mapper::gui::fonts::_COUSINE_REGULAR_TTF_SIZE, 32);
    createFont("droidsans_16", (void *)files_mapper::gui::fonts::_DROIDSANS_TTF, files_mapper::gui::fonts::_DROIDSANS_TTF_SIZE, 16);
    createFont("droidsans_24", (void *)files_mapper::gui::fonts::_DROIDSANS_TTF, files_mapper::gui::fonts::_DROIDSANS_TTF_SIZE, 24);
    createFont("droidsans_32", (void *)files_mapper::gui::fonts::_DROIDSANS_TTF, files_mapper::gui::fonts::_DROIDSANS_TTF_SIZE, 32);
    createFont("karla_16", (void *)files_mapper::gui::fonts::_KARLA_REGULAR_TTF, files_mapper::gui::fonts::_KARLA_REGULAR_TTF_SIZE, 16);
    createFont("karla_24", (void *)files_mapper::gui::fonts::_KARLA_REGULAR_TTF, files_mapper::gui::fonts::_KARLA_REGULAR_TTF_SIZE, 24);
    createFont("karla_32", (void *)files_mapper::gui::fonts::_KARLA_REGULAR_TTF, files_mapper::gui::fonts::_KARLA_REGULAR_TTF_SIZE, 32);
    createFont("proggyclean_16", (void *)files_mapper::gui::fonts::_PROGGYCLEAN_TTF, files_mapper::gui::fonts::_PROGGYCLEAN_TTF_SIZE, 16);
    createFont("proggyclean_24", (void *)files_mapper::gui::fonts::_PROGGYCLEAN_TTF, files_mapper::gui::fonts::_PROGGYCLEAN_TTF_SIZE, 24);
    createFont("proggyclean_32", (void *)files_mapper::gui::fonts::_PROGGYCLEAN_TTF, files_mapper::gui::fonts::_PROGGYCLEAN_TTF_SIZE, 32);
    createFont("proggytiny_16", (void *)files_mapper::gui::fonts::_PROGGYTINY_TTF, files_mapper::gui::fonts::_PROGGYTINY_TTF_SIZE, 16);
    createFont("proggytiny_24", (void *)files_mapper::gui::fonts::_PROGGYTINY_TTF, files_mapper::gui::fonts::_PROGGYTINY_TTF_SIZE, 24);
    createFont("proggytiny_32", (void *)files_mapper::gui::fonts::_PROGGYTINY_TTF, files_mapper::gui::fonts::_PROGGYTINY_TTF_SIZE, 32);
    createFont("roboto_16", (void *)files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF, files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF_SIZE, 16);
    createFont("roboto_24", (void *)files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF, files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF_SIZE, 24);
    createFont("roboto_32", (void *)files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF, files_mapper::gui::fonts::_ROBOTO_MEDIUM_TTF_SIZE, 32);
    createFont("vera_16", (void *)files_mapper::gui::fonts::_VERA_TTF, files_mapper::gui::fonts::_VERA_TTF_SIZE, 16);
    createFont("vera_24", (void *)files_mapper::gui::fonts::_VERA_TTF, files_mapper::gui::fonts::_VERA_TTF_SIZE, 24);
    createFont("vera_32", (void *)files_mapper::gui::fonts::_VERA_TTF, files_mapper::gui::fonts::_VERA_TTF_SIZE, 32);
    createFont("code_small", (void *)files_mapper::gui::fonts::_PROGGYCLEAN_TTF, files_mapper::gui::fonts::_PROGGYCLEAN_TTF_SIZE, 13);
    createFont("code_big", (void *)files_mapper::gui::fonts::_PROGGYCLEAN_TTF, files_mapper::gui::fonts::_PROGGYCLEAN_TTF_SIZE, 26);

    ImGui::SFML::UpdateFontTexture();
    m_currentFont = m_fonts[0].getName().c_str();
}

void ebox::FontManager::setCurrentFontByName(const std::string_view &name)
{
    for(int i = 0; i < m_fonts.size(); ++i)
    {
        if(m_fonts[i].getName() == name)
        {
            m_chosenFont = &m_fonts[i];
            m_currentFont = m_chosenFont->getName().c_str();
            setChosenFontAsDefaultFont();
        }
    }
}

ebox::Font *ebox::FontManager::getFont(const std::string &name)
{
    for(int i = 0; i < m_fonts.size(); ++i)
    {
        if(m_fonts[i].getName() == name)
        {
            return &m_fonts[i];
        }
    }

    return nullptr;
}

void ebox::FontManager::createDefaultFont(const std::string &name, float fontSize)
{
    ImFontConfig config;
    config.SizePixels = fontSize;
    m_fonts.emplace_back(name, ImGui::GetIO().Fonts->AddFontDefault(&config), fontSize);
}

void ebox::FontManager::createFont(const std::string &name, void *data, size_t size, float fontSize)
{
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    m_fonts.emplace_back(name, ImGui::GetIO().Fonts->AddFontFromMemoryTTF(data, size, fontSize, &config), fontSize);
}


void ebox::FontManager::setChosenFontAsDefaultFont()
{
    ImFontAtlas* atlas = ImGui::GetIO().Fonts;
    for (int i = 0; i < atlas->Fonts.Size; i++)
    {
        ImFont *font = atlas->Fonts[i];
        if(m_chosenFont != nullptr && m_chosenFont->getImFont() == font)
        {
            atlas->Fonts[i] = atlas->Fonts[0];
            atlas->Fonts[0] = font;
        }
    }
}

/*!
 * Gets the font size factor, used for other parts of the program to know how to scale things.
 * If default size, the value is 1. If twice the default size, the value is 2.
 * @return
 */
float ebox::FontManager::getFontSizeFactor()
{
    ImFontAtlas* atlas = ImGui::GetIO().Fonts;
    float scaleFactor = (atlas->Fonts[0]->FontSize / 13);
    float scale = 1 + ((scaleFactor - 1) / 2);
    if(scale < 1)
        scale = 1;

    return scale;
}

ebox::Font *ebox::FontManager::getChosenFont()
{
    return m_chosenFont;
}
