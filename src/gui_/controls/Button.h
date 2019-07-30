//
// Created by robin on 01.01.18.
//

#ifndef EMU_JUKEBOX_BUTTON_H
#define EMU_JUKEBOX_BUTTON_H

#include "Control.h"
#include <vector>
#include <functional>

namespace ebox
{
    class Button : public Control
    {
        typedef std::function<void(ebox::Button*)> func_btn; //OnPressed(), for instance
        public:
            explicit Button(std::string id);
            Button(const std::string &id, const std::string &label, const sf::Vector2<int> &size);

            void create(const std::string &label, const sf::Vector2<int> &size);

            bool process() override;

            void registerOnPressedCallback(const func_btn &cb);
            void clearCallbacks();

            void setCommand(const std::string &command);
            void setColor(const sf::Color &color, const sf::Color &colorHovered, const sf::Color &colorPressed);
            void setSize(const sf::Vector2<int> &size);

            const std::string &getCommand() const;
            const sf::Vector2<int> &getSize() const;
            bool isPressed() const;

        protected:
            void assignColors() override;

            sf::Color m_color;
            sf::Color m_colorHovered;
            sf::Color m_colorPressed;

            std::string m_command = "";

            std::vector<func_btn> m_callbackOnPressed;

            sf::Vector2<int> m_size;
            bool m_isPressed = false;
    };
}

#endif //EMU_JUKEBOX_BUTTON_H
