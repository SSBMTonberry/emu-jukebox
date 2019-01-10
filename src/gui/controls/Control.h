//
// Created by robin on 27.12.17.
//

#ifndef EMU_JUKEBOX_CONTROL_H
#define EMU_JUKEBOX_CONTROL_H

#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/time.h>
#include <imgui/imgui.h>
#include "../properties/Tooltip.h"
#include "imgui/imgui-SFML.h"
#include "../../misc/Enums.hpp"
#include <optional>
#include <vector>

namespace ebox
{
    enum class ControlType : uint
    {
        Unassigned = 0,
        Textbox = 1,
        Label = 2,
        Button = 3,
        ImageButton = 4,
        Combobox = 5,
        RadioSection = 6,
        Checkbox = 7,
        CheckboxSection = 8,
        Selectable = 9,
        Listbox = 10,
        TreeNode = 11,
        SliderInt = 12,
        SliderFloat = 13,
        Image = 14,
        ColorPicker = 15,
        MenuBar = 16,
        MenuItemCollection = 17,
        MenuItem = 18,
        DragInt = 19,
        DragFloat = 20,
        ColorButton = 21,
        Group = 22,
        Child = 23,
        ProgressBar = 24,
        DataTable = 25,
        Table = 26,
        TreeList = 27,
        ColoredText = 28,
        InputInt = 29,
        InputFloat = 30
    };

    class Control
    {
        public:
            Control();

            explicit Control(std::string id);
            Control(const std::string &id, const std::string &label);

            /*!
             * Primarily does the drawing, but due to the way ImGui works, it does more things as well.
             * @return true if control is marked as visible, false if it is supposed to be hidden
             */
            virtual bool process();

            void setId(const std::string &id);

            void setLabel(const std::string &label);
            void setUseDefaultColor(bool useDefaultColor);
            void setOnSameLine(bool putOnSameLine);
            void setTooltip(const std::optional<Tooltip> &tooltip);
            void setIsVisible(bool isVisible);

            void createBasicTooltip(const std::string &text);

            bool isOnSameLine() const;
            bool isUsingDefaultColor() const;
            bool isVisible() const;

            const std::optional<Tooltip> &getTooltip() const;
            const std::string &getId() const;
            const std::string &getLabel() const;
            ControlType getType() const;

        protected:
            virtual void assignColors();

            bool m_isVisible = true;

            std::string m_id;
            std::string m_label;
            std::optional<ebox::Tooltip> m_tooltip = std::nullopt;
            ControlType m_type = ControlType::Unassigned;

            bool m_colorIsChanged = false;
            bool m_useDefaultColor = false; //Forces default color set by the theme
            bool m_putOnSameLine = false;
    };
}

#endif //EMU_JUKEBOX_CONTROL_H
