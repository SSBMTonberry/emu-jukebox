//
// Created by robin on 01.10.18.
//

#include "InputFloat.h"

ebox::InputFloat::InputFloat(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::InputFloat;
}

ebox::InputFloat::InputFloat(const std::string &id, const std::string &label, float minimum, float maximum, float step,
                            float stepFast) : Control(id, label)
{
    m_type = ControlType::InputFloat;
    initialize(minimum, maximum, step, stepFast);
}

/*!
 * MUST be called in the basic constructor that doesn't have these parameters is used
 * @param minimum
 * @param maximum
 * @param step
 * @param stepFast
 */
void ebox::InputFloat::initialize(float minimum, float maximum, float step, float stepFast)
{
    m_minimum = minimum;
    m_maximum = maximum;
    m_step = step;
    m_stepFast = stepFast;
}

bool ebox::InputFloat::process()
{
    bool isChanged = false;
    if(Control::process())
    {
        if(ImGui::InputFloat(m_label.c_str(), &m_value, m_step, m_stepFast))
        {
            performValueValidation();
            isChanged = true;
        }

    }

    return isChanged;
}

void ebox::InputFloat::setValue(float value)
{
    m_value = value;
}

float ebox::InputFloat::getValue() const
{
    return m_value;
}

/*!
 * Simply makes sure none of the values are below minimum or above maximum.
 * @return if a value had to be corrected
 */
bool ebox::InputFloat::performValueValidation()
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

