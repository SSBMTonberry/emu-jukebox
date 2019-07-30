//
// Created by robin on 06.01.18.
//

#include "Theme.h"

ebox::Theme::Theme()
{
    initialize();
}

void ebox::Theme::initialize()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    m_colorMap[Control::Text] = colors[ImGuiCol_Text];
    m_colorMap[Control::TextDisabled] = colors[ImGuiCol_TextDisabled];
    m_colorMap[Control::WindowBg] = colors[ImGuiCol_WindowBg];                              // Background of normal windows
    m_colorMap[Control::ChildBg] = colors[ImGuiCol_ChildBg];                                // Background of child windows
    m_colorMap[Control::PopupBg] = colors[ImGuiCol_PopupBg];                                // Background of popups, menus, tooltips windows
    m_colorMap[Control::Border] = colors[ImGuiCol_Border];
    m_colorMap[Control::BorderShadow] = colors[ImGuiCol_BorderShadow];
    m_colorMap[Control::FrameBg] = colors[ImGuiCol_FrameBg];                                // Background of checkbox, radio button, plot, slider, text input
    m_colorMap[Control::FrameBgHovered] = colors[ImGuiCol_FrameBgHovered];
    m_colorMap[Control::FrameBgActive] = colors[ImGuiCol_FrameBgActive];
    m_colorMap[Control::TitleBg] = colors[ImGuiCol_TitleBg];
    m_colorMap[Control::TitleBgActive] = colors[ImGuiCol_TitleBgActive];
    m_colorMap[Control::TitleBgCollapsed] = colors[ImGuiCol_TitleBgCollapsed];
    m_colorMap[Control::MenuBarBg] = colors[ImGuiCol_MenuBarBg];
    m_colorMap[Control::ScrollbarBg] = colors[ImGuiCol_ScrollbarBg];
    m_colorMap[Control::ScrollbarGrab] = colors[ImGuiCol_ScrollbarGrab];
    m_colorMap[Control::ScrollbarGrabHovered] = colors[ImGuiCol_ScrollbarGrabHovered];
    m_colorMap[Control::ScrollbarGrabActive] = colors[ImGuiCol_ScrollbarGrabActive];
    m_colorMap[Control::CheckMark] = colors[ImGuiCol_CheckMark];
    m_colorMap[Control::SliderGrab] = colors[ImGuiCol_SliderGrab];
    m_colorMap[Control::SliderGrabActive] = colors[ImGuiCol_SliderGrabActive];
    m_colorMap[Control::Button] = colors[ImGuiCol_Button];
    m_colorMap[Control::ButtonHovered] = colors[ImGuiCol_ButtonHovered];
    m_colorMap[Control::ButtonActive] = colors[ImGuiCol_ButtonActive];
    m_colorMap[Control::Header] = colors[ImGuiCol_Header];
    m_colorMap[Control::HeaderHovered] = colors[ImGuiCol_HeaderHovered];
    m_colorMap[Control::HeaderActive] = colors[ImGuiCol_HeaderActive];
    m_colorMap[Control::Separator] = colors[ImGuiCol_Separator];
    m_colorMap[Control::SeparatorHovered] = colors[ImGuiCol_SeparatorHovered];
    m_colorMap[Control::SeparatorActive] = colors[ImGuiCol_SeparatorActive];
    m_colorMap[Control::ResizeGrip] = colors[ImGuiCol_ResizeGrip];
    m_colorMap[Control::ResizeGripHovered] = colors[ImGuiCol_ResizeGripHovered];
    m_colorMap[Control::ResizeGripActive] = colors[ImGuiCol_ResizeGripActive];
    m_colorMap[Control::Tab] = colors[ImGuiCol_Tab];
    m_colorMap[Control::TabHovered] = colors[ImGuiCol_TabHovered];
    m_colorMap[Control::TabActive] = colors[ImGuiCol_TabActive];
    m_colorMap[Control::TabUnfocused] = colors[ImGuiCol_TabUnfocused];
    m_colorMap[Control::TabUnfocusedActive] = colors[ImGuiCol_TabUnfocusedActive];
    m_colorMap[Control::DockingPreview] = colors[ImGuiCol_DockingPreview];
    m_colorMap[Control::DockingEmptyBg] = colors[ImGuiCol_DockingEmptyBg];                  // Background color for empty node (e.g. CentralNode with no window docked into it)
    m_colorMap[Control::PlotLines] = colors[ImGuiCol_PlotLines];
    m_colorMap[Control::PlotLinesHovered] = colors[ImGuiCol_PlotLinesHovered];
    m_colorMap[Control::PlotHistogram] = colors[ImGuiCol_PlotHistogram];
    m_colorMap[Control::PlotHistogramHovered] = colors[ImGuiCol_PlotHistogramHovered];
    m_colorMap[Control::TextSelectedBg] = colors[ImGuiCol_TextSelectedBg];
    m_colorMap[Control::DragDropTarget] = colors[ImGuiCol_DragDropTarget];
    m_colorMap[Control::NavHighlight] = colors[ImGuiCol_NavHighlight];                      // Gamepad/keyboard: current highlighted item
    m_colorMap[Control::NavWindowingHighlight] = colors[ImGuiCol_NavWindowingHighlight];    // Highlight window when using CTRL+TAB
    m_colorMap[Control::NavWindowingDimBg] = colors[ImGuiCol_NavWindowingDimBg];            // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    m_colorMap[Control::ModalWindowDimBg] = colors[ImGuiCol_ModalWindowDimBg];              // Darken/colorize entire screen behind a modal window, when one is active
}

