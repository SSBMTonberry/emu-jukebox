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
//#include "pmgui.h"
//#include <imgui/imgui_internal.h>
//#include "../gui/controls/MenuBar.h"
//#include "../gui/controls/MenuItemCollection.h"
#include "../../content/files_mapper.h"
#include "Hotkeys.h"
#include "../data/IniFile.h"
#include "../popups/PreferencesPopup.h"
#include "../data/PlaylistFile.h"
#include "../popups/EmuFileExporterPopup.h"
#include "../popups/AboutPopup.h"

#include "../misc/Math.hpp"

namespace ebox
{
    class ProgramManager
    {
        public:
            ProgramManager(int argc, char **argv, char** envp);
            void initialize(const std::string &title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
            void run();

        private:
            sf::Vector2<uint32_t> getResolution();

            void initializeArgs(int argc, char **argv, char** envp);
            bool initializeFiles();

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

            void applyIniFileToProgram();

            void onChosenMenuItem(pmgui::MenuItem *sender);
			void onFileChosen(const fs::path& path); //(const std::string &path);
			void onFolderChosen(const fs::path& path); //(const std::string &path);
            void onSavePlaylist(const fs::path& path); //(const std::string &path);
            void onOpenPlaylist(const fs::path& path); //(const std::string &path);
            void onChangedPreferences(PreferencesPopup *sender);

            void updateViewMenu();
            void openExportPopup();

            static const std::string DOCK_ROOT_ID;
            static const std::string DOCKSPACE_ID;

            pmgui::MenuBar m_menu {"main_menubar", true};

            pmgui::MenuItemCollection m_menuFile {"main_file", "File"};
            pmgui::MenuItem m_menuOpenFolder {"main_file_open_folder", "Open Folder"};
            pmgui::MenuItem m_menuOpenFile {"main_file_open_file", "Open File"};
            pmgui::MenuItem m_menuSavePlaylist {"main_file_save_playlist", "Save Playlist"};
            pmgui::MenuItem m_menuOpenPlaylist {"main_file_open_playlist", "Open Playlist"};
            pmgui::MenuItem m_menuQuit {"main_file_quit", "Quit"};

            pmgui::MenuItemCollection m_menuSettings {"main_settings", "Settings"};
            pmgui::MenuItem m_menuSettingsReset {"main_settings_reset", "Reset Layout"};
            pmgui::MenuItem m_menuSettingsPreferences {"main_settings_preferences", "Preferences"};

            pmgui::MenuItemCollection m_menuView {"main_view", "View"};
            pmgui::MenuItem m_menuViewFiles {"main_view_files", "Files"};
            pmgui::MenuItem m_menuViewPlaylist {"main_view_playlist", "Playlist"};
            pmgui::MenuItem m_menuViewSystemlog {"main_view_systemlog", "System log"};
            pmgui::MenuItem m_menuViewAudioPlayer {"main_view_audioplayer", "Audio Player"};

            pmgui::MenuItemCollection m_menuTools {"main_tools", "Tools"};
            pmgui::MenuItem m_menuToolsExport {"main_tools_export", "Export to audio file..."};

            pmgui::MenuItemCollection m_menuHelp {"main_help", "Help"};
            pmgui::MenuItem m_menuHelpAbout {"main_help_about", "About"};

            //Images
            pmgui::Image m_openFolderImage {"img_open_folder", files_mapper::gui::general::_OPENPROJECT_PNG, files_mapper::gui::general::_OPENPROJECT_PNG_SIZE};
            pmgui::Image m_openFileImage {"img_open_file", files_mapper::gui::filetypes::_TEXT_PNG, files_mapper::gui::filetypes::_TEXT_PNG_SIZE};
            pmgui::Image m_savePlaylistImage {"img_save_playlist", files_mapper::gui::actions::_QUICKLIST_PNG, files_mapper::gui::actions::_QUICKLIST_PNG_SIZE};
            pmgui::Image m_openPlaylistImage {"img_open_playlist", files_mapper::gui::actions::_PROPERTIES_PNG, files_mapper::gui::actions::_PROPERTIES_PNG_SIZE};
            pmgui::Image m_resetLayoutImage {"img_reset_layout", files_mapper::gui::debugger::_RESTORELAYOUT_PNG, files_mapper::gui::debugger::_RESTORELAYOUT_PNG_SIZE};
            pmgui::Image m_preferencesImage {"img_preferences", files_mapper::gui::general::_GEARPLAIN_DARK_PNG, files_mapper::gui::general::_GEARPLAIN_DARK_PNG_SIZE};
            pmgui::Image m_imgQuit {"img_quit", files_mapper::gui::actions::_EXIT_PNG, files_mapper::gui::actions::_EXIT_PNG_SIZE};
            pmgui::Image m_imgExport {"img_export", files_mapper::gui::misc::_EXPORT_PNG, files_mapper::gui::misc::_EXPORT_PNG_SIZE};
            pmgui::Image m_imgAbout {"img_about", files_mapper::gui::general::_BALLOONINFORMATION_PNG, files_mapper::gui::general::_BALLOONINFORMATION_PNG_SIZE};

            //File dialogs
            pmgui::FileDialog m_fileDialogFile { pmgui::DialogType::OpenFile, "main_file_dialog_file", "Choose a file", false};
            pmgui::FileDialog m_fileDialogFolder { pmgui::DialogType::OpenDirectory, "main_file_dialog_folder", "Choose a folder", false};
            pmgui::FileDialog m_fileDialogSavePlaylist { pmgui::DialogType::SaveFile, "main_file_dialog_save_playlist", "Save playlist", false};
            pmgui::FileDialog m_fileDialogOpenPlaylist { pmgui::DialogType::OpenFile, "main_file_dialog_open_playlist", "Open playlist", false};

            PreferencesPopup m_preferences {"preferences_popup", "Preferences"};
            EmuFileExporterPopup m_fileExporter {"file_exporter_popup", "Export to audio file"};
            AboutPopup m_about {"about_popup", "About"};

            bool m_firstRun = true; //Used to make stuff happen on first run
            //bool m_itemChosenOnStartup = false;
            sf::RenderWindow m_window;
            //pmgui::EventManager m_events;
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
