//
// Created by robin on 10.03.18.
//

#include "Progressbar.h"

/*!
 *
 * @param id
 * @param format Uses the fmt format string. {0} = current progress, {1} is the max value
 * @param min
 * @param max
 * @param size
 * @param currentProgress
 */
ebox::Progressbar::Progressbar(const std::string &id, float min, float max, const std::string &format, const sf::Vector2<int> &size, float currentProgress)
                             : Control(id, format), m_minimum {min}, m_maximum {max}, m_size {size},
                               m_currentProgress {currentProgress}
{
    m_type = ControlType::ProgressBar;
    //m_minimum = min;
    //m_maximum = max;
    //m_size = size;
    //m_currentProgress = currentProgress;

    if(m_currentProgress > m_maximum)
        m_currentProgress = m_maximum;

}

bool ebox::Progressbar::process()
{
    if(Control::process())
    {
        m_title = fmt::format(m_label, m_currentProgress, m_maximum);
        float progress = m_currentProgress / m_maximum;
        ImGui::ProgressBar(progress, m_size, m_title.c_str());

        return true;
    }
    return false;
}


float ebox::Progressbar::getCurrentProgress() const
{
    return m_currentProgress;
}

void ebox::Progressbar::setCurrentProgress(float currentProgress)
{
    m_currentProgress = currentProgress;
}

float ebox::Progressbar::getMaximum() const
{
    return m_maximum;
}

void ebox::Progressbar::setMaximum(float maximum)
{
    m_maximum = maximum;
}

const sf::Vector2<int> &ebox::Progressbar::getSize() const
{
    return m_size;
}

void ebox::Progressbar::setSize(const sf::Vector2<int> &size)
{
    m_size = size;
}
