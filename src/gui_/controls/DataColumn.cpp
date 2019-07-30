//
// Created by robin on 15.03.18.
//

#include "DataColumn.h"


ebox::DataColumn::DataColumn(const std::string &columnName, const std::string &columnTitle, size_t dataSize, const DataColumnType &dataColumnType) :
                            m_name {columnName}, m_title {columnTitle}, m_dataSize {dataSize}, m_dataColumnType {dataColumnType}
{

}

void ebox::DataColumn::setWidth(const std::optional<float> &width)
{
    m_width = width;
}

void ebox::DataColumn::setDataColumnType(ebox::DataColumnType dataColumnType)
{
    m_dataColumnType = dataColumnType;
}

const float ebox::DataColumn::getWidth() const
{
    return m_width.value();
}

const bool ebox::DataColumn::hasWidth()
{
    return (m_width.has_value());
}


const std::string &ebox::DataColumn::getName() const
{
    return m_name;
}

const std::string &ebox::DataColumn::getTitle() const
{
    return m_title;
}

ebox::DataColumnType ebox::DataColumn::getDataColumnType() const
{
    return m_dataColumnType;
}

size_t ebox::DataColumn::getDataSize() const
{
    return m_dataSize;
}

void ebox::DataColumn::setDataSize(size_t dataSize)
{
    m_dataSize = dataSize;
}


