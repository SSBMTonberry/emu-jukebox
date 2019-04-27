//
// Created by robin on 22.02.18.
//

#include "Popup.h"

ebox::Popup::Popup(std::string id, std::string title, std::string imguiId)
        : Form(std::move(id), std::move(title), std::move(imguiId))
{
    m_open = false;
}

ebox::Popup::Popup(const sf::Vector2<int> &position, const sf::Vector2<int> &size,
                  std::string id, std::string title, std::string imguiId)
                  : Form(position, size, std::move(id), std::move(title), std::move(imguiId))
{
    m_open = false;
}

/*!
 *
 * @return Returns false if not visible or all items are unchanged. True if any item s changed
 */
bool ebox::Popup::draw()
{
    if(!m_isVisible)
        return false;

    bool anyItemChanged = false;
    if(m_open)
    {
        if(!ImGui::IsPopupOpen(getImguiId().c_str()))
            ImGui::OpenPopup(getImguiId().c_str());

        if(m_positionHasBeenChanged || m_useLockedPosition)
        {
            ImGui::SetNextWindowPos(ImVec2(m_position));
            ImGui::SetNextWindowSize(ImVec2(m_scaledSize));
            m_positionHasBeenChanged = false;
        }
    }

    if (ImGui::BeginPopupModal(getImguiId().c_str(), &m_open, getFlagsAsImGuiFlags()))
    {
        for (auto const &item : m_controls)
        {
            if(item->process())
                anyItemChanged = true;

        }
        for(const auto &item : m_controlRefs)
        {
            if(item->process())
                anyItemChanged = true;
        }
        customDraw();
        /*if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
            m_open = false;
        }*/

        ImGui::EndPopup();
    }

    return anyItemChanged;
}

void ebox::Popup::handleEvents()
{

}