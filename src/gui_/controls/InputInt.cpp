//
// Created by robin on 22.07.18.
//

#include "InputInt.h"

ebox::InputInt::InputInt(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::InputInt;
}

ebox::InputInt::InputInt(const std::string &id, const std::string &label, int minimum, int maximum, int step, int stepFast)
        : Control(id, label)
{
    m_type = ControlType::InputInt;
    initialize(minimum, maximum, step, stepFast);
}

/*!
 * MUST be called in the basic constructor that doesn't have these parameters is used
 * @param minimum
 * @param maximum
 * @param step
 * @param stepFast
 */
void ebox::InputInt::initialize(int minimum, int maximum, int step, int stepFast)
{
    m_minimum = minimum;
    m_maximum = maximum;
    m_step = step;
    m_stepFast = stepFast;
}

bool ebox::InputInt::process()
{
    bool isChanged = false;
    if(Control::process())
    {
        if(ImGui::InputInt(m_label.c_str(), &m_value, m_step, m_stepFast))
        {
            performValueValidation();
            isChanged = true;
        }
    }

    return isChanged;
}

/*!
 * Simply makes sure none of the values are below minimum or above maximum.
 * @return if a value had to be corrected
 */
bool ebox::InputInt::performValueValidation()
{
    bool valuesHasBeenCorrected = false;

    if(m_value < m_minimum)
    {
        m_value = m_minimum;
        valuesHasBeenCorrected = true;
    }
    else if(m_value > m_maximum)
    {
        m_value = m_maximum;
        valuesHasBeenCorrected = true;
    }

    return valuesHasBeenCorrected;
}

int ebox::InputInt::getValue() const
{
    return m_value;
}

void ebox::InputInt::setValue(int value)
{
    m_value = value;
}