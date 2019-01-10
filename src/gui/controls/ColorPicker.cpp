//
// Created by robin on 21.01.18.
//

#include "ColorPicker.h"

ebox::ColorPicker::ColorPicker(const std::string &id, const std::string &label, const ColorPickerType &pickerType,
                              const sf::Color &defaultColor) : Control(id, label), m_pickerType {pickerType}
{
    //m_pickerType = pickerType;
    m_type = ControlType::ColorPicker;
    setColor(defaultColor);
}

bool ebox::ColorPicker::process()
{
    bool valueChanged = false;
    if(Control::process())
    {
        if (processByPickerType())
        {
            setColor(m_values);
            valueChanged = true;
        }
    }

    return valueChanged;
}

bool ebox::ColorPicker::processByPickerType()
{
    switch (m_pickerType)
    {
        case ColorPickerType::ColorEdit3:
            return ImGui::ColorEdit3(m_label.c_str(), (float *) &m_values);
        case ColorPickerType::ColorEdit4:
            return ImGui::ColorEdit4(m_label.c_str(), (float *) &m_values);
        case ColorPickerType::ColorPicker3:
            //Use ColorEdit till the bug causing crash between ColorPicker and Textbox is fixed.
            return ImGui::ColorEdit3(m_label.c_str(), (float *) &m_values); //ImGui::ColorPicker3(m_label.c_str(), (float *) &m_values);
        case ColorPickerType::ColorPicker4:
            //Use ColorEdit till the bug causing crash between ColorPicker and Textbox is fixed.
            return ImGui::ColorEdit4(m_label.c_str(), (float *) &m_values); //ImGui::ColorPicker4(m_label.c_str(), (float *)&m_values);

    }

    return false;
}

const sf::Color &ebox::ColorPicker::getColor() const
{
    return m_color;
}

void ebox::ColorPicker::setColor(const sf::Color &color)
{
    m_values = ImVec4(color);//ImVec4(color.r/255, color.g/255, color.b/255, color.a/255);
    m_color = color;
}
