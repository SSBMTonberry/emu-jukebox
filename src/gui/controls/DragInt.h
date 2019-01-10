//
// Created by robin on 28.01.18.
//

#ifndef EMU_JUKEBOX_DRAGINT_H
#define EMU_JUKEBOX_DRAGINT_H

#include "Control.h"

namespace ebox
{
    class DragInt : public Control
    {
        public:
            enum class DragIntSize : unsigned
            {
                One = 0,
                Two = 1,
                Three = 2,
                Four = 3
            };

            DragInt(const std::string &id, const std::string &label, int minimum, int maximum,
                    float speed = 1.f, DragIntSize dragSize = DragIntSize::One);

            bool process() override;

            void setValues(const std::initializer_list<int> &values);
            void setSpeed(float speed);
            void setHideNumber(bool hideNumber);

            const int * getValues() const;
            float getSpeed() const;
            bool getHideNumber() const;

        protected:
            bool processDrag();
            bool performValueValidation();
            bool m_hideNumber = false;

            DragIntSize m_dragSize = DragIntSize::One;
            size_t m_arraySize = 1;
            std::unique_ptr<int[]> m_values;
            int m_minimum;
            int m_maximum;
            float m_speed;

        private:
            void initialize();

    };
}


#endif //EMU_JUKEBOX_DRAGINT_H
