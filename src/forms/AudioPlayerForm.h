//
// Created by robin on 17.02.19.
//

#ifndef EMU_JUKEBOX_AUDIOPLAYERFORM_H
#define EMU_JUKEBOX_AUDIOPLAYERFORM_H

#include "../gui/forms/Form.h"
#include "../gui/controls/Button.h"
#include "../../content/files_mapper.h"
#include "../gui/controls/ImageButton.h"
#include "../audio/EmuStream.h"
#include "../gui/controls/Label.h"
#include "../gui/controls/Textbox.h"
#include "../widgets/FileDialog.h"
#include "../gui/controls/InputFloat.h"
#include "../audio/EmuFileInfo.h"

namespace ebox
{
    class AudioPlayerForm : public Form
    {
        public:
            typedef std::function<bool(AudioPlayerForm* )> func_audioplayer; //OnCancel(), for instance
            typedef std::function<bool(AudioPlayerForm*, EmuStream *)> func_audioplayertrack;

            AudioPlayerForm(const string &id, const string &title, const string &imguiId);

            AudioPlayerForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const string &id, const string &title,
                            const string &imguiId);

            void handleEvents() override;

            bool createStream(const EmuFileInfo &info);
            void setStream(std::unique_ptr<EmuStream> stream);

            void registerOnPlayCallback(const func_audioplayer &cb);
            void registerOnStopCallback(const func_audioplayer &cb);
            void registerOnPauseCallback(const func_audioplayer &cb);
            void registerOnNextTrackCallback(const func_audioplayer &cb);
            void registerOnPreviousTrackCallback(const func_audioplayer &cb);
            void registerOnTrackEndedCallback(const func_audioplayertrack &cb);

            EmuStream *getStream() const;

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();

            void drawAudioPanel();

            void drawAudioInfo();
            void drawEqualizer();

            std::string getAudioTimestamp();
            std::string getMillisecondsAsTimeString(int milliseconds);

            bool m_hasItemsFocused = false;

            //Callbacks
            std::vector<func_audioplayer> m_callbackOnPlay;
            std::vector<func_audioplayer> m_callbackOnStop;
            std::vector<func_audioplayer> m_callbackOnPause;
            std::vector<func_audioplayer> m_callbackOnNext;
            std::vector<func_audioplayer> m_callbackOnPrevious;
            std::vector<func_audioplayertrack> m_callbackOnTrackEnded;

            //EmuStream *m_stream = nullptr;
            std::unique_ptr<EmuStream> m_stream;

            ebox::ImageButton m_previousButton {"test_previous_button", files_mapper::gui::ebox::_PREVIOUS_TRACK_16_PNG, files_mapper::gui::ebox::_PREVIOUS_TRACK_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_stopButton {"test_stop_button", files_mapper::gui::ebox::_STOP_16_PNG, files_mapper::gui::ebox::_STOP_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_pauseButton {"test_pause_button", files_mapper::gui::ebox::_PAUSE_16_PNG, files_mapper::gui::ebox::_PAUSE_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_playButton {"test_play_button", files_mapper::gui::ebox::_PLAY_16_PNG, files_mapper::gui::ebox::_PLAY_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_nextButton {"test_next_button", files_mapper::gui::ebox::_NEXT_TRACK_16_PNG, files_mapper::gui::ebox::_NEXT_TRACK_16_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::InputFloat m_tempo {"tempo_float", "tempo", 0.1, 5, 0.1, 0.3};
    };
}

#endif //EMU_JUKEBOX_AUDIOPLAYERFORM_H
