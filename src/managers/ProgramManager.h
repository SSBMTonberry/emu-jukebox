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
#include "Hotkeys.h"
#include "../data/IniFile.h"
#include "../popups/PreferencesPopup.h"

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
            void initializeFiles();

            void update();
            void handleActions();
            void processHotkeys();
            void draw();

            void handleClipboard();
            void handleEvents();

            void drawDock();
            void createDock();
            void resetDock();

            void createMenu();

            void registerCallbacks();

            void onChosenMenuItem(MenuItem *sender);
            void onFileChosen(const std::string &path);
            void onFolderChosen(const std::string &path);

            void updateViewMenu();

            static const std::string DOCK_ROOT_ID;
            static const std::string DOCKSPACE_ID;

            MenuBar m_menu {"main_menubar", true};

            MenuItemCollection m_menuFile {"main_file", "File"};
            MenuItem m_menuOpenFolder {"main_file_open_folder", "Open Folder"};
            MenuItem m_menuOpenFile {"main_file_open_file", "Open File"};
            MenuItem m_menuQuit {"main_file_quit", "Quit"};

            MenuItemCollection m_menuSettings {"main_settings", "Settings"};
            MenuItem m_menuSettingsReset {"main_settings_reset", "Reset Layout"};
            MenuItem m_menuSettingsPreferences {"main_settings_preferences", "Preferences"};

            MenuItemCollection m_menuView {"main_view", "View"};
            MenuItem m_menuViewFiles {"main_view_files", "Files"};
            MenuItem m_menuViewPlaylist {"main_view_playlist", "Playlist"};
            MenuItem m_menuViewSystemlog {"main_view_systemlog", "System log"};
            MenuItem m_menuViewAudioPlayer {"main_view_audioplayer", "Audio Player"};

            //Images
            Image m_openFolderImage {"img_open_folder", files_mapper::gui::general::_OPENPROJECT_PNG, files_mapper::gui::general::_OPENPROJECT_PNG_SIZE};
            Image m_openFileImage {"img_open_file", files_mapper::gui::filetypes::_TEXT_PNG, files_mapper::gui::filetypes::_TEXT_PNG_SIZE};
            Image m_resetLayoutImage {"img_reset_layout", files_mapper::gui::debugger::_RESTORELAYOUT_PNG, files_mapper::gui::debugger::_RESTORELAYOUT_PNG_SIZE};
            Image m_preferencesImage {"img_preferences", files_mapper::gui::general::_GEARPLAIN_DARK_PNG, files_mapper::gui::general::_GEARPLAIN_DARK_PNG_SIZE};
            Image m_imgQuit {"img_quit", files_mapper::gui::actions::_EXIT_PNG, files_mapper::gui::actions::_EXIT_PNG_SIZE};

            //File dialogs
            FileDialog m_fileDialogFile { DialogType::OpenFile, "main_file_dialog_file", "Choose a file", "main_file_dialog_file"};
            FileDialog m_fileDialogFolder { DialogType::OpenDirectory, "main_file_dialog_folder", "Choose a folder", "main_file_dialog_folder" };
            PreferencesPopup m_preferences {"preferences_popup", "Preferences"};

            bool m_firstRun = true; //Used to make stuff happen on first run
            sf::RenderWindow m_window;
            EventManager m_events;
            FormManager m_formManager;
            ClipboardManager m_clipboard;
            std::vector<std::string> m_args;
            std::vector<std::string> m_environmentList;
            std::unordered_map<std::string, std::string> m_environmentMap; //Map of environment variables. first: ID, second: value;
            sf::Color m_backgroundColor = {35, 65, 90, 255};

            ebox::Timer m_clipboardDelay;

            IniFile m_iniFile;
    };
}

#endif //EMU_JUKEBOX_PROGRAMMANAGER_H
