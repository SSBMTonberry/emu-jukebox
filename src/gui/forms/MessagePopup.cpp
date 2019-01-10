//
// Created by robin on 27.04.18.
//

#include "MessagePopup.h"

ebox::MessagePopup::MessagePopup(std::string id, std::string title, const MessagePopupType &popupType,
                                std::string imguiId) : Popup(std::move(id), std::move(title), std::move(imguiId)),
                                m_messagePopupType {popupType}
{
    initialize();
    addReferences();
}

ebox::MessagePopup::MessagePopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, std::string id,
                                std::string title, const MessagePopupType &popupType,
                                std::string imguiId) : Popup(position, size, std::move(id), std::move(title), std::move(imguiId)),
                                m_messagePopupType {popupType}
{
    initialize();
    addReferences();
}


void ebox::MessagePopup::initialize()
{
    m_msgText.create(m_message, "", LabelType::OnlyLabel);
    setFormFlags(FormFlags::NoResize | FormFlags::NoScrollbar | FormFlags::NoTitleBar);
    m_btn1.create("Button 1", {(int)(m_size.x * 0.2), (int)(m_size.y * 0.15)});
    m_btn2.create("Button 2", {(int)(m_size.x * 0.2), (int)(m_size.y * 0.15)});
    m_btn3.create("Button 3", {(int)(m_size.x * 0.2), (int)(m_size.y * 0.15)});
    m_btn2.setOnSameLine(true);
    m_btn3.setOnSameLine(true);

    m_btnChildMid.setOnSameLine(true);
    m_messageChild.setSize({-1, (int)(m_size.y * 0.65f)});

    int fillerSizeX = (int)((m_size.x * 0.435f) - (getNumberOfButtons() * (m_btn1.getSize().x / 2)));
    m_btnChildFiller.setSize({fillerSizeX, (int)(m_size.y * 0.2f)}); //(int)(m_size.y * 0.25f)});
    m_btnChildMid.setSize({-1, (int)(m_size.y * 0.2f)});
    initializeButtons();
    //uptr_textbox msgbox = GuiFactory::CreateTextbox("msgbox", "Message", m_maxMessageSize);
}

void ebox::MessagePopup::addReferences()
{
    m_messageGroup.addReference(&m_messageChild);
    m_messageChild.addReference(&m_msgText);
    m_btnGroup.addReference(&m_btnChildFiller);
    m_btnGroup.addReference(&m_btnChildMid);
    m_btnChildMid.addReference(&m_btn1);
    m_btnChildMid.addReference(&m_btn2);
    m_btnChildMid.addReference(&m_btn3);
}


bool ebox::MessagePopup::draw()
{
    if(m_isVisible)
    {
        if(m_open)
        {
            if(!ImGui::IsPopupOpen(getImguiId().c_str()))
                ImGui::OpenPopup(getImguiId().c_str());

            if(m_positionHasBeenChanged || m_useLockedPosition)
            {
                ImGui::SetNextWindowPos(ImVec2(m_position));
                ImGui::SetNextWindowSize(ImVec2(m_size));
                m_positionHasBeenChanged = false;
            }
        }

        if (ImGui::BeginPopupModal(getImguiId().c_str(), &m_open, getFlagsAsImGuiFlags()))
        {
            m_messageGroup.process();
            m_btnGroup.process();
            //m_msgText.process();
            if(m_btn1.isPressed()) onButtonPress(&m_btn1, m_btn1.getCommand());
            if(m_btn2.isPressed()) onButtonPress(&m_btn2, m_btn2.getCommand());
            if(m_btn3.isPressed()) onButtonPress(&m_btn3, m_btn3.getCommand());

            ImGui::EndPopup();
        }
    }
    return m_isVisible;
}



void ebox::MessagePopup::setMessage(const std::string &msg)
{
    m_message = msg;
    m_msgText.setLabel(m_message);
}

const string &ebox::MessagePopup::getMessage() const
{
    return m_message;
}

