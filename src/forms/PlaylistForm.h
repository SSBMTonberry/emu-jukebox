//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFORM_H
#define EMU_JUKEBOX_PLAYLISTFORM_H

#include "../gui/forms/Form.h"
#include "../audio/EmuFileInfo.h"
#include "../gui/controls/TreeList.h"

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
            std::string getId(size_t number, int digits = 6);
        private:
            void initialize();

            void onChosenChildNode(Selectable *sender);
            bool onRightClickedChildNode(Selectable *sender);
            void onDoubleClickChildNode(Selectable *sender);
            void onChosenRightClickContextItems(Selectable* owner, MenuItem *sender);

            std::vector<std::pair<EmuFileInfo, int>> m_playlist;
            TreeList m_filemapping {"playlist_filemapper", "Playlist"};
    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
