//
// Created by robin on 20.01.18.
//

#include "SliderFloat.h"

/*!
 *
 * @param id
 * @param label
 * @param minimum
 * @param maximum
 * @param decimals
 * @param sliderType
 * @param size Only used for vertical sliders
 */
ebox::SliderFloat::SliderFloat(const std::string &id, const std::string &label, float minimum,
                              float maximum, int decimals, ebox::SliderFloat::SliderFloatType sliderType,
                              const sf::Vector2<int> &size)
        : Control (id, label), m_minimum {minimum}, m_maximum {maximum}, m_decimals {decimals},
          m_sliderSize {sliderType}, m_size {size}
{
    //m_minimum = minimum;
    //m_maximum = maximum;
    //m_decimals = decimals;
    m_format = fmt::format("%.{0}f", decimals);
    //m_sliderSize = sliderType;
    //m_size = size;
    m_type = ControlType::SliderFloat;
    initialize();
}

void ebox::SliderFloat::initialize()
{
    switch (m_sliderSize)
    {
        case SliderFloatType::H_One:
        case SliderFloatType::Vertical:
            m_values = std::make_unique<float[]>(1);
            m_values[0] = m_minimum;
            m_arraySize = 1;
            break;

        case SliderFloatType::H_Two:
            m_values = std::make_unique<float[]>(2);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_arraySize = 2;
            break;

        case SliderFloatType::H_Three:
            m_values = std::make_unique<float[]>(3);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_arraySize = 3;
            break;

        case SliderFloatType::H_Four:
            m_values = std::make_unique<float[]>(4);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_values[3] = m_minimum;
            m_arraySize = 4;
            break;
    }
}

bool ebox::SliderFloat::process()
{
    bool isChanged = false;
    if(Control::process())
    {
        if(processSlider())
        {
            isChanged = true;
        }
    }

    return isChanged;
}

void ebox::SliderFloat::setValues(const std::initializer_list<float> &values)
{
    size_t size = (m_arraySize > values.size()) ? values.size() : m_arraySize;

    size_t i = 0;
    for(const auto & v : values)
    {
        if(i < size)
            m_values[i] = v;

        i++;
    }
}

const float * ebox::SliderFloat::getValues() const
{
    return m_values.get();
}

bool ebox::SliderFloat::processSlider()
{
    std::string format = (m_hideNumber) ? "" : m_format;
    switch (m_sliderSize)
    {
        case SliderFloatType::H_One:
            return ImGui::SliderFloat(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderFloatType::H_Two:
            return ImGui::SliderFloat2(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderFloatType::H_Three:
            return ImGui::SliderFloat3(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderFloatType::H_Four:
            return ImGui::SliderFloat4(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderFloatType::Vertical:
            return ImGui::VSliderFloat(m_label.c_str(), m_size, m_values.get(), m_minimum, m_maximum, format.c_str());

    }
    return false;
}

bool ebox::SliderFloat::getHideNumber() const
{
    return m_hideNumber;
}

void ebox::SliderFloat::setHideNumber(bool hideNumber)
{
    m_hideNumber = hideNumber;
}
