//
// Created by robin on 22.02.18.
//

#ifndef EMU_JUKEBOX_POPUP_H
#define EMU_JUKEBOX_POPUP_H

#include "Form.h"

namespace ebox
{
    /*!
     * A popup works pretty much like a Form, but puts the popup in focus, so you cannot click outside of it.
     */
    class Popup : public Form
    {
        public:
            Popup(std::string id, std::string title, std::string imguiId = "");

            Popup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, std::string id,
                  std::string title, std::string imguiId = "");

            bool draw() override;
            void handleEvents() override;
    };
}

#endif //EMU_JUKEBOX_POPUP_H
