//
// Created by robin on 10.01.19.
//

#include "Voice.h"

ebox::Voice::Voice(Music_Emu *emu, int channelNo, const std::string &channelName, bool isMuted)//, sf::Keyboard::Key hotkey)
                   : m_emu {emu}, m_channelNo {channelNo}, m_channelName {channelName}, m_isMuted {isMuted}//, m_hotkey {hotkey}
{
    std::string title = channelName;
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
    if(m_checkbox.process())
    {
        setMuted(!m_checkbox.isChecked());
    }
}

void ebox::Voice::setTooltip(const std::string &tooltip)
{
    m_checkbox.setTooltip(std::make_optional<Tooltip>(tooltip));
}