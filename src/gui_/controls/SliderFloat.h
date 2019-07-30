//
// Created by robin on 20.01.18.
//

#ifndef EMU_JUKEBOX_SLIDERFLOAT_H
#define EMU_JUKEBOX_SLIDERFLOAT_H

#include "Control.h"

namespace ebox
{
    class SliderFloat : public Control
    {
        public:
            enum class SliderFloatType : unsigned
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

            SliderFloat(const std::string &id, const std::string &label, float minimum, float maximum,
                        int decimals = 3, SliderFloatType sliderType = SliderFloatType::H_One, const sf::Vector2<int> &size = {0,0});

            bool process() override;

            void setValues(const std::initializer_list<float> &values);
            void setHideNumber(bool hideNumber);

            const float * getValues() const;
            bool getHideNumber() const;

        protected:
            bool processSlider();

            SliderFloatType m_sliderSize = SliderFloatType::H_One;

            bool m_hideNumber = false;

            sf::Vector2<int> m_size = {0,0};
            size_t m_arraySize = 1;
            std::unique_ptr<float[]> m_values;
            float m_minimum;
            float m_maximum;
            int m_decimals = 2;
            std::string m_format;

        private:
            void initialize();
    };
}

#endif //EMU_JUKEBOX_SLIDERFLOAT_H
