//
// Created by robin on 10.01.19.
//

#include "Voice.h"

ebox::Voice::Voice()
{

}

ebox::Voice::Voice(int channelNo, const std::string &channelName, bool isMuted)
                   : m_channelNo {channelNo}, m_channelName {channelName}, m_isMuted {isMuted}
{

}

void ebox::Voice::toggleMute()
{
    m_isMuted = !m_isMuted;
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
}
