//
// Created by robin on 28.01.18.
//

#ifndef EMU_JUKEBOX_COLORBUTTON_H
#define EMU_JUKEBOX_COLORBUTTON_H

#include "Control.h"

namespace ebox
{
    class ColorButton : public Control
    {
        public:
            ColorButton(const std::string &id, const std::string &label, const sf::Color &color, const sf::Vector2<int> &size = {0,0});

            bool process() override;

            const sf::Color &getColor() const;

            void setColor(const sf::Color &color);

        protected:
            sf::Color m_color;
            sf::Vector2<int> m_size;
            bool m_isClicked = false;
    };
}

#endif //EMU_JUKEBOX_COLORBUTTON_H
