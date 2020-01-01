//
// Created by robin on 01.01.2020.
//

#ifndef EMU_JUKEBOX_ABOUTPOPUP_H
#define EMU_JUKEBOX_ABOUTPOPUP_H

#include "pmgui.h"

namespace ebox
{
    class AboutPopup : public pmgui::Popup
    {
        public:
            AboutPopup(const std::string &id, const std::string &title);
            AboutPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size,
                       const std::string &id, const std::string &title);

            void initialize(const sf::Vector2<int> &size);

        protected:
            bool onDraw() override;
    };
}

#endif //EMU_JUKEBOX_ABOUTPOPUP_H
