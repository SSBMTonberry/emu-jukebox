//
// Created by robin on 10.01.19.
//

#ifndef EMU_JUKEBOX_PROGRAMMANAGER_H
#define EMU_JUKEBOX_PROGRAMMANAGER_H

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include "../misc/Tools.hpp"
#include "FormManager.h"

namespace ebox
{
    class ProgramManager
    {
        public:
            ProgramManager(int argc, char **argv, char** envp);
            void initialize(const std::string &title, const sf::Vector2<uint> &resolution, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
            void run();

        private:
            void initializeArgs(int argc, char **argv, char** envp);
            void update();
            void handleActions();
            void processHotkeys();
            void draw();

            sf::RenderWindow m_window;
            EventManager m_events;
            FormManager m_formManager;

            std::vector<std::string> m_args;
            std::vector<std::string> m_environmentList;
            std::unordered_map<std::string, std::string> m_environmentMap; //Map of environment variables. first: ID, second: value;
    };
}

#endif //EMU_JUKEBOX_PROGRAMMANAGER_H
