//
// Created by robin on 30.01.18.
//

#include "Column.h"

ebox::Column::Column(const std::string &id, const std::string &label, const std::optional<float> &width) : Control(id, label),
                                                                                                          m_width {width}
{
    //m_width = width;
}

bool ebox::Column::process()
{
    bool anyItemActivated = false;
    if(Control::process())
    {
        for(const auto &item : m_items)
        {
            if(item->process())
                anyItemActivated = true;

        }
    }
    return anyItemActivated;
}


void ebox::Column::add(std::unique_ptr<ebox::Control> control)
{
    m_items.push_back(std::move(control));
}

const float ebox::Column::getWidth() const
{
    return m_width.value();
}

void ebox::Column::setWidth(const std::optional<float> &width)
{
    m_width = width;
}

const bool ebox::Column::hasWidth()
{
    return (m_width.has_value());
}

/*!
 * Sets the width of column based on the available space
 * Value range is from 0 to 100.
 * @param widthByPercentOfAvailableSpace
 */
void ebox::Column::setWidthByPercent(size_t widthByPercentOfAvailableSpace)
{
    if(widthByPercentOfAvailableSpace > 100)
        widthByPercentOfAvailableSpace = 100;

    float width = ImGui::GetContentRegionAvailWidth() * ((float)widthByPercentOfAvailableSpace / 100);
    m_width = width;
}
