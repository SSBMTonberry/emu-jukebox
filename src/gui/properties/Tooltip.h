//
// Created by robin on 11.01.18.
//

#ifndef EMU_JUKEBOX_TOOLTIP_H
#define EMU_JUKEBOX_TOOLTIP_H

#include <iostream>
#include <fmt/format.h>
#include <imgui/imgui.h>
#include "imgui/imgui-SFML.h"

namespace ebox
{
    enum class TooltipType : uint
    {
        None = 0,
        Basic = 1
    };

    class Tooltip
    {
        public:
            Tooltip();
            Tooltip(const std::string &text);

            virtual void show();

            void setText(const std::string &text);

            const std::string &getText() const;

        protected:
            std::string m_text = "";
            TooltipType m_type;
    };
}

#endif //EMU_JUKEBOX_TOOLTIP_H
