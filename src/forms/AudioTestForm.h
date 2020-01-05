//
// Created by robin on 12.01.19.
//

#ifndef EMU_JUKEBOX_AUDIOTESTFORM_H
#define EMU_JUKEBOX_AUDIOTESTFORM_H

//#include "../gui/forms/Form.h"
//#include "../gui/controls/Button.h"
#include "pmgui.h"
#include "../../content/files_mapper.h"
//#include "../gui/controls/ImageButton.h"
#include "../audio/EmuStream.h"
//#include "../gui/controls/Label.h"
//#include "../gui/controls/Textbox.h"
//#include "../widgets/FileDialog.h"
//#include "../gui/controls/InputFloat.h"

//#if MSVC
//    #include <filesystem>
//    namespace fs = std::filesystem;
//#elif MINGW
//    #if __MINGW64_VERSION_MAJOR > 6
//        #include <filesystem>
//        namespace fs = std::filesystem;
//    #else
//        #include <experimental/filesystem>
//        namespace fs = std::experimental::filesystem;
//    #endif
//#elif APPLE
//    #include <experimental/filesystem>
//    namespace fs = std::experimental::filesystem;
//#else
//    #if __GNUC__ < 8 //GCC major version less than 8
//        #include <experimental/filesystem>
//        namespace fs = std::experimental::filesystem;
//    #else
//        #include <filesystem>
//        namespace fs = std::filesystem;
//    #endif
//#endif

namespace ebox
{
    class AudioTestForm : public pmgui::Form
    {
        public:
            AudioTestForm(const std::string &id, const std::string &title);

            AudioTestForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title);

            void handleEvents() override;

            static const std::string ID;

        protected:
            bool onDraw() override;

        private:
            void initialize();

            void drawAudioPanel();
            void drawAudioButtons();
            void drawAudioInfo();
            void drawEqualizer();

			void onFileChosen(const fs::path& path); //(const std::string &path);

            EmuStream m_stream;
            FileDialog m_fileDialog { DialogType::OpenFile, "audio_test_file_dialog", "Choose a file" };

            bool m_hasItemsFocused = false;

            pmgui::ImageButton m_previousButton {"test_previous_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_stopButton {"test_stop_button", files_mapper::gui::actions::_SUSPEND_PNG, files_mapper::gui::actions::_SUSPEND_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_pauseButton {"test_pause_button", files_mapper::gui::actions::_PAUSE_PNG, files_mapper::gui::actions::_PAUSE_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_playButton {"test_play_button", files_mapper::gui::actions::_EXECUTE_PNG, files_mapper::gui::actions::_EXECUTE_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::ImageButton m_nextButton {"test_next_button", files_mapper::gui::actions::_RERUN_PNG, files_mapper::gui::actions::_RERUN_PNG_SIZE, sf::Vector2i(30, 30)};
            pmgui::InputFloat m_tempo {"tempo_float", "tempo", 0.1, 5, 0.1, 0.3};

            //Audio buttons
            pmgui::Button m_ayButton {"test_btn_ay", "Test Amstrad CPC (AY)", {200, 30}};
            pmgui::Button m_gbsButton {"test_btn_gbs", "Test Gameboy (GBS)", {200, 30}};
            pmgui::Button m_gymButton {"test_btn_gym", "Sega Mega Drive (GYM)", {200, 30}};
            pmgui::Button m_hesButton {"test_btn_hes", "NEC TurboGrafx-16 (HES)", {200, 30}};
            pmgui::Button m_kssButton {"test_btn_kss", "MSX Home Computer (KSS)", {200, 30}};
            pmgui::Button m_nsfButton {"test_btn_nsf", "Nintendo NES (NSF)", {200, 30}};
            pmgui::Button m_nsfeButton {"test_btn_nsfe", "Nintendo NES (NSFE)", {200, 30}};
            pmgui::Button m_sapButton {"test_btn_sap", "Atari (SAP)", {200, 30}};
            pmgui::Button m_spcButton {"test_btn_spc", "Super NES (SPC)", {200, 30}};
            pmgui::Button m_vgmButton {"test_btn_vgm", "Video Game Music (VGM)", {200, 30}};

            pmgui::Label m_loadFromFileLabel {"load_from_file", "From file:", "From file:", LabelType::OnlyLabel};
            pmgui::Textbox m_loadFromFileText {"load_from_file_text", "", 0};//150};

            std::string getAudioTimestamp();
            std::string getMillisecondsAsTimeString(int milliseconds);
    };
}

#endif //EMU_JUKEBOX_AUDIOTESTFORM_H
