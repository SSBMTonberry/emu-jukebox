//
// Created by robin on 16.01.18.
//

#include "Listbox.h"

ebox::Listbox::Listbox(const std::string &id, const std::string &label, bool multichoice, int itemSpace,
                      int heightInItems) : Control(id, label), m_multichoice {multichoice}, m_itemSpace {itemSpace}
{
    //m_multichoice = multichoice;
    //m_itemSpace = itemSpace;
    m_heightInItems = (heightInItems > -2) ? heightInItems : m_itemSpace;
    m_type = ControlType::Listbox;
}

/*!
 *
 * @return true if anything is selected
 */
bool ebox::Listbox::process()
{
    if(Control::process())
    {
        //auto localItems = getLocalItems();
        if(!m_hasLabel)
            ImGui::PushItemWidth(-1);

        ImGui::ListBoxHeader(m_label.c_str(), m_itemSpace, m_heightInItems);
        bool anythingPressed = false;
        for (const auto & [pos, item] : m_items)
        {
            if(item->process())
            {
                ImGui::SetCursorPos({100.f, 100.f});
                if(!m_multichoice)
                    manageItem(item.get());

                anythingPressed = true;
            }
        }
        ImGui::ListBoxFooter();

        if(!m_hasLabel)
            ImGui::PopItemWidth();

        return anythingPressed;
    }

    return false;
}

void ebox::Listbox::manageItem(Selectable *item)
{
    for (const auto & [pos, value] : m_items)
    {
        bool isSelected = (value.get() == item) ? true : false;
        value->setSelected(isSelected);
    }
}

int ebox::Listbox::getCurrentItem() const
{
    return m_currentItem;
}

/*const char ** ebox::Listbox::getLocalItems()
{
    const char * items[m_items.size()];

    for(int i = 0; i < m_items.size(); i++)
    {
        items[i] = m_items[i].c_str();
    }

    return items;
}*/

void ebox::Listbox::addValue(const int &id, const std::string &value)
{
    std::string valueId = fmt::format("{0}_{1}", m_label, id);
    m_items[id] = std::make_unique<ebox::Selectable>(valueId, value);
}

void ebox::Listbox::addValues(const std::initializer_list<std::pair<size_t, std::string>> &values)
{
    for(const auto & item : values)
    {
        std::string id = fmt::format("{0}_{1}", m_label, item.first);
        m_items[item.first] = std::make_unique<ebox::Selectable>(id, item.second);
    }
}

size_t ebox::Listbox::getItemSpace() const
{
    return m_itemSpace;
}

void ebox::Listbox::setItemSpace(size_t itemSpace)
{
    m_itemSpace = itemSpace;
}

bool ebox::Listbox::hasLabel() const
{
    return m_hasLabel;
}

void ebox::Listbox::setHasLabel(bool hasLabel)
{
    m_hasLabel = hasLabel;
}