void ebox::MessagePopup::initializeButtons()
{
    switch(m_messagePopupType)
    {
        case MessagePopupType::Ok:
            m_btn1.setIsVisible(true);
            m_btn1.setLabel("Ok");
            m_btn1.setCommand("Ok");

            m_btn2.setIsVisible(false);
            m_btn3.setIsVisible(false);
            break;

        case MessagePopupType::OkCancel:
            m_btn1.setIsVisible(true);
            m_btn1.setLabel("Ok");
            m_btn1.setCommand("Ok");

            m_btn2.setIsVisible(true);
            m_btn2.setLabel("Cancel");
            m_btn2.setCommand("Cancel");

            m_btn3.setIsVisible(false);
            break;

        case MessagePopupType::YesNo:
            m_btn1.setIsVisible(true);
            m_btn1.setLabel("Yes");
            m_btn1.setCommand("Yes");

            m_btn2.setIsVisible(true);
            m_btn2.setLabel("No");
            m_btn2.setCommand("No");

            m_btn3.setIsVisible(false);
            break;

        case MessagePopupType::YesNoCancel:
            m_btn1.setIsVisible(true);
            m_btn1.setLabel("Yes");
            m_btn1.setCommand("Yes");

            m_btn2.setIsVisible(true);
            m_btn2.setLabel("No");
            m_btn2.setCommand("No");

            m_btn3.setIsVisible(true);
            m_btn3.setLabel("Cancel");
            m_btn3.setCommand("Cancel");
            break;
    }
}

void ebox::MessagePopup::onButtonPress(Button *btn, const std::string &command)
{
    MessagePopupResponse response = MessagePopupResponse::None;
    if(command == "Ok") response = MessagePopupResponse::Ok;
    else if(command == "Yes") response = MessagePopupResponse::Yes;
    else if(command == "No") response = MessagePopupResponse::No;
    else if(command == "Cancel") response = MessagePopupResponse::Cancel;
    else if(m_messagePopupType == MessagePopupType::Custom)
        response = MessagePopupResponse::Custom;

    m_lastResponse = response;

    m_open = false;
    ImGui::CloseCurrentPopup();

    for(const auto & callback: m_callbackOnMsgResponse)
        callback(btn, m_lastResponse);
}

ebox::MessagePopupResponse ebox::MessagePopup::getLastResponse() const
{
    return m_lastResponse;
}

void ebox::MessagePopup::registerOnMsgResponseCallback(const ebox::MessagePopup::func_msg_response &cb)
{
    m_callbackOnMsgResponse.emplace_back(cb);
}

void ebox::MessagePopup::clearCallbacks()
{
    m_callbackOnMsgResponse.clear();
}

void ebox::MessagePopup::changePopupType(const ebox::MessagePopupType &popupType)
{
    m_messagePopupType = popupType;
    initializeButtons();
}

/*!
 * If something is resized, we want the controls to resize as well
 */
void ebox::MessagePopup::refresh()
{
    initialize();
}

/*!
 * Requires MessagePopupType to be Custom to change
 * @param btn1Visible
 * @param btn2Visible
 * @param btn3Visible
 */
void ebox::MessagePopup::setCustomButtonVisibility(bool btn1Visible, bool btn2Visible, bool btn3Visible)
{
    if(m_messagePopupType == MessagePopupType::Custom)
    {
        m_btn1.setIsVisible(btn1Visible);
        m_btn2.setIsVisible(btn2Visible);
        m_btn3.setIsVisible(btn3Visible);
    }
}

void ebox::MessagePopup::setCustomButtonTexts(const string &btn1Text, const string &btn2Text, const string &btn3Text)
{
    if(m_messagePopupType == MessagePopupType::Custom)
    {
        m_btn1.setLabel(btn1Text);
        m_btn2.setLabel(btn2Text);
        m_btn3.setLabel(btn3Text);
    }
}

void ebox::MessagePopup::setCustomButtonCommands(const string &btn1Cmd, const string &btn2Cmd, const string &btn3Cmd)
{
    if(m_messagePopupType == MessagePopupType::Custom)
    {
        m_btn1.setCommand(btn1Cmd);
        m_btn2.setCommand(btn2Cmd);
        m_btn3.setCommand(btn3Cmd);
    }
}

/*!
 *
 * @return Number of visible buttons
 */
size_t ebox::MessagePopup::getNumberOfButtons()
{
    size_t buttons = 0;
    if(m_btn1.isVisible()) ++buttons;
    if(m_btn2.isVisible()) ++buttons;
    if(m_btn3.isVisible()) ++buttons;

    return buttons;
}


