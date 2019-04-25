//
// Created by robin on 26.03.19.
//

#include "PreferencesPopup.h"

ebox::PreferencesPopup::PreferencesPopup(const std::string &id, const std::string &title, const std::string &imguiId) : Popup(id, title, imguiId)
{

}

ebox::PreferencesPopup::PreferencesPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id,
                                         const std::string &title, const std::string &imguiId) : Popup(position, size, id, title, imguiId)
{

}

bool ebox::PreferencesPopup::customDraw()
{
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("PreferencesTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("General"))
        {
            drawGeneralTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Themes"))
        {
            drawThemesTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Fonts"))
        {
            drawFontsTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    return true;
}

void ebox::PreferencesPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);
    m_okButton.setOnSameLine(false);
    m_applyButton.setOnSameLine(true);
    m_cancelButton.setOnSameLine(true);

    m_totalButtonWidth = m_okButton.getSize().x + m_applyButton.getSize().x + m_cancelButton.getSize().x + 20;
    m_buttonOffset = (m_size.x / 2) - (m_totalButtonWidth / 2);

    m_themes.addValueRange({"dark", "light", "classic", "modern"});
    m_themes.setValue(0);
    createFonts();
}

void ebox::PreferencesPopup::setIniFile(ebox::IniFile *iniFile)
{
    m_iniFile = iniFile;
}

void ebox::PreferencesPopup::drawGeneralTab()
{
    ImGui::BeginChild("preferences_general_tab", {-1, (float)(m_size.y * 0.85)}, true, 0);
    m_loadLastFileOnStartup.process();
    m_loadLastPlaylistOnStartup.process();
    m_filePreviewsPlayForever.process();
    m_backgroundColor.process();
    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawThemesTab()
{
    ImGui::BeginChild("themes_general_tab", {-1, (float)(m_size.y * 0.85)}, true, 0);
    m_themes.process();
    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawFontsTab()
{
    ImGui::BeginChild("fonts_general_tab", {-1, (float)(m_size.y * 0.85)}, true, 0);
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
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::SmallButton("Set as default"))
    {
        setChosenFontAsDefaultFont();
    }

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
    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawButtonBar()
{
    ImGui::BeginChild("button_offset", {(float) m_buttonOffset, -1}, false, 0);
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("preferences_buttons", {-1, -1}, false, 0);
    if(m_okButton.process())
    {
        updateIniData();
        setOpen(false);
    }
    if(m_applyButton.process())
    {
        updateIniData();
    }
    if(m_cancelButton.process())
        setOpen(false);
    ImGui::EndChild();
}

void ebox::PreferencesPopup::onOpen()
{
    //General
    m_loadLastFileOnStartup.setChecked(m_iniFile->openLastOpenedItemOnStartup());
    m_loadLastPlaylistOnStartup.setChecked(m_iniFile->openLastPlaylistOnStartup());
    m_filePreviewsPlayForever.setChecked(m_iniFile->loopPreviewTracksForever());
    m_backgroundColor.setColor(m_iniFile->getBackgroundColor());
    m_themes.setValue(m_iniFile->getCurrentTheme());
}

void ebox::PreferencesPopup::updateIniData()
{
    //General
    m_iniFile->setOpenLastOpenedItemOnStartup(m_loadLastFileOnStartup.isChecked());
    m_iniFile->setOpenLastPlaylistOnStartup(m_loadLastPlaylistOnStartup.isChecked());
    m_iniFile->setLoopPreviewTracksForever(m_filePreviewsPlayForever.isChecked());
    m_iniFile->setBackgroundColor(m_backgroundColor.getColor());
    m_iniFile->setCurrentTheme(m_themes.getValue());
    m_iniFile->applyTheme();
    m_iniFile->write();
}

void ebox::PreferencesPopup::createFonts()
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
}

void ebox::PreferencesPopup::setCurrentFontByName(const std::string_view &name)
{
    for(int i = 0; i < m_fonts.size(); ++i)
    {
        if(m_fonts[i].getName() == name)
        {
            m_chosenFont = &m_fonts[i];
            setChosenFontAsDefaultFont();
        }
    }
}

ebox::Font *ebox::PreferencesPopup::getFont(const std::string &name)
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

void ebox::PreferencesPopup::createDefaultFont(const std::string &name, float fontSize)
{
    ImFontConfig config;
    config.SizePixels = fontSize;
    m_fonts.emplace_back(name, ImGui::GetIO().Fonts->AddFontDefault(&config));
}

void ebox::PreferencesPopup::createFont(const std::string &name, void *data, size_t size, float fontSize)
{
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    m_fonts.emplace_back(name, ImGui::GetIO().Fonts->AddFontFromMemoryTTF(data, size, fontSize, &config));
}

void ebox::PreferencesPopup::setChosenFontAsDefaultFont()
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


