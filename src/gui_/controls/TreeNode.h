//
// Created by robin on 19.01.18.
//

#ifndef EMU_JUKEBOX_TREENODE_H
#define EMU_JUKEBOX_TREENODE_H

#include <map>
#include "Control.h"

namespace ebox
{
    class TreeNode : public Control
    {
        public:
            enum class NodeType : unsigned
            {
                CollapsingHeader = 0,
                TreeNode = 1
            };

            TreeNode(const std::string &id, const std::string &label, NodeType nodeType);
            bool process() override;

            void add(std::unique_ptr<Control> control);
            void addReference(ebox::Control *ref);

            template <typename T>
            T * getControl(const std::string &id);
            template <typename T>
            T * getControlReference(const std::string &id);

        protected:
            NodeType m_nodeType = NodeType::CollapsingHeader;
            std::vector<std::unique_ptr<ebox::Control>> m_controls;
            std::vector<ebox::Control *> m_controlRefs; //Pointers to items owned by something else

    };

    template<typename T>
    T * ebox::TreeNode::getControl(const std::string &id)
    {
        ebox::Control *control = nullptr;
        for(auto & item : m_controls)
        {
            if(item->getId().compare(id) == 0)
                control = item.get();
        }

        if(control == nullptr)
            return nullptr;

        T * reference = static_cast<T*>(control);
        return reference;
    }

    template<typename T>
    T * ebox::TreeNode::getControlReference(const std::string &id)
    {
        ebox::Control *control = nullptr;
        for(auto & item : m_controlRefs)
        {
            if(item->getId().compare(id) == 0)
                control = item;
        }

        if(control == nullptr)
            return nullptr;

        T * reference = static_cast<T*>(control);
        return reference;
    }
}

#endif //EMU_JUKEBOX_TREENODE_H
