//
// Created by robin on 10.01.19.
//

#ifndef EMU_JUKEBOX_PROGRAMMANAGER_H
#define EMU_JUKEBOX_PROGRAMMANAGER_H

#include "../misc/Tools.hpp"
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include "FormManager.h"
#include "ClipboardManager.h"
#include <imgui/imgui_internal.h>
#include "../gui/controls/MenuBar.h"
#include "../gui/controls/MenuItemCollection.h"
#include "../../content/files_mapper.h"

namespace ebox
{
    class ProgramManager
    {
        public:
            ProgramManager(int argc, char **argv, char** envp);
            void initialize(const std::string &title, const sf::Vector2<uint32_t> &resolution, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
            void run();

        private:
            void initializeArgs(int argc, char **argv, char** envp);
            void update();
            void handleActions();
            void processHotkeys();
            void draw();

            void drawDock();
            void createDock();
            void resetDock();

            void createMenu();

            void registerCallbacks();

            void onChosenMenuItem(MenuItem *sender);

            static const std::string DOCK_ROOT_ID;
            static const std::string DOCKSPACE_ID;

            MenuBar m_menu {"main_menubar", true};

            MenuItemCollection m_menuFile {"main_file", "File"};
            MenuItem m_menuOpenFolder {"main_file_open_folder", "Open Folder"};
            MenuItem m_menuOpenFile {"main_file_open_file", "Open File"};

            //Images
            Image m_openFolderImage {"img_open_folder", files_mapper::gui::general::_OPENPROJECT_PNG, files_mapper::gui::general::_OPENPROJECT_PNG_SIZE};
            Image m_openFileImage {"img_open_file", files_mapper::gui::filetypes::_TEXT_PNG, files_mapper::gui::filetypes::_TEXT_PNG_SIZE};

            sf::RenderWindow m_window;
            EventManager m_events;
            FormManager m_formManager;
            ClipboardManager m_clipboard;
            std::vector<std::string> m_args;
            std::vector<std::string> m_environmentList;
            std::unordered_map<std::string, std::string> m_environmentMap; //Map of environment variables. first: ID, second: value;
    };
}

#endif //EMU_JUKEBOX_PROGRAMMANAGER_H
