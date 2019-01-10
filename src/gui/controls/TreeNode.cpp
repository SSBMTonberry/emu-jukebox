//
// Created by robin on 19.01.18.
//

#include "TreeNode.h"

ebox::TreeNode::TreeNode(const std::string &id, const std::string &label, NodeType nodeType)
        : Control(id, label), m_nodeType {nodeType}
{
    //m_nodeType = nodeType;
    m_type = ControlType::TreeNode;
}

bool ebox::TreeNode::process()
{
    bool isAnyItemActivated = false;
    if(Control::process())
    {
        switch(m_nodeType)
        {
            case NodeType::CollapsingHeader:
                if(ImGui::CollapsingHeader(m_label.c_str()))
                {
                    ImGui::PushID(m_label.c_str());
                    for (const auto &item : m_controls)
                    {
                        if (item->process())
                        {
                            isAnyItemActivated = true;
                        }
                    }
                    for (const auto &item : m_controlRefs)
                    {
                        if (item->process())
                        {
                            isAnyItemActivated = true;
                        }
                    }
                    ImGui::PopID();
                }
                break;

            case NodeType::TreeNode:
                if(ImGui::TreeNode(m_label.c_str()))
                {
                    for (const auto &item : m_controls)
                    {
                        if (item->process())
                        {
                            isAnyItemActivated = true;
                        }
                    }
                    for (const auto &item : m_controlRefs)
                    {
                        if (item->process())
                        {
                            isAnyItemActivated = true;
                        }
                    }
                    ImGui::TreePop();
                }
                break;
        }
    }

    return isAnyItemActivated;
}

void ebox::TreeNode::add(std::unique_ptr<ebox::Control> control)
{
    m_controls.push_back(std::move(control));
}


void ebox::TreeNode::addReference(ebox::Control *ref)
{
    m_controlRefs.push_back(ref);
}
