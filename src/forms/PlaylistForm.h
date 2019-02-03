//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFORM_H
#define EMU_JUKEBOX_PLAYLISTFORM_H

#include "../gui/forms/Form.h"

namespace ebox
{
    class PlaylistForm : public Form
    {
        public:
            PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();
    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
