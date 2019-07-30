//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFORM_H
#define EMU_JUKEBOX_PLAYLISTFORM_H

//#include "../gui/forms/Form.h"
//#include "../gui/controls/TreeList.h"
#include "pmgui.h"
#include "../audio/EmuFileInfo.h"
#include "../forms/AudioPlayerForm.h"
#include "../misc/Tools.hpp"
#include <random>
#include "../managers/Hotkeys.h"
#include "../data/PlaylistFile.h"
#include "../data/IniFile.h"

namespace ebox
{
    class PlaylistForm : public pmgui::Form
    {
        typedef Hotkeys::PlaylistHotkey key;
        public:
            PlaylistForm(const std::string &id, const std::string &title);

            PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title);

            void handleEvents() override;

            void setPlayer(AudioPlayerForm *player);
            void setIniFile(IniFile *iniFile);
            void createByJson(json playlist);
            void createByFile(const PlaylistFile &file);

            void add(const EmuFileInfo &fileInfo, int trackNumber);
            bool containsId(const std::string &id);

            json getAsJson();

            static const std::string ID;

        protected:
            bool onDraw() override;
            std::string getId(const std::pair<EmuFileInfo, int> &item);
            std::string getId(size_t number, int digits = 6);
        private:
            void initialize();
            void processPlaylistButtonPanel();
            void processHotkeys();

            int getIndex(const std::string &id);
            std::pair<EmuFileInfo, int> *getPlaylistItemById(const std::string &id);

            void onFocusedChildNode(pmgui::Selectable *sender);
            void onChosenChildNode(pmgui::Selectable *sender);
            bool onRightClickedChildNode(pmgui::Selectable *sender);
            void onDoubleClickChildNode(pmgui::Selectable *sender);
            void onChosenRightClickContextItems(pmgui::Selectable* owner, pmgui::MenuItem *sender);

            void setAsSelectedChildNode(pmgui::Selectable *child);
            void setAsSelectedChildNode(const std::string &id);
            void setAsSelectedChildNode(int index);
            void selectNextItem();
            void selectPreviousItem();

            pmgui::Selectable *getSelected();
            EmuFileInfo * getEmuFileInfo(const std::string &id);
            int getSelectedIndex();
            int getNumberOfSelectedItems();

            void moveItemUp();
            void moveItemDown();
            void removeAllItems();
            void removeItem(const std::string &id);
            void removeSelectedItems();

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
            IniFile *m_iniFile;
            bool m_hasShuffle = false;
            bool m_hasRepeat = false;
            bool m_hasMultiSelect = false;

            std::vector<std::pair<EmuFileInfo, int>> m_playlist;
            pmgui::TreeList m_filemapping {"playlist_filemapper", "Playlist"};

            pmgui::ImageButton m_shuffleButton {"shuffle_button", files_mapper::gui::ebox::_SHUFFLE_16_PNG, files_mapper::gui::ebox::_SHUFFLE_16_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_repeatButton {"repeat_button", files_mapper::gui::ebox::_REPEAT_16_PNG, files_mapper::gui::ebox::_REPEAT_16_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_moveUpButton {"move_up_button", files_mapper::gui::actions::_MOVEUP_PNG, files_mapper::gui::actions::_MOVEUP_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_moveDownButton {"move_down_button", files_mapper::gui::actions::_MOVEDOWN_PNG, files_mapper::gui::actions::_MOVEDOWN_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_removeAllButton {"remove_all_button", files_mapper::gui::debugger::_KILLPROCESS_PNG, files_mapper::gui::debugger::_KILLPROCESS_PNG_SIZE, sf::Vector2i(30, 30)};

    };
}

#endif //EMU_JUKEBOX_PLAYLISTFORM_H
