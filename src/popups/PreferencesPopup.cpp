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
    ImGui::Text("Fonts coming soon!");
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


