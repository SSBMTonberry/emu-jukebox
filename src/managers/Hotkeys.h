//
// Created by robin on 17.03.19.
//

#ifndef EMU_JUKEBOX_HOTKEYMANAGER_H
#define EMU_JUKEBOX_HOTKEYMANAGER_H

#include <map>
#include "EventManager.h"
#include "../classes/Hotkey.h"

namespace ebox
{
    /*!
     * HotkeyManager! Using the name Hotkeys just for naming simplicity. Not to be confused with the "Hotkey" class
     */
    class Hotkeys
    {
        public:
            enum class ProgramHotkey
            {
                    None = 0,
                    OpenFolder = 1,
                    OpenFile = 2,
                    CloseApplication = 3,
                    Copy = 4,
                    Paste = 5
            };

            enum class PlayerHotkey
            {
                    None = 0,
                    ToggleVoiceMute1 = 1,
                    ToggleVoiceMute2 = 2,
                    ToggleVoiceMute3 = 3,
                    ToggleVoiceMute4 = 4,
                    ToggleVoiceMute5 = 5,
                    ToggleVoiceMute6 = 6,
                    ToggleVoiceMute7 = 7,
                    ToggleVoiceMute8 = 8,
                    ToggleVoiceMute9 = 9,
                    PreviousTrack = 10,
                    NextTrack = 11,
                    TogglePlayAndPause = 12,
                    Stop = 13

            };

            enum class PlaylistHotkey
            {
                    None = 0,
                    MoveItemUp = 1,
                    MoveItemDown = 2,
                    DeleteItem = 3
            };

            enum class FilelistHotkey
            {
                    None = 0,
                    DeleteItem = 1
            };

            static Hotkeys *get() {
                static Hotkeys manager;
                return &manager;
            }

            void setEventManager(ebox::EventManager *eventManager);
            sf::Vector2i getMousePosition();

            bool isActive() const;

            void setActive(bool isActive);

            bool isProgramHotkeyPressed(ProgramHotkey hotkey);
            bool isProgramHotkeyDown(ProgramHotkey hotkey);
            bool isPlayerHotkeyPressed(PlayerHotkey hotkey);
            bool isPlayerHotkeyDown(PlayerHotkey hotkey);
            bool isPlaylistHotkeyPressed(PlaylistHotkey hotkey);
            bool isPlaylistHotkeyDown(PlaylistHotkey hotkey);
            bool isFilelistHotkeyPressed(FilelistHotkey hotkey);
            bool isFilelistHotkeyDown(FilelistHotkey hotkey);

            bool isShiftKeyDown();
            bool isControlKeyDown();
            bool isAltKeyDown();

            bool isMousePressed(sf::Mouse::Button button = sf::Mouse::Button::Left);
            bool isMouseDown(sf::Mouse::Button button = sf::Mouse::Button::Left);

            float getMouseWheelScroll();

        protected:
            void resetStates();

            Hotkeys();
            void generateDefaultHotkeys();

            ebox::EventManager *m_events;

            bool m_isActive = true;

            std::map<sf::Mouse::Button, bool> m_mouseButtonPressed;

            std::map<ProgramHotkey, Hotkey> m_programHotkeys;
            std::map<ProgramHotkey, bool> m_programHotkeyPressed;
            std::map<PlayerHotkey, Hotkey> m_playerHotkeys;
            std::map<PlayerHotkey, bool> m_playerHotkeyPressed;
            std::map<PlaylistHotkey, Hotkey> m_playlistHotkeys;
            std::map<PlaylistHotkey, bool> m_playlistHotkeyPressed;
            std::map<FilelistHotkey, Hotkey> m_filelistHotkeys;
            std::map<FilelistHotkey, bool> m_filelistHotkeyPressed;
    };
}

#endif //EMU_JUKEBOX_HOTKEYMANAGER_H
