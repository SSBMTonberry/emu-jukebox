//
// Created by robin on 10.01.19.
//

#ifndef EMU_JUKEBOX_VOICE_H
#define EMU_JUKEBOX_VOICE_H

#include <iostream>

namespace ebox
{
    class Voice
    {
        public:
            Voice();
            Voice(int channelNo, const std::string &channelName, bool isMuted);

            void toggleMute();

            void setChannelNo(int channelNo);
            void setChannelName(const std::string &channelName);
            void setMuted(bool isMuted);

            int getChannelNo() const;
            const std::string &getChannelName() const;
            bool isMuted() const;

        private:
            int m_channelNo = 0;
            std::string m_channelName = "";
            bool m_isMuted = true;
    };
}

#endif //EMU_JUKEBOX_VOICE_H
