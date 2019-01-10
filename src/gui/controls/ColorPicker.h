//
// Created by robin on 21.01.18.
//

#ifndef EMU_JUKEBOX_COLORPICKER_H
#define EMU_JUKEBOX_COLORPICKER_H

#include "Control.h"

namespace ebox
{
    class ColorPicker : public Control
    {
        public:
            enum class ColorPickerType
            {
                ColorEdit3 = 0,
                ColorEdit4 = 1,
                ColorPicker3 = 2,
                ColorPicker4 = 3
            };

            ColorPicker(const std::string &id, const std::string &label, const ColorPickerType &pickerType, const sf::Color &defaultColor = sf::Color::White);

            bool process() override;

            void setColor(const sf::Color &color);
            const sf::Color &getColor() const;

        protected:

            bool processByPickerType();
            ImVec4 m_values;
            sf::Color m_color;
            ColorPickerType m_pickerType;
    };
}

#endif //EMU_JUKEBOX_COLORPICKER_H
