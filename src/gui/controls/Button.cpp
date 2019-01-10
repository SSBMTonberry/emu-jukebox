//
// Created by robin on 01.01.18.
//

#include "Button.h"

/*!
 * More stack memory friendly constructor.
 * Remember to call create() before running process()
 *
 * @param id
 */
ebox::Button::Button(std::string id) : Control(std::move(id))
{

}


ebox::Button::Button(const std::string &id, const std::string &label, const sf::Vector2<int> &size) : Control(id, label),
                                                                                                     m_size {size}
{
    //m_size = size;
    m_type = ControlType::Button;
}

/*!
 * Only needs to be called when calling the most basic constructor
 * @param label
 * @param size
 */
void ebox::Button::create(const std::string &label, const sf::Vector2<int> &size)
{
    m_label = label;
    m_size = size;
}

/*!
 *
 * @return true if button is pressed, false otherwise
 */
bool ebox::Button::process()
{
    if(Control::process())
    {
        m_isPressed = false;
        bool popColors = false;
        bool toReturn = false;
        if (m_colorIsChanged && !m_useDefaultColor)
        {
            assignColors();
            popColors = true;
        }

        if (ImGui::Button(m_label.c_str(), ImVec2(m_size)))
        {
            m_isPressed = true;
            toReturn = true;

            for(const auto &callback : m_callbackOnPressed)
                callback(this);
        }

        if (popColors && !m_useDefaultColor)
        {
            ImGui::PopStyleColor(3);
        }

        return toReturn;
    }
    return false;
}


bool ebox::Button::isPressed() const
{
    return m_isPressed;
}

void ebox::Button::assignColors()
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(m_color));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(m_colorHovered));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(m_colorPressed));
}

void ebox::Button::setColor(const sf::Color &color, const sf::Color &colorHovered, const sf::Color &colorPressed)
{
    m_color = color;
    m_colorHovered = colorHovered;
    m_colorPressed = colorPressed;
    m_colorIsChanged = true;
}

const std::string &ebox::Button::getCommand() const
{
    return m_command;
}

void ebox::Button::setCommand(const std::string &command)
{
    m_command = command;
}

void ebox::Button::registerOnPressedCallback(const std::function<void(ebox::Button*)> &cb)
{
    m_callbackOnPressed.emplace_back(cb);
}

void ebox::Button::clearCallbacks()
{
    m_callbackOnPressed.clear();
}

const sf::Vector2<int> &ebox::Button::getSize() const
{
    return m_size;
}

void ebox::Button::setSize(const sf::Vector2<int> &size)
{
    m_size = size;
}







