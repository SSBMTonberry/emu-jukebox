//
// Created by robin on 14.07.18.
//

#include "TreeList.h"

ebox::TreeList::TreeList() : Control("undefined", "undefined")
{

}

ebox::TreeList::TreeList(const std::string &id, const std::string &label) : Control(id, label)
{
    m_type = ControlType::TreeList;
}

bool ebox::TreeList::process()
{
    bool isAnyItemActivated = false;
    if(Control::process())
    {
        bool opened = (m_hasParentNode) ? ImGui::TreeNode(m_label.c_str()) : true;

        if(opened)
        {
            processMouseEvents();
            //Child nodes
            for(auto & [pos, item] : m_items)
            {
                if(item.process())
                    isAnyItemActivated = true;
            }
            if(m_hasParentNode)
                ImGui::TreePop();
        }
        else
        {
            ImGui::PushID(m_label.c_str());
            {
                processMouseEvents();
            }
            ImGui::PopID();
        }
        if(ImGui::IsMouseClicked(0))
        {
            m_rightClickContextActivated = false;
        }
    }

    return isAnyItemActivated;
}

/*!
 * Adds a selectable item to the TreeList.
 * ID is automatically generated as a lower-case string of the label
 * @param label The text shown in the TreeList
 * @return The generated Selectable as a pointer
 */
ebox::Selectable* ebox::TreeList::add(const std::string &label)
{
    std::string id = label;
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    //m_items[id] = {id, label};
    //Must be done this way because ebox::Selectable has no empty constructor
    m_items.insert(std::map< std::string, ebox::Selectable>::value_type (id, ebox::Selectable(id, label)));
    return &m_items.find(id)->second;//&m_items[id];
}

/*!
 * Adds a selectable item to the TreeList with an image in the front generated by image data.
 * @param id The ID used to track the object inside a std::map
 * @param label The label of the object shown to the user
 * @param image The image object that is placed in the front of the text of the selectable
 * @return
 */
ebox::Selectable *ebox::TreeList::add(const std::string &id, const std::string &label, const ebox::Image &image)
{
    m_items.insert(std::map< std::string, ebox::Selectable>::value_type (id, ebox::Selectable(id, label, image)));
    return &m_items.find(id)->second;
}

/*!
 * Adds a selectable item to the TreeList with an image in the front generated by image data.
 * ID is automatically generated as a lower-case string of the label
 * @param label The text shown in the TreeList
 * @return The generated Selectable as a pointer
 */
ebox::Selectable* ebox::TreeList::add(const std::string &label, const void *imageData, size_t imageDataSize)
{
    std::string id = label;
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

    m_items.insert(std::map< std::string, ebox::Selectable>::value_type (id, ebox::Selectable(id, label)));
    auto item = &m_items.find(id)->second;
    item->setImage(imageData, imageDataSize, true);
    return item;
}

ebox::Selectable *ebox::TreeList::getItem(const std::string &id)
{
    return &m_items.find(id)->second;
}

/*!
 * Removes an item by its ID
 * @param id The items of the id to remove
 */
bool ebox::TreeList::remove(const std::string &id)
{
    //int i = 0;
    for(std::map<std::string, ebox::Selectable>::iterator it = m_items.begin(); it != m_items.end();it++)
    {
        if(it->first == id)
        {
            m_items.erase(it);
            return true;
        }
    }

    return false;
}

void ebox::TreeList::clear()
{
    m_items.clear();
}

void ebox::TreeList::registerOnChosenCallback(const ebox::TreeList::func_treelist_parent &cb)
{
    m_callbackOnParentClicked.emplace_back(cb);
}

void ebox::TreeList::registerOnRightClickCallback(const ebox::TreeList::func_treelist_parent_rightclick &cb)
{
    m_callbackOnParentRightClicked.emplace_back(cb);
}

void ebox::TreeList::registerOnDoubleClickCallback(const ebox::TreeList::func_treelist_parent &cb)
{
    m_callbackOnParentDoubleClicked.emplace_back(cb);
}

void ebox::TreeList::registerOnChosenContextItemCallback(const ebox::TreeList::func_treelist_parent_chosencontextitem &cb)
{
    m_callbackOnChosenParentContextItem.emplace_back(cb);
}

/*!
 * Creates a context of menuitems used for when the right click context has been activated.
 * This is a fresh context, and will overwrite any potential existing data.
 *
 * @param items Each item is defined as {"id", "label"}
 */
void ebox::TreeList::createRightClickContextItemsAdvanced(
        const std::initializer_list<std::pair<std::string, std::string>> &items)
{
    m_rightClickContextItems.clear();
    for(auto &item : items)
    {
        m_rightClickContextItems.emplace_back(item.first, item.second);
    }
}

/*!
 * An easier way to create right click context, where ID's are automatically set to be the same as label, but in lower-case.
 * @param items
 */
void ebox::TreeList::createRightClickContextItems(const std::initializer_list<std::string> &items)
{
    m_rightClickContextItems.clear();
    for(auto &item : items)
    {
        std::string id = item;
        std::transform(id.begin(), id.end(), id.begin(), ::tolower);
        m_rightClickContextItems.emplace_back(id, item);
    }
}

void ebox::TreeList::processMouseEvents()
{
    if(ImGui::IsItemClicked(1))
    {
        for (auto &callback : m_callbackOnParentRightClicked)
        {
            if (callback(this))
            {
                m_rightClickContextActivated = true;
            }
        }
    }

    if(ImGui::IsItemClicked())
    {
        for (auto &callback : m_callbackOnParentClicked)
            callback(this);
    }

    if(m_rightClickContextActivated)
    {
        //if (ImGui::BeginMenu(m_label.c_str()))
        if(ImGui::BeginPopupContextWindow())
        {
            for(auto &item : m_rightClickContextItems)
            {
                if(item.process())
                {
                    for (auto &callback : m_callbackOnChosenParentContextItem)
                    {
                        callback(this, &item);
                    }
                }
            }
            //ImGui::EndMenu();
            ImGui::EndPopup();
        }
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
    {
        for (auto &callback : m_callbackOnParentDoubleClicked)
        {
            callback(this);
        }
    }
}

std::vector<ebox::Selectable *> ebox::TreeList::getItems()
{
    std::vector<Selectable *> items;
    for(auto & [pos, item] : m_items)
    {
        items.push_back(&item);
    }
    return items;
}

bool ebox::TreeList::hasParentNode() const
{
    return m_hasParentNode;
}

void ebox::TreeList::setHasParentNode(bool hasParentNode)
{
    m_hasParentNode = hasParentNode;
}


