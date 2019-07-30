//
// Created by robin on 10.03.18.
//

#ifndef EMU_JUKEBOX_PROGRESSBAR_H
#define EMU_JUKEBOX_PROGRESSBAR_H

#include "Control.h"
#include <fmt/format.h>
namespace ebox
{
    class Progressbar : public Control
    {
        public:
            Progressbar(const std::string &id, float min, float max, const std::string &format = "{0}/{1}", const sf::Vector2<int> &size = {-1,0}, float currentProgress = 0.f);

            bool process() override;

            void setSize(const sf::Vector2<int> &size);
            void setMaximum(float maximum);
            void setCurrentProgress(float currentProgress);

            const sf::Vector2<int> &getSize() const;
            float getMaximum() const;
            float getCurrentProgress() const;

        public:
            sf::Vector2<int> m_size = {-1,0};
            float m_minimum = 0.f;
            float m_maximum = 0.f;
            float m_currentProgress = 0.f;
            std::string m_title = ""; //The title displayed on the progress bar, based on label, which is the format string
    };
}

#endif //EMU_JUKEBOX_PROGRESSBAR_H
