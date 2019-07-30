//
// Created by robin on 07.03.18.
//

#include "Child.h"

/*!
 * A child form for creating layouts inside a form
 * ocornut: Note that you can pass a (0,0) for fit all or a negative value to align from the right or lower edge. Works on both axis independently.
 * @param id
 * @param label
 * @param size
 * @param hasBorder
 * @param flags
 */
ebox::Child::Child(const std::string &id, const std::string &label, const sf::Vector2<int> &size, bool hasBorder,
                  ebox::FormFlags flags) : Control(id, label), m_size {size}, m_hasBorder {hasBorder}, m_flags{flags}
{
    //m_size = size;
    //m_hasBorder = hasBorder;
    //m_flags = flags;
    m_type = ControlType::Child;
}

bool ebox::Child::process()
{
    bool anyItemActivated = false;
    if(Control::process())
    {
        ImGui::BeginChild(getId().c_str(), m_size, m_hasBorder, getFlagsAsImGuiFlags());
        for(const auto &item : m_items)
        {
            if(item->process())
                anyItemActivated = true;

        }
        for(const auto &item : m_itemRefs)
        {
            if(item->process())
                anyItemActivated = true;

        }
        ImGui::EndChild();
    }
    return anyItemActivated;
}

void ebox::Child::add(std::unique_ptr<ebox::Control> control)
{
    m_items.push_back(std::move(control));
}

void ebox::Child::addReference(ebox::Control *ref)
{
    m_itemRefs.push_back(ref);
}

void ebox::Child::setFlags(const ebox::FormFlags &formFlags)
{
    m_flags = formFlags;
}

void ebox::Child::addFlag(const ebox::FormFlags &formFlag)
{
    m_flags |= formFlag;
}

void ebox::Child::removeFlag(const ebox::FormFlags &formFlag)
{
    m_flags &= ~formFlag;
}

bool ebox::Child::hasFlag(const ebox::FormFlags &formFlag)
{
    return ((m_flags & formFlag) == formFlag) ? true : false;
}

ImGuiWindowFlags_ ebox::Child::getFlagsAsImGuiFlags()
{
    return (ImGuiWindowFlags_)m_flags;
}

ebox::FormFlags ebox::Child::getFlags() const
{
    return m_flags;
}

const sf::Vector2<int> &ebox::Child::getSize() const
{
    return m_size;
}

void ebox::Child::setSize(const sf::Vector2<int> &size)
{
    m_size = size;
}

bool ebox::Child::hasBorder() const
{
    return m_hasBorder;
}

void ebox::Child::setHasBorder(bool hasBorder)
{
    m_hasBorder = hasBorder;
}



