//
// Created by robin on 10.01.19.
//

#include "Voice.h"

ebox::Voice::Voice()
{
    initializeHotkeyMap();
}

ebox::Voice::Voice(Music_Emu *emu, int channelNo, const std::string &channelName, bool isMuted, sf::Keyboard::Key hotkey)
                   : m_emu {emu}, m_channelNo {channelNo}, m_channelName {channelName}, m_isMuted {isMuted}, m_hotkey {hotkey}
{
    initializeHotkeyMap();
    std::string title = (hotkey != sf::Keyboard::Key::Unknown) ? fmt::format("{0} (Hotkey: {1})", channelName, m_hotkeyMap[hotkey]) : channelName;
    m_checkbox.initialize(title, title, !isMuted);
}

void ebox::Voice::toggleMute()
{
    setMuted(!m_isMuted);
    m_checkbox.setChecked(!m_isMuted);
}

int ebox::Voice::getChannelNo() const
{
    return m_channelNo;
}

void ebox::Voice::setChannelNo(int channelNo)
{
    m_channelNo = channelNo;
}

const std::string &ebox::Voice::getChannelName() const
{
    return m_channelName;
}

void ebox::Voice::setChannelName(const std::string &channelName)
{
    m_channelName = channelName;
}

bool ebox::Voice::isMuted() const
{
    return m_isMuted;
}

void ebox::Voice::setMuted(bool isMuted)
{
    m_isMuted = isMuted;
    m_emu->mute_voice(m_channelNo, isMuted);
}

bool *ebox::Voice::getMuted()
{
    return &m_isMuted;
}

Music_Emu *ebox::Voice::getEmu() const
{
    return m_emu;
}

void ebox::Voice::setEmu(Music_Emu *emu)
{
    m_emu = emu;
}

void ebox::Voice::showCheckbox()
{
    checkHotkeyPress();
    if(m_checkbox.process())
    {
        setMuted(!m_checkbox.isChecked());
    }
}

void ebox::Voice::setHotkey(sf::Keyboard::Key key)
{
    m_hotkey = key;
}

sf::Keyboard::Key ebox::Voice::getHotkey() const
{
    return m_hotkey;
}

void ebox::Voice::checkHotkeyPress()
{
    if(sf::Keyboard::isKeyPressed(m_hotkey) && !m_hotkeyPressed)
    {
        m_hotkeyPressed = true;
        toggleMute();
    }
    else if(!sf::Keyboard::isKeyPressed(m_hotkey))
        m_hotkeyPressed = false;
}

void ebox::Voice::initializeHotkeyMap()
{
    m_hotkeyMap[sf::Keyboard::Num0] = "0";
    m_hotkeyMap[sf::Keyboard::Num1] = "1";
    m_hotkeyMap[sf::Keyboard::Num2] = "2";
    m_hotkeyMap[sf::Keyboard::Num3] = "3";
    m_hotkeyMap[sf::Keyboard::Num4] = "4";
    m_hotkeyMap[sf::Keyboard::Num5] = "5";
    m_hotkeyMap[sf::Keyboard::Num6] = "6";
    m_hotkeyMap[sf::Keyboard::Num7] = "7";
    m_hotkeyMap[sf::Keyboard::Num8] = "8";
    m_hotkeyMap[sf::Keyboard::Num9] = "9";
}
