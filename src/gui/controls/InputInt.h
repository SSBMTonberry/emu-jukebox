//
// Created by robin on 22.07.18.
//

#ifndef EMU_JUKEBOX_INPUTINT_H
#define EMU_JUKEBOX_INPUTINT_H

#include "Control.h"

namespace ebox
{
    class InputInt : public Control
    {
        public:
            InputInt(const std::string &id, const std::string &label);
            InputInt(const std::string &id, const std::string &label, int minimum, int maximum, int step, int stepFast);

            void initialize(int minimum, int maximum, int step, int stepFast);
            bool process() override;

            void setValue(int value);

            int getValue() const;

        protected:
            bool performValueValidation();

            int m_value;
            int m_minimum;
            int m_maximum;
            int m_step;
            int m_stepFast;
    };
}

#endif //EMU_JUKEBOX_INPUTINT_H
