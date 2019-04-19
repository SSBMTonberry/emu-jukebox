//
// Created by robin on 11.01.19.
//

#ifndef EMU_JUKEBOX_FORMMANAGER_H
#define EMU_JUKEBOX_FORMMANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "EventManager.h"
#include "../gui/forms/Form.h"
//#include "../forms/AudioTestForm.h"
#include "../forms/AudioPlayerForm.h"
#include "../forms/FilelistForm.h"
#include "../forms/PlaylistForm.h"
#include "../forms/SystemLog.h"

namespace ebox
{
    enum class FormType : unsigned
    {
        Playlist = 0,
        Files = 1,
        SystemLog = 2,
        AudioPlayer = 3
    };

    class FormManager
    {
        public:
            FormManager();
            void initialize(sf::RenderWindow *window, EventManager * events, IniFile *iniFile);

            void showImguiDemoWindow(bool showImguiDemoWindow);

            bool showImguiDemoWindow() const;

            void update();
            void draw();
            void handleEvents();

            void setOpened(FormType formType, bool open);
            void toggleOpened(FormType formType);
            bool isOpened(FormType formType);

            FilelistForm * getFilelistForm();
            PlaylistForm * getPlaylistForm();
            void shutdown();

        private:
            void initializeForms();

            std::vector<ebox::Form *> m_forms;

            FilelistForm m_filelistForm {"filelist_form", "Files", FilelistForm::ID};
            PlaylistForm m_playlistForm {"playlist_form", "Playlist", PlaylistForm::ID};
            AudioPlayerForm m_audioPlayerForm {"audio_player_form", "Audio Player", AudioPlayerForm::ID};
            //AudioTestForm m_audioTestForm {"audio_test_form", "Audio Test", AudioTestForm::ID};
            //AudioTestForm m_audioTestForm {{0,0}, {800, 900}, "audio_test_form", AudioTestForm::ID};

            IniFile *m_iniFile;
            sf::RenderWindow *m_window;
            EventManager *m_events;
            bool m_showImguiDemoWindow;
            ImGuiStyle *m_style = nullptr;
            ImGuiIO *m_io = nullptr;
            sf::Clock m_deltaClock;
    };
}

#endif //EMU_JUKEBOX_FORMMANAGER_H
