//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFORM_H
#define EMU_JUKEBOX_PLAYLISTFORM_H

#include "../gui/forms/Form.h"
#include "../audio/EmuFileInfo.h"

namespace ebox
{
    class PlaylistForm : public Form
    {
        public:
            PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            void add(const EmuFileInfo &fileInfo, int trackNumber);

            static const std::string ID;

        protected:
            bool customDraw() override;
            std::string getId(const std::pair<EmuFileInfo, int> &item);

        private:
            void initialize();

            std::vector<std::pair<EmuFileInfo, int>> m_playlist;
    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
