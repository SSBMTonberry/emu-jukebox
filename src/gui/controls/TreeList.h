//
// Created by robin on 14.07.18.
//

#ifndef EMU_JUKEBOX_TREELIST_H
#define EMU_JUKEBOX_TREELIST_H

#include <map>
#include <vector>
#include <algorithm>
#include "Selectable.h"

namespace ebox
{

    class TreeList : public Control
    {
            typedef std::function<void(TreeList* )> func_treelist_parent;
            typedef std::function<bool(TreeList* )> func_treelist_parent_rightclick;
            typedef std::function<void(TreeList*, MenuItem*)> func_treelist_parent_chosencontextitem;

        public:
            TreeList(const std::string &id, const std::string &label);

            bool process() override;
            ebox::Selectable* add(const std::string &label);
            ebox::Selectable* add(const std::string &id, const std::string &label, const ebox::Image &image);
            ebox::Selectable* add(const std::string &label, const void *imageData, size_t imageDataSize);
            bool remove(const std::string &id);
            void clear();

            void createRightClickContextItemsAdvanced(const std::initializer_list<std::pair<std::string, std::string>> &items);
            void createRightClickContextItems(const std::initializer_list<std::string> &items);

            void registerOnChosenCallback(const func_treelist_parent &cb);
            void registerOnRightClickCallback(const func_treelist_parent_rightclick &cb);
            void registerOnDoubleClickCallback(const func_treelist_parent &cb);
            void registerOnChosenContextItemCallback(const func_treelist_parent_chosencontextitem &cb);

            void setHasParentNode(bool hasParentNode);

            ebox::Selectable * getItem(const std::string &id);
            std::vector<ebox::Selectable *> getItems();
            bool hasParentNode() const;

        protected:
            void processMouseEvents();

            std::vector<func_treelist_parent> m_callbackOnParentClicked; //When you click the TreeList.
            std::vector<func_treelist_parent> m_callbackOnParentDoubleClicked; //When you double-click the TreeList.
            std::vector<func_treelist_parent_rightclick> m_callbackOnParentRightClicked; //When you right click the TreeList
            std::vector<func_treelist_parent_chosencontextitem> m_callbackOnChosenParentContextItem; //When you have chosen a context item of the TreeList (after a right click)

            std::map<std::string, ebox::Selectable> m_items;
            std::vector<ebox::MenuItem> m_rightClickContextItems;
            bool m_rightClickContextActivated = false;

            bool m_hasParentNode = true; //true = Has a tree-node. false = Makes it pretty much work like a list
    };
}

#endif //EMU_JUKEBOX_TREELIST_H
