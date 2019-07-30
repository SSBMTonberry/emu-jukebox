//
// Created by robin on 11.01.18.
//

#include "Tooltip.h"


ebox::Tooltip::Tooltip()
{
    m_type = TooltipType::Basic;
}

ebox::Tooltip::Tooltip(const std::string &text)
{
    m_text = text;
    m_type = TooltipType::Basic;
}

void ebox::Tooltip::show()
{
    ImGui::SetTooltip(m_text.c_str());
}

const std::string &ebox::Tooltip::getText() const
{
    return m_text;
}

void ebox::Tooltip::setText(const std::string &text)
{
    m_text = text;
}


