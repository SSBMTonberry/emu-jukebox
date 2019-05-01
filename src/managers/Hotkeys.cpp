//
// Created by robin on 17.03.19.
//

#include "Hotkeys.h"

ebox::Hotkeys::Hotkeys()
{
    generateDefaultHotkeys();
    resetStates();
}

void ebox::Hotkeys::generateDefaultHotkeys()
{
    m_programHotkeys[ProgramHotkey::None] = Hotkey();
    m_programHotkeys[ProgramHotkey::OpenFolder] = Hotkey({sf::Keyboard::Key::LControl, sf::Keyboard::Key::O});
    m_programHotkeys[ProgramHotkey::OpenFile] = Hotkey({sf::Keyboard::Key::LAlt, sf::Keyboard::Key::O});
    m_programHotkeys[ProgramHotkey::CloseApplication] = Hotkey({sf::Keyboard::Key::LControl, sf::Keyboard::Key::Q});
    m_programHotkeys[ProgramHotkey::Copy] = Hotkey({sf::Keyboard::Key::LControl, sf::Keyboard::Key::C});
    m_programHotkeys[ProgramHotkey::Paste] = Hotkey({sf::Keyboard::Key::LControl, sf::Keyboard::Key::V});

    m_playerHotkeys[PlayerHotkey::None] = Hotkey();
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute1] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num1});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute2] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num2});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute3] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num3});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute4] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num4});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute5] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num5});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute6] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num6});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute7] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num7});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute8] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num8});
    m_playerHotkeys[PlayerHotkey::ToggleVoiceMute9] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Num9});
    m_playerHotkeys[PlayerHotkey::PreviousTrack] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Left});
    m_playerHotkeys[PlayerHotkey::NextTrack] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Right});
    m_playerHotkeys[PlayerHotkey::TogglePlayAndPause] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Space});
    m_playerHotkeys[PlayerHotkey::Stop] = Hotkey({sf::Keyboard::LControl, sf::Keyboard::Space});

    m_playlistHotkeys[PlaylistHotkey::None] = Hotkey();
    m_playlistHotkeys[PlaylistHotkey::MoveItemUp] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Up});
    m_playlistHotkeys[PlaylistHotkey::MoveItemDown] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::Down});
    m_playlistHotkeys[PlaylistHotkey::DeleteItem] = Hotkey({sf::Keyboard::Delete});
    m_playlistHotkeys[PlaylistHotkey::PlaySelectedItem] = Hotkey({sf::Keyboard::Return});
    m_playlistHotkeys[PlaylistHotkey::SelectPreviousItem] = Hotkey({sf::Keyboard::Up});
    m_playlistHotkeys[PlaylistHotkey::SelectNextItem] = Hotkey({sf::Keyboard::Down});
    m_playlistHotkeys[PlaylistHotkey::Shuffle] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::S});
    m_playlistHotkeys[PlaylistHotkey::Repeat] = Hotkey({sf::Keyboard::LAlt, sf::Keyboard::R});
    m_playlistHotkeys[PlaylistHotkey::MultiSelect] = Hotkey({sf::Keyboard::LControl});

    m_filelistHotkeys[FilelistHotkey::None] = Hotkey();
    m_filelistHotkeys[FilelistHotkey::DeleteItem] = Hotkey({sf::Keyboard::Delete});
}

void ebox::Hotkeys::resetStates()
{
    //Program
    m_programHotkeyPressed[ProgramHotkey::None] = false;
    m_programHotkeyPressed[ProgramHotkey::OpenFolder] = false;
    m_programHotkeyPressed[ProgramHotkey::OpenFile] = false;
    m_programHotkeyPressed[ProgramHotkey::CloseApplication] = false;
    m_programHotkeyPressed[ProgramHotkey::Copy] = false;
    m_programHotkeyPressed[ProgramHotkey::Paste] = false;

    m_playerHotkeyPressed[PlayerHotkey::None] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute1] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute2] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute3] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute4] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute5] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute6] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute7] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute8] = false;
    m_playerHotkeyPressed[PlayerHotkey::ToggleVoiceMute9] = false;
    m_playerHotkeyPressed[PlayerHotkey::PreviousTrack] = false;
    m_playerHotkeyPressed[PlayerHotkey::NextTrack] = false;
    m_playerHotkeyPressed[PlayerHotkey::TogglePlayAndPause] = false;

    m_playlistHotkeyPressed[PlaylistHotkey::None] = false;
    m_playlistHotkeyPressed[PlaylistHotkey::MoveItemUp] = false;
    m_playlistHotkeyPressed[PlaylistHotkey::MoveItemDown] = false;
    m_playlistHotkeyPressed[PlaylistHotkey::DeleteItem] = false;

    m_filelistHotkeyPressed[FilelistHotkey::None] = false;
    m_filelistHotkeyPressed[FilelistHotkey::DeleteItem] = false;
}

void ebox::Hotkeys::setEventManager(ebox::EventManager *eventManager)
{
    m_events = eventManager;
}

