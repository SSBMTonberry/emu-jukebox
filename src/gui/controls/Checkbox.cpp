//
// Created by robin on 14.01.18.
//

#include "Checkbox.h"

ebox::Checkbox::Checkbox() : Control("", "")
{
    m_type = ControlType::Checkbox;
}

ebox::Checkbox::Checkbox(const std::string &id, const std::string &label, bool isChecked) : Control(id, label),
                                                                                           m_isChecked {isChecked}
{
    m_type = ControlType::Checkbox;
}

void ebox::Checkbox::initialize(const std::string &id, const std::string &label, bool isChecked)
{
    m_id = id;
    m_label = label;
    m_isChecked = isChecked;
}

/*!
 *
 * @return true if checkbox is check/unchecked, false otherwise
 */
bool ebox::Checkbox::process()
{
    if(Control::process())
    {
        bool action = ImGui::Checkbox(m_label.c_str(), &m_isChecked);
        return action;
    }

    return false;
}

bool ebox::Checkbox::isChecked() const
{
    return m_isChecked;
}

void ebox::Checkbox::setChecked(bool isChecked)
{
    m_isChecked = isChecked;
}

/*!
 * Returns a pointer to the actual bool.
 * If you don't need the pointer, use isChecked() instead.
 * @return
 */
bool * ebox::Checkbox::getChecked()
{
    return &m_isChecked;
}

bool ebox::Checkbox::toggle()
{
    m_isChecked = !m_isChecked;
    return m_isChecked;
}
