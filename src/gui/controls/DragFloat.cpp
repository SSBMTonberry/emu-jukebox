//
// Created by robin on 28.01.18.
//

#include "DragFloat.h"

ebox::DragFloat::DragFloat(const std::string &id, const std::string &label, float minimum, float maximum,
                          int decimals, float speed, ebox::DragFloat::DragFloatSize dragSize)
        : Control(id, label), m_minimum {minimum}, m_maximum {maximum}, m_speed {speed}, m_dragSize {dragSize},
          m_decimals {decimals}
{
    //m_minimum = minimum;
    //m_maximum = maximum;
    //m_speed = speed;
    m_type = ControlType::DragFloat;
    //m_dragSize = dragSize;
    //m_decimals = decimals;
    m_format = fmt::format("%.{0}f", decimals);
    initialize();
}

bool ebox::DragFloat::process()
{
    bool isChanged = false;
    if(Control::process())
    {
        if(processDrag())
        {
            performValueValidation();
            isChanged = true;
        }
    }

    return isChanged;
}

void ebox::DragFloat::setValues(const std::initializer_list<float> &values)
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

const float *ebox::DragFloat::getValues() const
{
    return m_values.get();
}

bool ebox::DragFloat::processDrag()
{
    std::string format = (m_hideNumber) ? "" : m_format;
    switch (m_dragSize)
    {
        case DragFloatSize::One:
            return ImGui::DragFloat(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragFloatSize::Two:
            return ImGui::DragFloat2(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragFloatSize::Three:
            return ImGui::DragFloat3(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragFloatSize::Four:
            return ImGui::DragFloat4(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
    }

    return false;
}

bool ebox::DragFloat::performValueValidation()
{
    bool valuesHasBeenCorrected = false;

    for(int i = 0; i < m_arraySize; i++)
    {
        if(m_values[i] < m_minimum)
        {
            m_values[i] = m_minimum;
            valuesHasBeenCorrected = true;
        }
        else if(m_values[i] > m_maximum)
        {
            m_values[i] = m_maximum;
            valuesHasBeenCorrected = true;
        }
    }

    return valuesHasBeenCorrected;
}

void ebox::DragFloat::initialize()
{
    switch (m_dragSize)
    {
        case DragFloatSize::One:
            m_values = std::make_unique<float[]>(1);
            m_values[0] = m_minimum;
            m_arraySize = 1;
            break;

        case DragFloatSize::Two:
            m_values = std::make_unique<float[]>(2);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_arraySize = 2;
            break;

        case DragFloatSize::Three:
            m_values = std::make_unique<float[]>(3);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_arraySize = 3;
            break;

        case DragFloatSize::Four:
            m_values = std::make_unique<float[]>(4);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_values[3] = m_minimum;
            m_arraySize = 4;
            break;
    }
}

bool ebox::DragFloat::getHideNumber() const
{
    return m_hideNumber;
}

void ebox::DragFloat::setHideNumber(bool hideNumber)
{
    m_hideNumber = hideNumber;
}

float ebox::DragFloat::getSpeed() const
{
    return m_speed;
}

void ebox::DragFloat::setSpeed(float speed)
{
    m_speed = speed;
}
