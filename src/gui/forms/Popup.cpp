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
    m_formIsHovered = false;
    m_formIsActive = false;

    if(!m_isVisible)
        return false;

    m_previousWindowPosition = m_currentWindowPosition;
    m_previousWindowSize = m_currentWindowSize;

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
        m_currentWindowSize = ImGui::GetWindowSize();
        m_currentWindowPosition = ImGui::GetWindowPos();
        m_position = {(int)m_currentWindowPosition.x, (int) m_currentWindowPosition.y};

        if (ImGui::IsWindowHovered())
        {
            m_formIsHovered = true;
        }
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
        {
            m_formIsActive = true;
        }

        if(m_currentWindowSize != m_previousWindowSize) onWindowResize();
        if(m_currentWindowPosition != m_previousWindowPosition) onMoved();

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