//
// Created by robin on 17.02.19.
//

#ifndef EMU_JUKEBOX_TIMER_H
#define EMU_JUKEBOX_TIMER_H

#include <chrono>
#include <string>
#include "pmgui.h"
//#include <fmt/format.h>
#include "../../EmuJukeboxConfig.h"
using namespace std::chrono_literals;

namespace ebox
{
    class Timer
    {
        enum class TimerState : unsigned
        {
            /*! When nothing has been started */
            Idle = 0,
            /*! When the start() function has been called*/
            Running = 1,
            /*! */
            Stopped = 2
        };

        public:
            Timer();
            Timer(bool startOnCreate);

            void start();
            void reset();
            void end();

            std::chrono::duration<double> getElapsedTime();
            std::string getTimeElapsedMessage(std::string preMsg = "");
        private:

            TimerState m_state = TimerState::Idle;
            std::chrono::time_point<std::chrono::system_clock> m_startPoint;
            std::chrono::time_point<std::chrono::system_clock> m_endPoint;
    };
}

#endif //EMU_JUKEBOX_TIMER_H
