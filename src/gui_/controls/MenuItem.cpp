//
// Created by robin on 24.01.18.
//

#include "MenuItem.h"

ebox::MenuItem::MenuItem(const std::string &id, const std::string &label, std::unique_ptr<ebox::Image> image) : Control(id, label)
{
    m_type = ControlType::MenuItem;
    if(image != nullptr)
    {
        m_useImageRef = false;
        m_image = std::move(image);
    }
}

ebox::MenuItem::MenuItem(const std::string &id, const std::string &label, ebox::Image *image) : Control(id, label)
{
    m_type = ControlType::MenuItem;
    if(image != nullptr)
    {
        m_useImageRef = true;
        m_imageRef = image;
    }
}

bool ebox::MenuItem::process()
{
    m_isPressed = false;
    if(Control::process())
    {
        if(!m_useImageRef && m_image != nullptr)
        {
            m_image->process();
            ImGui::SameLine();
        }
        else if(m_useImageRef && m_imageRef != nullptr)
        {
            m_imageRef->process();
            ImGui::SameLine();
        }

        if(ImGui::MenuItem(m_label.c_str(), m_shortcut.c_str(), m_isSelected, m_isEnabled))
        {
            /*m_isPressed = true;
            for (auto &callback : m_callbackOnChosen)
                callback(this);*/

        }

        if(ImGui::IsItemHovered())
        {
            if(ImGui::IsMouseDoubleClicked(0))
            {
                for (auto &callback : m_callbackOnDoubleClick)
                {
                    callback(this);
                }
            }
            //In some contexts, ImGui::MenuItem will not return true when pressed, so make sure to specifically check it it has been left-clicked
            if(ImGui::IsItemClicked(0) && !m_isPressed)
            {
                m_isPressed = true;
                for (auto &callback : m_callbackOnChosen)
                    callback(this);
            }

            if(ImGui::IsMouseClicked(1))
            {
                for (auto &callback : m_callbackOnRightClick)
                {
                    if (callback(this))
                    {

                    }
                }
            }
            //BeginPopupContextItem() is activated when last item is right-clicked. We only use it to call the callbacks
            /*if (ImGui::BeginPopupContextItem(m_propertyTitle.c_str()))
            {
                bool openPopup = false;
                for (auto &callback : m_callbackOnRightClick)
                {
                    if (callback(this))
                        openPopup = true;
                }

                if (!openPopup)
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }*/
        }
    }

    return m_isPressed;
}

/*!
 *
 * @return If menu item has been pressed. Does not reset the variable so this is true until it's setto be otherwise
 */
bool ebox::MenuItem::isPressed() const
{
    return m_isPressed;
}

bool ebox::MenuItem::isSelected() const
{
    return m_isSelected;
}

void ebox::MenuItem::setIsPressed(bool isPressed)
{
    m_isPressed = isPressed;
}

/*!
 * Checks if the menu item is pressed, returns true if it has been, then resets the variable to false.
 * @return
 */
 [[deprecated("Register a callback instead")]]
bool ebox::MenuItem::handlePressEvent()
{
    bool originalValue = m_isPressed;
    if(m_isPressed)
        m_isPressed = false;

    return originalValue;
}

const std::string &ebox::MenuItem::getShortcut() const
{
    return m_shortcut;
}

void ebox::MenuItem::setShortcut(const std::string &shortcut)
{
    m_shortcut = shortcut;
}

void ebox::MenuItem::setImage(std::unique_ptr<ebox::Image> image)
{
    m_image = std::move(image);
    m_useImageRef = false;
}

void ebox::MenuItem::setImageRef(ebox::Image * image)
{
    m_imageRef = image;
    m_useImageRef = true;
}

void ebox::MenuItem::registerOnChosenCallback(const func_menuitem &cb)
{
    m_callbackOnChosen.emplace_back(cb);
}

void ebox::MenuItem::registerOnRightClickCallback(const func_onrightclick &cb)
{
    m_callbackOnRightClick.emplace_back(cb);
}

void ebox::MenuItem::registerOnDoubleClickCallback(const ebox::MenuItem::func_menuitem &cb)
{
    m_callbackOnDoubleClick.emplace_back(cb);
}

void ebox::MenuItem::setIsSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

