//
// Created by robin on 24.04.19.
//

#ifndef EMU_JUKEBOX_EMUTHEMES_HPP
#define EMU_JUKEBOX_EMUTHEMES_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ebox::theme
{
    inline void SetDarkTheme();
    inline void SetLightTheme();
    inline void SetClassicTheme();
    inline void SetModernTheme();

    void SetDarkTheme()
    {
        ImGui::StyleColorsDark();
        ImGuiStyle * style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;
        colors[ImGuiCol_PlotLines]              = sf::Color(32, 113, 160, 255); //ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotLinesHovered]       = sf::Color(32, 113, 160, 255);
        colors[ImGuiCol_PlotHistogram]          = sf::Color(32, 113, 160, 255); //ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotHistogramHovered]   = sf::Color(32, 113, 160, 255);
    }

    void SetLightTheme()
    {
        ImGui::StyleColorsLight();
    }

    void SetClassicTheme()
    {
        ImGui::StyleColorsClassic();
    }

    void SetModernTheme()
    {
        ImGuiStyle * style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;

        colors[ImGuiCol_Text]                   = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        colors[ImGuiCol_Border]                 = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = sf::Color(163, 17, 88, 255); //ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = sf::Color(99, 8, 52, 255); //ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
        colors[ImGuiCol_TitleBgActive]          = sf::Color(163, 17, 88, 255); //ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = sf::Color(163, 17, 88, 255); //ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_ButtonHovered]          = sf::Color(163, 17, 88, 255); //ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_Header]                 = sf::Color(99, 8, 52, 255); //ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        colors[ImGuiCol_HeaderHovered]          = sf::Color(163, 17, 88, 255); //ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_HeaderActive]           = sf::Color(32, 113, 160, 255); //ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_Separator]              = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_SeparatorHovered]       = sf::Color(163, 17, 88, 255); //ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        colors[ImGuiCol_Tab]                    = ImLerp(colors[ImGuiCol_Header],       colors[ImGuiCol_TitleBgActive], 0.80f);
        colors[ImGuiCol_TabHovered]             = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_TabActive]              = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
        colors[ImGuiCol_TabUnfocused]           = ImLerp(colors[ImGuiCol_Tab],          colors[ImGuiCol_TitleBg], 0.80f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImLerp(colors[ImGuiCol_TabActive],    colors[ImGuiCol_TitleBg], 0.40f);
        colors[ImGuiCol_DockingPreview]         = {colors[ImGuiCol_HeaderActive].x, colors[ImGuiCol_HeaderActive].y, colors[ImGuiCol_HeaderActive].z, colors[ImGuiCol_HeaderActive].w * 0.7f};
        colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_PlotLines]              = sf::Color(163, 17, 88, 255); //ImVec4(0.25f, 1.00f, 0.00f, 1.00f); //ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotLinesHovered]       = sf::Color(163, 17, 88, 255); //ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = sf::Color(163, 17, 88, 255); //ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotHistogramHovered]   = sf::Color(163, 17, 88, 255); //ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = sf::Color(163, 17, 88, 255); //ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.50f, 0.50f, 0.50f, 0.63f); //ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.50f, 0.50f, 0.50f, 0.63f); //ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.50f, 0.50f, 0.50f, 0.63f); //ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
    }
}

#endif //EMU_JUKEBOX_EMUTHEMES_HPP
