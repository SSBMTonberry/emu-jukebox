//
// Created by robin on 25.04.19.
//

#ifndef EMU_JUKEBOX_FONT_H
#define EMU_JUKEBOX_FONT_H

#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace ebox
{
    class Font
    {
        public:
            Font(std::string name, ImFont *font, float fontSize);

            void setName(const std::string &name);

            const std::string &getName() const;
            float  getFontSize() const;
            ImFont *getImFont() const;

        protected:
            std::string m_name;
            float m_fontSize;
            ImFont *m_imFont;
    };
}

#endif //EMU_JUKEBOX_FONT_H
