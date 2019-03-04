//
// Created by robin on 17.02.19.
//

#include "Timer.h"

ebox::Timer::Timer()
{

}

ebox::Timer::Timer(bool startOnCreate)
{
    if(startOnCreate)
        start();
}

void ebox::Timer::start()
{
    m_state = TimerState::Running;
    m_startPoint = std::chrono::system_clock::now();
}

void ebox::Timer::end()
{
    if(m_state == TimerState::Running)
    {
        m_state = TimerState::Stopped;
        m_endPoint = std::chrono::system_clock::now();
    }
}

/*!
 *
 * @param preMsg Message to be added in the front of the elapsed time
 * @return The message with the elapsed time.
 */
std::string ebox::Timer::getTimeElapsedMessage(std::string preMsg)
{
    if(m_state == TimerState::Stopped)
    {
        std::chrono::duration<double> elapsedSeconds = m_endPoint - m_startPoint;
#if MSVC
        time_t endTime = std::chrono::system_clock::to_time_t(m_endPoint);
#elif
        std::time_t endTime = std::chrono::system_clock::to_time_t(m_endPoint);
#endif
        std::string msg = fmt::format("{0} Elapsed time: {1} seconds.", preMsg, elapsedSeconds.count());

        return msg;
    }

    return "Timer must be stopped to get elapsed time...";
}

std::chrono::duration<double> ebox::Timer::getElapsedTime()
{
    if(m_state == TimerState::Stopped)
        return m_endPoint - m_startPoint;

    return std::chrono::duration<double>(0);
}
