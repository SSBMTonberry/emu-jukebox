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
#include <random>
#include "../managers/Hotkeys.h"
#include "../data/JsonFile.h"

namespace ebox
{
    class PlaylistForm : public Form
    {
        typedef Hotkeys::PlaylistHotkey key;
        public:
            PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            void setPlayer(AudioPlayerForm *player);
            void createByJson(json playlist);

            void add(const EmuFileInfo &fileInfo, int trackNumber);
            bool containsId(const std::string &id);

            json getAsJson();

            static const std::string ID;

        protected:
            bool customDraw() override;
            std::string getId(const std::pair<EmuFileInfo, int> &item);
            std::string getId(size_t number, int digits = 6);
        private:
            void initialize();
            void processPlaylistButtonPanel();
            void processHotkeys();

            int getIndex(const std::string &id);

            void onFocusedChildNode(Selectable *sender);
            void onChosenChildNode(Selectable *sender);
            bool onRightClickedChildNode(Selectable *sender);
            void onDoubleClickChildNode(Selectable *sender);
            void onChosenRightClickContextItems(Selectable* owner, MenuItem *sender);

            void setAsSelectedChildNode(Selectable *child);
            void setAsSelectedChildNode(const std::string &id);
            void setAsSelectedChildNode(int index);
            void selectNextItem();
            void selectPreviousItem();

            Selectable *getSelected();
            EmuFileInfo * getEmuFileInfo(const std::string &id);
            int getSelectedIndex();

            void moveItemUp();
            void moveItemDown();
            void removeAllItems();
            void removeItem(const std::string &id);

            bool loadEmuFile(EmuFileInfo *emuFileInfo, int trackNo);

            bool onNextTrack(AudioPlayerForm *player);
            bool onPreviousTrack(AudioPlayerForm *player);
            bool onTrackEnded(AudioPlayerForm *player, EmuStream *stream);

            void startNextTrack(const std::string &currentId);
            void startPreviousTrack(const std::string &currentId);
            void startTrack(const std::string &id);
            void startRandomTrack(const std::string &currentId);

            void setShuffle(bool shuffle);
            void setRepeat(bool repeat);

            AudioPlayerForm *m_player;
            bool m_hasShuffle = false;
            bool m_hasRepeat = false;

            std::vector<std::pair<EmuFileInfo, int>> m_playlist;
            TreeList m_filemapping {"playlist_filemapper", "Playlist"};

            ebox::ImageButton m_shuffleButton {"shuffle_button", files_mapper::gui::ebox::_SHUFFLE_16_PNG, files_mapper::gui::ebox::_SHUFFLE_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_repeatButton {"repeat_button", files_mapper::gui::ebox::_REPEAT_16_PNG, files_mapper::gui::ebox::_REPEAT_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_moveUpButton {"move_up_button", files_mapper::gui::actions::_MOVEUP_PNG, files_mapper::gui::actions::_MOVEUP_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_moveDownButton {"move_down_button", files_mapper::gui::actions::_MOVEDOWN_PNG, files_mapper::gui::actions::_MOVEDOWN_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_removeAllButton {"remove_all_button", files_mapper::gui::debugger::_KILLPROCESS_PNG, files_mapper::gui::debugger::_KILLPROCESS_PNG_SIZE, sf::Vector2i(30, 30)};

    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
