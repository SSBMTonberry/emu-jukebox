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
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Themes"))
        {
            drawThemesTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Fonts"))
        {
            drawFontsTab();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void ebox::PreferencesPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);
}

void ebox::PreferencesPopup::setIniFile(ebox::IniFile *iniFile)
{
    m_iniFile = iniFile;
}

void ebox::PreferencesPopup::drawGeneralTab()
{
    ImGui::Text("General settings coming soon!");
}

void ebox::PreferencesPopup::drawThemesTab()
{
    ImGui::Text("Themes coming soon!");
}

void ebox::PreferencesPopup::drawFontsTab()
{
    ImGui::Text("Fonts coming soon!");
}


