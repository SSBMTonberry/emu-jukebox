//
// Created by robin on 17.02.19.
//

#ifndef EMU_JUKEBOX_AUDIOPLAYERFORM_H
#define EMU_JUKEBOX_AUDIOPLAYERFORM_H

#include "../gui/forms/Form.h"
#include "../gui/controls/Button.h"
#include "../gui/controls/DragFloat.h"
#include "../../content/files_mapper.h"
#include "../gui/controls/ImageButton.h"
#include "../audio/EmuStream.h"
#include "../gui/controls/Label.h"
#include "../gui/controls/Textbox.h"
#include "../widgets/FileDialog.h"
#include "../gui/controls/InputFloat.h"
#include "../audio/EmuFileInfo.h"
#include "../gui/controls/Visualizer.h"
#include "../managers/Hotkeys.h"

#include "../data/IniFile.h"

namespace ebox
{
    class AudioPlayerForm : public Form
    {
        typedef Hotkeys::PlayerHotkey key;
        public:
            enum class AudioPlayerState
            {
                Stopped = 0,
                Play = 1,
                Pause = 2
            };
            typedef std::function<bool(AudioPlayerForm* )> func_audioplayer; //OnCancel(), for instance
            typedef std::function<bool(AudioPlayerForm*, EmuStream *)> func_audioplayertrack;

            AudioPlayerForm(const string &id, const string &title, const string &imguiId);

            AudioPlayerForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const string &id, const string &title,
                            const string &imguiId);

            void handleEvents() override;

            bool createStream(const EmuFileInfo &info);
            void setStream(std::unique_ptr<EmuStream> stream);
            void setTrack(int trackNo);
            void setIniFile(IniFile *iniFile);


            std::string getStreamId();

            void registerOnPlayCallback(const func_audioplayer &cb);
            void registerOnStopCallback(const func_audioplayer &cb);
            void registerOnPauseCallback(const func_audioplayer &cb);
            void registerOnNextTrackCallback(const func_audioplayer &cb);
            void registerOnPreviousTrackCallback(const func_audioplayer &cb);
            void registerOnTrackEndedCallback(const func_audioplayertrack &cb);

            //EmuStream connected functions
            void play();
            void stop();
            void pause();

            //EmuStream *getStream() const;

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();

            void processHotkeys();

            void drawAudioPanel();
            void drawAudioVisualizer();
            void drawAudioInfo();
            void drawEqualizer();

            std::string getAudioTimestamp();
            std::string getMillisecondsAsTimeString(int milliseconds);

            //bool m_hasItemsFocused = false;
            AudioPlayerState m_state = AudioPlayerState::Stopped;

            //Callbacks
            std::vector<func_audioplayer> m_callbackOnPlay;
            std::vector<func_audioplayer> m_callbackOnStop;
            std::vector<func_audioplayer> m_callbackOnPause;
            std::vector<func_audioplayer> m_callbackOnNext;
            std::vector<func_audioplayer> m_callbackOnPrevious;
            std::vector<func_audioplayertrack> m_callbackOnTrackEnded;

            //EmuStream *m_stream = nullptr;
            std::unique_ptr<EmuStream> m_stream;
            IniFile *m_iniFile;
            //float m_previousVolume = 100.f;

            ebox::ImageButton m_previousButton {"test_previous_button", files_mapper::gui::ebox::_PREVIOUS_TRACK_16_PNG, files_mapper::gui::ebox::_PREVIOUS_TRACK_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_stopButton {"test_stop_button", files_mapper::gui::ebox::_STOP_16_PNG, files_mapper::gui::ebox::_STOP_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_pauseButton {"test_pause_button", files_mapper::gui::ebox::_PAUSE_16_PNG, files_mapper::gui::ebox::_PAUSE_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_playButton {"test_play_button", files_mapper::gui::ebox::_PLAY_16_PNG, files_mapper::gui::ebox::_PLAY_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_nextButton {"test_next_button", files_mapper::gui::ebox::_NEXT_TRACK_16_PNG, files_mapper::gui::ebox::_NEXT_TRACK_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::DragFloat m_volume {"volume_control", "volume", 0.f, 100.f, 0};
            ebox::InputFloat m_tempo {"tempo_float", "tempo", 0.1, 5, 0.1, 0.3};
            ebox::Visualizer m_visualizer{"visualizer", "viz"};
    };
}

#endif //EMU_JUKEBOX_AUDIOPLAYERFORM_H
