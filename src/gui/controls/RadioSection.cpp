//
// Created by robin on 13.01.18.
//

#include "RadioSection.h"

ebox::RadioSection::RadioSection(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::RadioSection;
}

void ebox::RadioSection::addRadioData(int id, const std::string &label)
{
    m_data.emplace_back(id, label);
}

/*!
 *
 * @return true if any radio-button is pressed. false otherwise
 */
bool ebox::RadioSection::process()
{
    if(Control::process())
    {
        int i = 0;
        bool anythingPressed = false;
        for (const auto &item : m_data)
        {
            bool sameLine = (!m_isHorizontal) ? false : isSameLine(i);

            bool action = ImGui::RadioButton(item.getLabel().c_str(), &m_chosenItem, item.getId());

            if(action)
                anythingPressed = true;

            //Do not apply SameLine on the last element
            if (sameLine && i < m_data.size() - 1)
                ImGui::SameLine();

            ++i;
        }

        return anythingPressed;
    }
    return false;
}

std::string ebox::RadioSection::getValue() const
{
    std::string value = "";
    for(const auto & item : m_data)
    {
        if(item.getId() == m_chosenItem)
            value = item.getLabel();
    }
    return value;
}

ebox::RadioData * ebox::RadioSection::getValue()
{
    for(auto & item : m_data)
    {
        if(item.getId() == m_chosenItem)
            return &item;
    }

    return nullptr;
}

void ebox::RadioSection::setHorizontal(size_t itemsPerRow)
{
    m_itemsPerRow = itemsPerRow;
    m_isHorizontal = true;
}

void ebox::RadioSection::setVertical()
{
    m_isHorizontal = false;
}

void ebox::RadioSection::setValue(int index)
{
    for (auto &i : m_data)
    {
        if(index == i.getId())
            m_chosenItem = index;
    }
}

bool ebox::RadioSection::isSameLine(int i)
{
    if(m_itemsPerRow == 0)
        return true;

    int value = i + 1;
    bool sameLine = false;

    sameLine = ((value % m_itemsPerRow) != 0) ? true : false;

    return sameLine;
}