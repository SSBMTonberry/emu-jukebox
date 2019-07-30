//
// Created by robin on 17.03.18.
//

#include "DataColumnDefinition.h"


void ebox::DataColumnDefinition::addColumn(const std::string &columnName, const std::string &columnTitle,
                                          size_t dataSize, const DataColumnType &columnType)
{
    std::unique_ptr<DataColumn> col = std::make_unique<DataColumn>(columnName, columnTitle, dataSize, columnType);
    m_columns.push_back(std::move(col));
}

const std::vector<std::unique_ptr<ebox::DataColumn>> &ebox::DataColumnDefinition::getColumns() const
{
    return m_columns;
}

ebox::DataColumn *ebox::DataColumnDefinition::getColumn(const std::string &columnName)
{
    for(auto const &item : m_columns)
    {
        if(item->getName().compare(columnName) == 0)
            return item.get();
    }
    return nullptr;
}
