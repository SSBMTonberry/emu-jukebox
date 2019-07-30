//
// Created by robin on 20.01.18.
//

#include "SliderInt.h"

/*!
 *
 * @param id
 * @param label
 * @param minimum
 * @param maximum
 * @param sliderType
 * @param size Only used for vertical sliders
 */
ebox::SliderInt::SliderInt(const std::string &id, const std::string &label, int minimum, int maximum,
                          SliderIntType sliderType, const sf::Vector2<int> &size)
        : Control(id, label), m_minimum {minimum}, m_maximum {maximum}, m_size {size}, m_sliderType {sliderType}
{
    //m_minimum = minimum;
    //m_maximum = maximum;
    //m_size = size;
    m_type = ControlType::DragInt;
    //m_sliderType = sliderType;
    initialize();
}

bool ebox::SliderInt::process()
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

void ebox::SliderInt::initialize()
{
    switch (m_sliderType)
    {
        case SliderIntType::H_One:
        case SliderIntType::Vertical:
            m_values = std::make_unique<int[]>(1);
            m_values[0] = m_minimum;
            m_arraySize = 1;
            break;

        case SliderIntType::H_Two:
            m_values = std::make_unique<int[]>(2);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_arraySize = 2;
            break;

        case SliderIntType::H_Three:
            m_values = std::make_unique<int[]>(3);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_arraySize = 3;
            break;

        case SliderIntType::H_Four:
            m_values = std::make_unique<int[]>(4);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_values[3] = m_minimum;
            m_arraySize = 4;
            break;
    }
}

bool ebox::SliderInt::processSlider()
{
    std::string format = (m_hideNumber) ? "" : "%.0f";
    switch (m_sliderType)
    {
        case SliderIntType::H_One:
            return ImGui::SliderInt(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderIntType::H_Two:
            return ImGui::SliderInt2(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderIntType::H_Three:
            return ImGui::SliderInt3(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderIntType::H_Four:
            return ImGui::SliderInt4(m_label.c_str(), m_values.get(), m_minimum, m_maximum, format.c_str());
        case SliderIntType::Vertical:
            return ImGui::VSliderInt(m_label.c_str(), m_size, m_values.get(), m_minimum, m_maximum, format.c_str());
    }

    return false;
}

void ebox::SliderInt::setValues(const std::initializer_list<int> &values)
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

const int * ebox::SliderInt::getValues() const
{
    return m_values.get();
}

bool ebox::SliderInt::getHideNumber() const
{
    return m_hideNumber;
}

void ebox::SliderInt::setHideNumber(bool hideNumber)
{
    m_hideNumber = hideNumber;
}

