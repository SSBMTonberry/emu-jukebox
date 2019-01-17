//
// Created by robin on 10.01.19.
//

#ifndef EMU_JUKEBOX_VOICE_H
#define EMU_JUKEBOX_VOICE_H

#include <iostream>
#include <libgme/Music_Emu.h>
#include <SFML/Window.hpp>
#include <map>
#include "../gui/controls/Checkbox.h"

namespace ebox
{
    class Voice
    {
        public:
            Voice();
            Voice(Music_Emu *emu, int channelNo, const std::string &channelName, bool isMuted, sf::Keyboard::Key hotkey = sf::Keyboard::Unknown);

            void showCheckbox();
            void toggleMute();
            void checkHotkeyPress();

            void setHotkey(sf::Keyboard::Key key);
            void setEmu(Music_Emu *emu);
            void setChannelNo(int channelNo);
            void setChannelName(const std::string &channelName);
            void setMuted(bool isMuted);

            Music_Emu *getEmu() const;
            int getChannelNo() const;
            const std::string &getChannelName() const;
            bool isMuted() const;
            bool *getMuted();
            sf::Keyboard::Key getHotkey() const;

        private:
            void initializeHotkeyMap();

            ebox::Checkbox m_checkbox;
            int m_channelNo = 0;
            std::string m_channelName = "";
            bool m_isMuted = false;
            bool m_hotkeyPressed = false;
            std::map<sf::Keyboard::Key, std::string> m_hotkeyMap;

            Music_Emu *m_emu = nullptr;
            sf::Keyboard::Key m_hotkey = sf::Keyboard::Key::Unknown;
    };
}

#endif //EMU_JUKEBOX_VOICE_H
