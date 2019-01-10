//
// Created by robin on 27.12.17.
//

#ifndef EMU_JUKEBOX_TEXTBOX_H
#define EMU_JUKEBOX_TEXTBOX_H

#include "Control.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

namespace ebox
{
    class Textbox : public Control
    {
        public:
            explicit Textbox(std::string id);
            Textbox(const std::string &id, const std::string &label, size_t size = 0, int imguiId = -1);

            void create(const std::string &label, size_t size = 0, int imguiId = -1);

            bool process() override;

            void setValue(const std::string &text);
            void setColor(const sf::Color &text, const sf::Color &selection, const sf::Color &background, const sf::Color &readOnlyBackground);
            void setHasLabel(bool hasLabel, bool disablePushItemWidth = false);
            void setChanged();

            void setIsMultiline(bool isMultiline);
            void setMultilineTextboxSize(const sf::Vector2i &multilineTextboxSize);

            std::string getValue() const;
            const sf::Vector2i &getMultilineTextboxSize() const;
            bool hasLabel() const;
            bool isChanged() const;
            bool isMultiline() const;

            TextboxFlags getTextboxFlags() const;
            ImGuiInputTextFlags_ getFlagsAsImGuiFlags();
            void setTextboxFlags(const TextboxFlags &textboxFlags);
            void addTextboxFlag(const TextboxFlags &textboxFlag);
            void removeTextboxFlag(const TextboxFlags &textboxFlag);
            bool hasTextboxFlag(const TextboxFlags &textboxFlag);

            std::string getImguiId();

        protected:
            void assignColors() override;

            std::string m_text;
            TextboxFlags m_flags = TextboxFlags::None;
            size_t m_size = 0;
            int m_imguiId = -1;
            bool m_isChanged = false;
            bool m_hasLabel = true;
            bool m_disablePushItemWidth = false;

            //Multiline Textbox
            bool m_isMultiline = false;
            sf::Vector2i m_multilineTextboxSize = {100, 40};

            sf::Color m_textColor;
            sf::Color m_selectionColor;
            sf::Color m_backgroundColor;
            sf::Color m_readOnlyBgColor;
    };
}

#endif //EMU_JUKEBOX_TEXTBOX_H
