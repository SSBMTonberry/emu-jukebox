//
// Created by robin on 21.02.18.
//

#include "Table.h"

ebox::Table::Table(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::Table;
}

bool ebox::Table::process()
{
    bool anyItemActivated = false;
    if(Control::process())
    {
        for(const auto &row : m_rows)
        {
            if(row->process())
            {
                anyItemActivated = true;
            }
        }
        ImGui::Separator();
    }

    return anyItemActivated;
}

void ebox::Table::add(std::unique_ptr<ebox::Row> row)
{
    m_rows.push_back(std::move(row));
}

/*void ebox::Table::addRange(std::initializer_list<std::unique_ptr<ebox::Column>> &columns)
{
    for(auto &item : columns)
    {
        m_rows.push_back(item);
    }
}*/
