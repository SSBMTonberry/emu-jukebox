//
// Created by robin on 28.01.18.
//

#include "DragInt.h"

ebox::DragInt::DragInt(const std::string &id, const std::string &label, int minimum, int maximum,
                      float speed, ebox::DragInt::DragIntSize dragSize)
        : Control(id, label), m_minimum {minimum}, m_maximum {maximum}, m_speed {speed}, m_dragSize {dragSize}
{
    //m_minimum = minimum;
    //m_maximum = maximum;
    //m_speed = speed;
    m_type = ControlType::DragInt;
    //m_dragSize = dragSize;
    initialize();
}

bool ebox::DragInt::process()
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

void ebox::DragInt::initialize()
{
    switch (m_dragSize)
    {
        case DragIntSize::One:
            m_values = std::make_unique<int[]>(1);
            m_values[0] = m_minimum;
            m_arraySize = 1;
            break;

        case DragIntSize::Two:
            m_values = std::make_unique<int[]>(2);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_arraySize = 2;
            break;

        case DragIntSize::Three:
            m_values = std::make_unique<int[]>(3);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_arraySize = 3;
            break;

        case DragIntSize::Four:
            m_values = std::make_unique<int[]>(4);
            m_values[0] = m_minimum;
            m_values[1] = m_minimum;
            m_values[2] = m_minimum;
            m_values[3] = m_minimum;
            m_arraySize = 4;
            break;
    }
}

bool ebox::DragInt::processDrag()
{
    std::string format = (m_hideNumber) ? "" : "%.0f";
    ImGui::PushItemWidth(m_width);
    switch (m_dragSize)
    {
        case DragIntSize::One:
            return ImGui::DragInt(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragIntSize::Two:
            return ImGui::DragInt2(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragIntSize::Three:
            return ImGui::DragInt3(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
        case DragIntSize::Four:
            return ImGui::DragInt4(m_label.c_str(), m_values.get(), m_speed, m_minimum, m_maximum, format.c_str());
    }
    ImGui::PopItemWidth();
}

void ebox::DragInt::setValues(const std::initializer_list<int> &values)
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

const int *ebox::DragInt::getValues() const
{
    return m_values.get();
}

float ebox::DragInt::getSpeed() const
{
    return m_speed;
}

void ebox::DragInt::setSpeed(float speed)
{
    m_speed = speed;
}

bool ebox::DragInt::getHideNumber() const
{
    return m_hideNumber;
}

void ebox::DragInt::setHideNumber(bool hideNumber)
{
    m_hideNumber = hideNumber;
}

/*!
 * Simply makes sure none of the values are below minimum or above maximum.
 * @return if a value had to be corrected
 */
bool ebox::DragInt::performValueValidation()
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

float ebox::DragInt::getWidth() const
{
    return m_width;
}

void ebox::DragInt::setWidth(float width)
{
    m_width = width;
}
