//
// Created by robin on 13.01.18.
//

#include "RadioData.h"


ebox::RadioData::RadioData(const int &id, const std::string &label)
{
    m_id = id;
    m_label = label;
}

int ebox::RadioData::getId() const
{
    return m_id;
}

const std::string &ebox::RadioData::getLabel() const
{
    return m_label;
}

void ebox::RadioData::setId(int id)
{
    m_id = id;
}


void ebox::RadioData::setLabel(const std::string &label)
{
    m_label = label;
}
