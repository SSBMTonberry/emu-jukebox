//
// Created by robin on 14.01.19.
//

#include "ClipboardManager.h"

ClipboardManager::ClipboardManager()
{
    m_lastImGuiClipboardChange = high_resolution_clock::now();

    //sf::String osStr = sf::Clipboard::getString();
    //m_lastOsClipboardValue = osStr;

    m_lastOsClipboardChange = high_resolution_clock::now();
}

void ClipboardManager::update()
{
    bool valuesHasBeenChanged = false;
    //string osStr = "";
    string osStr;

    sf::String osSfStr = sf::Clipboard::getString();
    osStr = ws2s(osSfStr.toWideString());

    const char * imguiCharPtr = ImGui::GetClipboardText();
    string imguiStr = (imguiCharPtr == nullptr) ? "" : imguiCharPtr;

    //If changes in clipboard related to OS
    if(m_lastOsClipboardValue != osStr)
    {
        m_lastOsClipboardValue = osStr;
        m_lastOsClipboardChange = high_resolution_clock::now();
        valuesHasBeenChanged = true;
    }

    if(imguiStr != m_lastImguiClipboardValue)
    {
        m_lastImguiClipboardValue = imguiStr;
        m_lastImGuiClipboardChange = high_resolution_clock::now();
        valuesHasBeenChanged = true;
    }

    if(valuesHasBeenChanged)
    {
        if (m_lastOsClipboardChange > m_lastImGuiClipboardChange && m_lastOsClipboardValue != m_lastImguiClipboardValue)
        {
            m_lastImguiClipboardValue = m_lastOsClipboardValue;
            ImGui::SetClipboardText(m_lastOsClipboardValue.c_str());
        }
        else if(m_lastImGuiClipboardChange > m_lastOsClipboardChange && m_lastOsClipboardValue != m_lastImguiClipboardValue)
        {
            sf::Clipboard::setString(s2ws(m_lastImguiClipboardValue));//m_lastImguiClipboardValue);
        }
    }
}

std::string ClipboardManager::ws2s(const std::wstring &s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(s);
}

std::wstring ClipboardManager::s2ws(const std::string &ws)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(ws);
}