//
// Created by robin on 01.01.18.
//

#ifndef EMU_JUKEBOX_LABEL_H
#define EMU_JUKEBOX_LABEL_H

#include "Control.h"
#include "imgui/imgui.h"
namespace ebox
{
    enum class LabelType : unsigned
    {
        LabelWithTitle = 0,
        OnlyLabel = 1
    };

    class Label : public Control
    {
        public:
            explicit Label(std::string id);
            Label(const std::string &id, const std::string &label, std::string text,
                  const LabelType &labelType = LabelType::LabelWithTitle);

            void create(const std::string &label, const std::string &text, const LabelType &labelType);

            bool process() override;

            void setValue(const std::string &text);
            void setColor(const sf::Color &text);
            void setHasTitle(bool hasTitle);

            bool hasTitle() const;
            std::string getValue() const;

        protected:
            void assignColors() override;
            std::string m_text;
            bool m_hasTitle = true; //Just like m_hasLabel, but weird name for a label, so calling it title here

            LabelType m_labelType;

            sf::Color m_textColor;
    };
}

#endif //EMU_JUKEBOX_LABEL_H
