//
// Created by robin on 20.01.18.
//

#ifndef EMU_JUKEBOX_SLIDERINT_H
#define EMU_JUKEBOX_SLIDERINT_H

#include "Control.h"

namespace ebox
{
    class SliderInt : public Control
    {

        public:
            enum class SliderIntType : unsigned
            {
                /*! One slider, horizontally*/
                H_One = 0,
                /*! Two sliders, horizontally*/
                H_Two = 1,
                /*! Three sliders, horizontally*/
                H_Three = 2,
                /*! Four sliders, horizontally*/
                H_Four = 3,
                /*! One vertical slider*/
                Vertical = 4
            };

            SliderInt(const std::string &id, const std::string &label, int minimum, int maximum,
                      SliderIntType sliderType = SliderIntType::H_One, const sf::Vector2<int> &size = {0,0});

            bool process() override;

            void setValues(const std::initializer_list<int> &values);
            void setHideNumber(bool hideNumber);

            const int * getValues() const;
            bool getHideNumber() const;

        protected:
            bool processSlider();

            bool m_hideNumber = false;

            SliderIntType m_sliderType = SliderIntType::H_One;
            sf::Vector2<int> m_size = {0,0};
            size_t m_arraySize = 1;
            std::unique_ptr<int[]> m_values;
            int m_minimum;
            int m_maximum;

        private:
            void initialize();
    };
}

#endif //EMU_JUKEBOX_SLIDERINT_H
