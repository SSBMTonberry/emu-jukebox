//
// Created by robin on 12.01.19.
//

#ifndef EMU_JUKEBOX_AUDIOTESTFORM_H
#define EMU_JUKEBOX_AUDIOTESTFORM_H

#include "../gui/forms/Form.h"
#include "../gui/controls/Button.h"
#include "../../content/files_mapper.h"
#include "../gui/controls/ImageButton.h"
#include "../audio/EmuStream.h"
#include "../gui/controls/Label.h"
#include "../gui/controls/Textbox.h"

#if MSVC
    #include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
    #if __MINGW64_VERSION_MAJOR > 5
        #include <filesystem>
        namespace fs = std::filesystem;
    #else
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#elif APPLE
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #if __GNUC__ < 8 //GCC major version less than 8
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #else
        #include <filesystem>
        namespace fs = std::filesystem;
    #endif
#endif

namespace ebox
{
    class AudioTestForm : public Form
    {
        public:
            AudioTestForm(const std::string &id, const std::string &title, const std::string &imguiId = "");

            AudioTestForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                          const std::string &imguiId = "");

        protected:
            bool customDraw() override;

        private:
            void initialize();

            void drawAudioPanel();
            void drawAudioButtons();
            void drawAudioInfo();

            EmuStream m_stream;

            ebox::ImageButton m_previousButton {"test_previous_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_stopButton {"test_stop_button", files_mapper::gui::actions::_SUSPEND_PNG, files_mapper::gui::actions::_SUSPEND_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_pauseButton {"test_pause_button", files_mapper::gui::actions::_PAUSE_PNG, files_mapper::gui::actions::_PAUSE_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_playButton {"test_play_button", files_mapper::gui::actions::_EXECUTE_PNG, files_mapper::gui::actions::_EXECUTE_PNG_SIZE, sf::Vector2i(30, 30)};
            ebox::ImageButton m_nextButton {"test_next_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};

            //Audio buttons
            ebox::Button m_ayButton {"test_btn_ay", "Test Amstrad CPC (AY)", {200, 30}};
            ebox::Button m_gbsButton {"test_btn_gbs", "Test Gameboy (GBS)", {200, 30}};
            ebox::Button m_gymButton {"test_btn_gym", "Sega Mega Drive (GYM)", {200, 30}};
            ebox::Button m_hesButton {"test_btn_hes", "NEC TurboGrafx-16 (HES)", {200, 30}};
            ebox::Button m_kssButton {"test_btn_kss", "MSX Home Computer (KSS)", {200, 30}};
            ebox::Button m_nsfButton {"test_btn_nsf", "Nintendo NES (NSF)", {200, 30}};
            ebox::Button m_nsfeButton {"test_btn_nsfe", "Nintendo NES (NSFE)", {200, 30}};
            ebox::Button m_sapButton {"test_btn_sap", "Atari (SAP)", {200, 30}};
            ebox::Button m_spcButton {"test_btn_spc", "Super NES (SPC)", {200, 30}};
            ebox::Button m_vgmButton {"test_btn_vgm", "Video Game Music (VGM)", {200, 30}};

            ebox::Label m_loadFromFileLabel {"load_from_file", "From file:", "From file:", LabelType::OnlyLabel};
            ebox::Textbox m_loadFromFileText {"load_from_file_text", "", 150};
    };
}

#endif //EMU_JUKEBOX_AUDIOTESTFORM_H
