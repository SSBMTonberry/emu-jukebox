//

#include "Control.h"

//
// Created by robin on 27.12.17.

ebox::Control::Control() : m_id {"unnamed"}, m_label {""}
{

}

/*!
 * A bare minimum implementation of Control.
 * Perfect for simple objects when allocating on stack memory.
 * @param id
 */
ebox::Control::Control(std::string id) : m_id {std::move(id)}
{
    m_label = "";
}

ebox::Control::Control(const std::string &id, const std::string &label) : m_id {id}, m_label {label}
{
    //m_id = id;
    //m_propertyTitle = label;
}

const std::string & ebox::Control::getLabel() const
{
    return m_label;
}

void ebox::Control::setLabel(const std::string &label)
{
    m_label = label;
}

ebox::ControlType ebox::Control::getType() const
{
    return m_type;
}

const std::string &ebox::Control::getId() const
{
    return m_id;
}

void ebox::Control::setUseDefaultColor(bool useDefaultColor)
{
    m_useDefaultColor = useDefaultColor;
}

bool ebox::Control::isUsingDefaultColor() const
{
    return m_useDefaultColor;
}

void ebox::Control::assignColors()
{

}

bool ebox::Control::isOnSameLine() const
{
    return m_putOnSameLine;
}

void ebox::Control::setOnSameLine(bool putOnSameLine)
{
    m_putOnSameLine = putOnSameLine;
}

bool ebox::Control::process()
{
    if(m_putOnSameLine)
        ImGui::SameLine();

    return m_isVisible;
}

const std::optional<ebox::Tooltip> &ebox::Control::getTooltip() const
{
    return m_tooltip;
}

void ebox::Control::setTooltip(const std::optional<ebox::Tooltip> &tooltip)
{
    m_tooltip = std::move(tooltip);
}

void ebox::Control::createBasicTooltip(const std::string &text)
{
    m_tooltip = std::make_optional<Tooltip>(text);
}

bool ebox::Control::isVisible() const
{
    return m_isVisible;
}

void ebox::Control::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

void ebox::Control::setId(const std::string &id)
{
    m_id = id;
}

