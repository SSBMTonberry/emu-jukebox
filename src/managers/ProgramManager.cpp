//
// Created by robin on 10.01.19.
//

#include "ProgramManager.h"

ebox::ProgramManager::ProgramManager(int argc, char **argv, char** envp)
{
    initializeArgs(argc, argv, envp);
}

void ebox::ProgramManager::initialize(const std::string &title, const sf::Vector2<uint> &resolution, sf::Uint32 style,
                                      const sf::ContextSettings &settings)
{
    m_window.create(sf::VideoMode(resolution.x, resolution.y), title, style, settings);
    m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y)));
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_window.resetGLStates(); // call it if you only process ImGui. Otherwise not needed.

    m_events.initialize(&m_window);
    m_formManager.initialize(&m_window, &m_events);
}

void ebox::ProgramManager::initializeArgs(int argc, char **argv, char **envp)
{
    m_args.reserve(argc);
    while (*argv)
    {
        m_args.emplace_back(*argv++);
    }

    //Parse environment variables
    while (*envp)
    {
        std::vector<std::string> splitalini = ebox::tools::string::SplitString(*envp, '=');
        if(splitalini.size() > 1)
        {
            m_environmentMap[splitalini[0]] = splitalini[1];
        }
        //*envp++;
        m_environmentList.emplace_back(*envp++);
    }
}

void ebox::ProgramManager::run()
{
    sf::Clock deltaClock;
    while (m_window.isOpen())
    {
        m_window.clear({35, 65, 90, 255});
        update();
        draw();
        handleActions();

        //if(ImGui::IsKeyPressed(sf::Keyboard::Key::Escape))
        //    m_window.close();

        m_window.display();
    }
}

void ebox::ProgramManager::update()
{
    m_clipboard.update();
    m_events.update();
    m_formManager.update();
}

void ebox::ProgramManager::handleActions()
{

}

void ebox::ProgramManager::processHotkeys()
{

}

void ebox::ProgramManager::draw()
{
    m_formManager.draw();
}