void ebox::Theme::setColor(const Control &control, const sf::Color &color)
{
    m_colorMap[control] = color;
}

/*!
 * Assigns theme to gui
 */
void ebox::Theme::assign()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = m_colorMap[Control::Text];
    colors[ImGuiCol_TextDisabled] = m_colorMap[Control::TextDisabled];
    colors[ImGuiCol_WindowBg] = m_colorMap[Control::WindowBg];                              // Background of normal windows
    colors[ImGuiCol_ChildBg] = m_colorMap[Control::ChildBg];                                // Background of child windows
    colors[ImGuiCol_PopupBg] = m_colorMap[Control::PopupBg];                                // Background of popups, menus, tooltips windows
    colors[ImGuiCol_Border] = m_colorMap[Control::Border];
    colors[ImGuiCol_BorderShadow] = m_colorMap[Control::BorderShadow];
    colors[ImGuiCol_FrameBg] = m_colorMap[Control::FrameBg];                                // Background of checkbox, radio button, plot, slider, text input
    colors[ImGuiCol_FrameBgHovered] = m_colorMap[Control::FrameBgHovered];
    colors[ImGuiCol_FrameBgActive] = m_colorMap[Control::FrameBgActive];
    colors[ImGuiCol_TitleBg] = m_colorMap[Control::TitleBg];
    colors[ImGuiCol_TitleBgActive] = m_colorMap[Control::TitleBgActive];
    colors[ImGuiCol_TitleBgCollapsed] = m_colorMap[Control::TitleBgCollapsed];
    colors[ImGuiCol_MenuBarBg] = m_colorMap[Control::MenuBarBg];
    colors[ImGuiCol_ScrollbarBg] = m_colorMap[Control::ScrollbarBg];
    colors[ImGuiCol_ScrollbarGrab] = m_colorMap[Control::ScrollbarGrab];
    colors[ImGuiCol_ScrollbarGrabHovered] = m_colorMap[Control::ScrollbarGrabHovered];
    colors[ImGuiCol_ScrollbarGrabActive] = m_colorMap[Control::ScrollbarGrabActive];
    colors[ImGuiCol_CheckMark] = m_colorMap[Control::CheckMark];
    colors[ImGuiCol_SliderGrab] = m_colorMap[Control::SliderGrab];
    colors[ImGuiCol_SliderGrabActive] = m_colorMap[Control::SliderGrabActive];
    colors[ImGuiCol_Button] = m_colorMap[Control::Button];
    colors[ImGuiCol_ButtonHovered] = m_colorMap[Control::ButtonHovered];
    colors[ImGuiCol_ButtonActive] = m_colorMap[Control::ButtonActive];
    colors[ImGuiCol_Header] = m_colorMap[Control::Header];
    colors[ImGuiCol_HeaderHovered] = m_colorMap[Control::HeaderHovered];
    colors[ImGuiCol_HeaderActive] = m_colorMap[Control::HeaderActive];
    colors[ImGuiCol_Separator] = m_colorMap[Control::Separator];
    colors[ImGuiCol_SeparatorHovered] = m_colorMap[Control::SeparatorHovered];
    colors[ImGuiCol_SeparatorActive] = m_colorMap[Control::SeparatorActive];
    colors[ImGuiCol_ResizeGrip] = m_colorMap[Control::ResizeGrip];
    colors[ImGuiCol_ResizeGripHovered] = m_colorMap[Control::ResizeGripHovered];
    colors[ImGuiCol_ResizeGripActive] = m_colorMap[Control::ResizeGripActive];
    colors[ImGuiCol_Tab] = m_colorMap[Control::Tab];
    colors[ImGuiCol_TabHovered] = m_colorMap[Control::TabHovered];
    colors[ImGuiCol_TabActive] = m_colorMap[Control::TabActive];
    colors[ImGuiCol_TabUnfocused] = m_colorMap[Control::TabUnfocused];
    colors[ImGuiCol_TabUnfocusedActive] = m_colorMap[Control::TabUnfocusedActive];
    colors[ImGuiCol_DockingPreview] = m_colorMap[Control::DockingPreview];
    colors[ImGuiCol_DockingEmptyBg] = m_colorMap[Control::DockingEmptyBg];                  // Background color for empty node (e.g. CentralNode with no window docked into it)
    colors[ImGuiCol_PlotLines] = m_colorMap[Control::PlotLines];
    colors[ImGuiCol_PlotLinesHovered] = m_colorMap[Control::PlotLinesHovered];
    colors[ImGuiCol_PlotHistogram] = m_colorMap[Control::PlotHistogram];
    colors[ImGuiCol_PlotHistogramHovered] = m_colorMap[Control::PlotHistogramHovered];
    colors[ImGuiCol_TextSelectedBg] = m_colorMap[Control::TextSelectedBg];
    colors[ImGuiCol_DragDropTarget] = m_colorMap[Control::DragDropTarget];
    colors[ImGuiCol_NavHighlight] = m_colorMap[Control::NavHighlight];                      // Gamepad/keyboard: current highlighted item
    colors[ImGuiCol_NavWindowingHighlight] = m_colorMap[Control::NavWindowingHighlight];    // Highlight window when using CTRL+TAB
    colors[ImGuiCol_NavWindowingDimBg] = m_colorMap[Control::NavWindowingDimBg];            // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    colors[ImGuiCol_ModalWindowDimBg] = m_colorMap[Control::ModalWindowDimBg];              // Darken/colorize entire screen behind a modal window, when one is active
}

