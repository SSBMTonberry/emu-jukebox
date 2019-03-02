//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFORM_H
#define EMU_JUKEBOX_PLAYLISTFORM_H

#include "../gui/forms/Form.h"
#include "../audio/EmuFileInfo.h"
#include "../gui/controls/TreeList.h"
#include "../forms/AudioPlayerForm.h"
#include "../misc/Tools.hpp"

namespace ebox
{
    class PlaylistForm : public Form
    {
        public:
            PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            void setPlayer(AudioPlayerForm *player);

            void add(const EmuFileInfo &fileInfo, int trackNumber);
            bool containsId(const std::string &id);

            static const std::string ID;

        protected:
            bool customDraw() override;
            std::string getId(const std::pair<EmuFileInfo, int> &item);
            std::string getId(size_t number, int digits = 6);
        private:
            void initialize();

            int getIndex(const std::string &id);

            void onChosenChildNode(Selectable *sender);
            bool onRightClickedChildNode(Selectable *sender);
            void onDoubleClickChildNode(Selectable *sender);
            void onChosenRightClickContextItems(Selectable* owner, MenuItem *sender);
            void setAsSelectedChildNode(Selectable *child);

            bool loadEmuFile(EmuFileInfo *emuFileInfo, int trackNo);

            bool onNextTrack(AudioPlayerForm *player);
            bool onPreviousTrack(AudioPlayerForm *player);
            bool onTrackEnded(AudioPlayerForm *player, EmuStream *stream);

            void startNextTrack(const std::string &currentId);
            void startPreviousTrack(const std::string &currentId);
            void startRandomTrack(const std::string &currentId);

            AudioPlayerForm *m_player;

            std::vector<std::pair<EmuFileInfo, int>> m_playlist;
            TreeList m_filemapping {"playlist_filemapper", "Playlist"};
    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