float ebox::Hotkeys::getMouseWheelScroll()
{
    if(!m_isActive)
        return 0.f;

    for(auto const &event : m_events->getAllEvents())
    {
        if(event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            return event.mouseWheelScroll.delta;
    }

    return 0.f;
}

sf::Vector2i ebox::Hotkeys::getMousePosition()
{
    return sf::Mouse::getPosition();
}



bool ebox::Hotkeys::isShiftKeyDown()
{
    if(!m_isActive)
        return false;

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
}

bool ebox::Hotkeys::isControlKeyDown()
{
    if(!m_isActive)
        return false;

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
}

bool ebox::Hotkeys::isAltKeyDown()
{
    if(!m_isActive)
        return false;

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt);
}

bool ebox::Hotkeys::isMouseDown(sf::Mouse::Button button)
{
    if(!m_isActive)
        return false;

    return sf::Mouse::isButtonPressed(button);
}

bool ebox::Hotkeys::isMousePressed(sf::Mouse::Button button)
{
    if(!m_isActive)
        return false;

    if(m_mouseButtonPressed.count(button) == 0)
        m_mouseButtonPressed[button] = false;

    if(sf::Mouse::isButtonPressed(button) && !m_mouseButtonPressed[button])
    {
        m_mouseButtonPressed[button] = true;
        return true;
    }
    else if(!sf::Mouse::isButtonPressed(button))
    {
        m_mouseButtonPressed[button] = false;
    }

    return false;
}

bool ebox::Hotkeys::isProgramHotkeyPressed(ebox::Hotkeys::ProgramHotkey hotkey)
{
    if(m_isActive && m_programHotkeys.count(hotkey) > 0)
    {
        if(m_programHotkeys[hotkey].isPressed() && !m_programHotkeyPressed[hotkey])
        {
            m_programHotkeyPressed[hotkey] = true;
            return true;
        }
        else if(!m_programHotkeys[hotkey].isPressed())
        {
            m_programHotkeyPressed[hotkey] = false;
        }
    }
    return false;
}

bool ebox::Hotkeys::isProgramHotkeyDown(ebox::Hotkeys::ProgramHotkey hotkey)
{
    if(m_isActive && m_programHotkeys.count(hotkey) > 0)
    {
        if(m_programHotkeys[hotkey].isPressed())
            return true;
    }
    return false;
}

bool ebox::Hotkeys::isPlayerHotkeyPressed(ebox::Hotkeys::PlayerHotkey hotkey)
{
    if(m_isActive && m_playerHotkeys.count(hotkey) > 0)
    {
        if(m_playerHotkeys[hotkey].isPressed() && !m_playerHotkeyPressed[hotkey])
        {
            m_playerHotkeyPressed[hotkey] = true;
            return true;
        }
        else if(!m_playerHotkeys[hotkey].isPressed())
        {
            m_playerHotkeyPressed[hotkey] = false;
        }
    }
    return false;
}

bool ebox::Hotkeys::isPlayerHotkeyDown(ebox::Hotkeys::PlayerHotkey hotkey)
{
    if(m_isActive && m_playerHotkeys.count(hotkey) > 0)
    {
        if(m_playerHotkeys[hotkey].isPressed())
            return true;
    }
    return false;
}

bool ebox::Hotkeys::isPlaylistHotkeyPressed(ebox::Hotkeys::PlaylistHotkey hotkey)
{
    if(m_isActive && m_playlistHotkeys.count(hotkey) > 0)
    {
        if(m_playlistHotkeys[hotkey].isPressed() && !m_playlistHotkeyPressed[hotkey])
        {
            m_playlistHotkeyPressed[hotkey] = true;
            return true;
        }
        else if(!m_playlistHotkeys[hotkey].isPressed())
        {
            m_playlistHotkeyPressed[hotkey] = false;
        }
    }
    return false;
}

bool ebox::Hotkeys::isPlaylistHotkeyDown(ebox::Hotkeys::PlaylistHotkey hotkey)
{
    if(m_isActive && m_playlistHotkeys.count(hotkey) > 0)
    {
        if(m_playlistHotkeys[hotkey].isPressed())
            return true;
    }
    return false;
}

bool ebox::Hotkeys::isFilelistHotkeyPressed(ebox::Hotkeys::FilelistHotkey hotkey)
{
    if(m_isActive && m_filelistHotkeys.count(hotkey) > 0)
    {
        if(m_filelistHotkeys[hotkey].isPressed() && !m_filelistHotkeyPressed[hotkey])
        {
            m_filelistHotkeyPressed[hotkey] = true;
            return true;
        }
        else if(!m_filelistHotkeys[hotkey].isPressed())
        {
            m_filelistHotkeyPressed[hotkey] = false;
        }
    }
    return false;
}

bool ebox::Hotkeys::isFilelistHotkeyDown(ebox::Hotkeys::FilelistHotkey hotkey)
{
    if(m_isActive && m_filelistHotkeys.count(hotkey) > 0)
    {
        if(m_filelistHotkeys[hotkey].isPressed())
            return true;
    }
    return false;
}

bool ebox::Hotkeys::isActive() const
{
    return m_isActive;
}

void ebox::Hotkeys::setActive(bool isActive)
{
    m_isActive = isActive;
}
