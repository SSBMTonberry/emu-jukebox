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
            AudioPlayerForm(const string &id, const string &title, const string &imguiId);

            AudioPlayerForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const string &id, const string &title,
                            const string &imguiId);

            void handleEvents() override;

            void createStream(const EmuFileInfo &info);
            void setStream(std::unique_ptr<EmuStream> stream);

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

            //EmuStream *m_stream = nullptr;
            std::unique_ptr<EmuStream> m_stream;

            ebox::ImageButton m_previousButton {"test_previous_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_stopButton {"test_stop_button", files_mapper::gui::actions::_SUSPEND_PNG, files_mapper::gui::actions::_SUSPEND_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_pauseButton {"test_pause_button", files_mapper::gui::actions::_PAUSE_PNG, files_mapper::gui::actions::_PAUSE_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_playButton {"test_play_button", files_mapper::gui::actions::_EXECUTE_PNG, files_mapper::gui::actions::_EXECUTE_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_nextButton {"test_next_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::InputFloat m_tempo {"tempo_float", "tempo", 0.1, 5, 0.1, 0.3};
    };
}

#endif //EMU_JUKEBOX_AUDIOPLAYERFORM_H
