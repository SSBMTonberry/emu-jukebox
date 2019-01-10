//
// Created by robin on 23.02.18.
//

#include "Row.h"

ebox::Row::Row(const std::string &id, const std::string &label) : Control(id, label)
{

}

bool ebox::Row::process()
{
    bool anyItemActivated = false;
    if(Control::process())
    {
        if(m_columns.size() > 0)
        {
            ImGui::Columns(m_columns.size(), m_label.c_str(), m_hasVerticalBorders);
            for (const auto &column : m_columns)
            {
                if(column->hasWidth())
                {
                    ImGui::SetColumnWidth(ImGui::GetColumnIndex(), column->getWidth());
                }

                if (m_hasHorizontalBorders && ImGui::GetColumnIndex() == 0)
                    ImGui::Separator();

                if (column->process())
                {
                    anyItemActivated = true;
                }
                ImGui::NextColumn();
            }
            ImGui::Columns(1); //Do this to prevent nesting, which makes things crash :(
        }
    }
    return anyItemActivated;
}

void ebox::Row::add(std::unique_ptr<ebox::Column> column)
{
    m_columns.push_back(std::move(column));
}

bool ebox::Row::hasVerticalBorders() const
{
    return m_hasVerticalBorders;
}

void ebox::Row::setHasVerticalBorders(bool hasVerticalBorders)
{
    m_hasVerticalBorders = hasVerticalBorders;
}

bool ebox::Row::hasHorizontalBorders() const
{
    return m_hasHorizontalBorders;
}

void ebox::Row::setHasHorizontalBorders(bool hasHorizontalBorders)
{
    m_hasHorizontalBorders = hasHorizontalBorders;
}
