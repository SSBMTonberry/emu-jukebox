//
// Created by robin on 11.01.19.
//

#include "FormManager.h"

ebox::FormManager::FormManager()
{

}

void ebox::FormManager::initialize(sf::RenderWindow *window, EventManager * events, IniFile *iniFile)
{
    ImGui::CreateContext(); //IMGUI 1.60
    m_window = window;
    m_style = &ImGui::GetStyle();
    m_io = &ImGui::GetIO();
    m_events = events;
    m_iniFile = iniFile;

    ImGui::SFML::Init(*m_window);
    //Enable Ctrl+TAB (New in ImGui 1.63)
    //m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Removed - 18.03.2019 - Disabled due to interrupting hotkeys...
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    //Enable docking (New in ImGui 1.66 WIP) - Downloaded 14.10.2018
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    m_filelistForm.setPlaylist(&m_playlistForm);
    m_filelistForm.setAudioPlayer(&m_audioPlayerForm);
    m_filelistForm.setIniFile(m_iniFile);

    m_audioPlayerForm.setIniFile(m_iniFile);


    initializeForms();
}

void ebox::FormManager::initializeForms()
{
    m_forms.push_back(&m_filelistForm);
    m_forms.push_back(&m_playlistForm);
    m_forms.push_back(&m_audioPlayerForm);
}

void ebox::FormManager::update()
{
    for(sf::Event &event : m_events->getAllEvents())
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
    }
    ImGui::SFML::Update(*m_window, m_deltaClock.restart());
}

void ebox::FormManager::draw()
{
    if(m_showImguiDemoWindow)
        ImGui::ShowDemoWindow();

    for(auto const &item : m_forms)
        item->draw();

    SystemLog::get()->process();
}

void ebox::FormManager::showImguiDemoWindow(bool showImguiDemoWindow)
{
    m_showImguiDemoWindow = showImguiDemoWindow;
}

bool ebox::FormManager::showImguiDemoWindow() const
{
    return m_showImguiDemoWindow;
}

void FormManager::handleEvents()
{
    m_audioPlayerForm.handleEvents();
}

void FormManager::setOpened(FormType formType, bool open)
{
    switch(formType)
    {
        case FormType::AudioPlayer:
            m_audioPlayerForm.setOpen(open);
            break;

        case FormType::Files:
            m_filelistForm.setOpen(open);
            break;

        case FormType::Playlist:
            m_playlistForm.setOpen(open);
            break;

        case FormType::SystemLog:
            SystemLog::get()->setOpen(open);
            break;
    }
}

void FormManager::toggleOpened(FormType formType)
{
    setOpened(formType, !isOpened(formType));
}

bool FormManager::isOpened(FormType formType)
{
    switch(formType)
    {
        case FormType::AudioPlayer:
            return m_audioPlayerForm.isOpen();

        case FormType::Files:
            return m_filelistForm.isOpen();

        case FormType::Playlist:
            return m_playlistForm.isOpen();

        case FormType::SystemLog:
            return SystemLog::get()->isOpen();

        default:
            return false;
    }
}

FilelistForm *FormManager::getFilelistForm()
{
    return &m_filelistForm;
}


