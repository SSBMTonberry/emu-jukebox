//
// Created by robin on 27.12.17.
//

#include "Form.h"

ebox::Form::Form(std::string id, std::string title, std::string imguiId) :
                m_id {std::move(id)}, m_title {std::move(title)}, m_imguiId {std::move(imguiId)}
{

}

ebox::Form::Form(const sf::Vector2<int> &position, const sf::Vector2<int> &size, std::string id,
                std::string title, std::string imguiId) :
                m_position {position}, m_size {size}, m_scaledSize {size}, m_id {std::move(id)}, m_title {std::move(title)}, m_imguiId {std::move(imguiId)},
                m_positionHasBeenChanged {true}
{

}

/*void ebox::Form::update()
{
    for(auto const & item : m_controls)
        item->update();
}*/

/*!
 *
 * @return if any items are changed
 */
bool ebox::Form::draw()
{
    m_formIsHovered = false;
    m_formIsActive = false;
    if(!m_isVisible || !m_open)
        return false;

    m_previousWindowPosition = m_currentWindowPosition;
    m_previousWindowSize = m_currentWindowSize;

    bool anyItemChanged = false;
    if(m_positionHasBeenChanged || m_useLockedPosition)
    {
        ImGui::SetNextWindowPos(ImVec2(m_position));
        ImGui::SetNextWindowSize(ImVec2(m_scaledSize));
        m_positionHasBeenChanged = false;
    }

    ImGui::Begin(getImguiId().c_str(), &m_open, getFlagsAsImGuiFlags());
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

    for(auto const & item : m_controls)
    {
        if(item->process())
            anyItemChanged = true;
    }
    for(const auto &item : m_controlRefs)
    {
        if(item->process())
            anyItemChanged = true;

    }
    onDraw();
    ImGui::End();

    return anyItemChanged;
}

void ebox::Form::handleEvents()
{

}

/*!
 *
 * @return m_title + ### + m_imguiId
 */
std::string ebox::Form::getImguiId()
{
    return (!m_imguiId.empty()) ? fmt::format("{0}###{1}", m_title, m_imguiId) : m_title;
}

void ebox::Form::add(std::unique_ptr<ebox::Control> control)
{
    m_controls.push_back(std::move(control));
}

void ebox::Form::addReference(ebox::Control *ref)
{
    m_controlRefs.push_back(ref);
}

const std::string &ebox::Form::getId() const
{
    return m_id;
}

ebox::FormFlags ebox::Form::getFormFlags() const
{
    return m_flags;
}

void ebox::Form::setFormFlags(const ebox::FormFlags &formFlags)
{
    m_flags = formFlags;
}

void ebox::Form::addFormFlag(const ebox::FormFlags &formFlag)
{
    m_flags |= formFlag;
}

void ebox::Form::removeFormFlag(const ebox::FormFlags &formFlag)
{
    m_flags &= ~formFlag;
}

bool ebox::Form::hasFormFlag(const ebox::FormFlags &formFlag)
{
    return ((m_flags & formFlag) == formFlag) ? true : false;
}

ImGuiWindowFlags_ ebox::Form::getFlagsAsImGuiFlags()
{
    return (ImGuiWindowFlags_)m_flags;
}

bool ebox::Form::isOpen() const
{
    return m_open;
}

void ebox::Form::setOpen(bool open)
{
    m_open = open;
    if(open)
        onOpen();
}

bool ebox::Form::isVisible() const
{
    return m_isVisible;
}

void ebox::Form::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

const sf::Vector2<int> &ebox::Form::getSize() const
{
    return m_size;
}

void ebox::Form::setSize(const sf::Vector2<int> &size)
{
    m_positionHasBeenChanged = true;
    m_size = size;
    m_scaledSize = {(int)(size.x * m_scaleFactor), (int)(size.y * m_scaleFactor)};
}

const sf::Vector2<int> &ebox::Form::getPosition() const
{
    return m_position;
}

void ebox::Form::setPosition(const sf::Vector2<int> &position)
{
    m_position = position;
}

bool ebox::Form::hasImguiId() const
{
    return m_imguiId.empty() ? false : true;
}

bool ebox::Form::onDraw()
{
    return false;
}

const sf::Vector2<size_t> &ebox::Form::getCurrentWindowSize() const
{
    return m_currentWindowSize;
}

const sf::Vector2<size_t> &ebox::Form::getCurrentWindowPosition() const
{
    return m_currentWindowPosition;
}

/*!
 * Used to scale the size of the form and/or its elements.
 * Default is set to 1.
 * @param scaleFactor
 */
float ebox::Form::getScaleFactor() const
{
    return m_scaleFactor;
}

/*!
 * Used to scale the size of the form and/or its elements.
 * Default is set to 1.
 * @param scaleFactor
 */
void ebox::Form::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
    m_scaledSize = {(int)(m_size.x * m_scaleFactor), (int)(m_size.y * m_scaleFactor)};
    m_positionHasBeenChanged = true;
}