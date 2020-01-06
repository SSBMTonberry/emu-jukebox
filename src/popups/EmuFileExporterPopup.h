//
// Created by robin on 21.04.19.
//

#ifndef EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H
#define EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H

//#include "../gui/forms/Popup.h"
//#include "../gui/controls/DragInt.h"
//#include "../gui/controls/InputFloat.h"
#include "../audio/EmuFile.h"
//#include "../gui/controls/Button.h"
//#include "../gui/controls/Textbox.h"
//#include "../gui/controls/Combobox.h"
//#include "../widgets/FileDialog.h"
#include "pmgui.h"

namespace ebox
{
    class EmuFileExporterPopup : public pmgui::Popup
    {
        public:
            EmuFileExporterPopup(const std::string &id, const std::string &title);

            EmuFileExporterPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title);

            void setExportInfo(const fs::path &path, int trackNo, float tempo);
            void transferVoiceStates(std::vector<Voice> * voices);

            void initialize(const sf::Vector2<int> &size);
            void handleEvents() override;

			void onFileChosen(const fs::path& path);//(const std::string &path);

            void setScaleFactor(float scaleFactor) override;

        protected:

            bool onDraw() override;
            void onOpen() override;

            fs::path m_path;
            int m_trackNo = 0;
            sf::Vector2<int> m_size {200, 200};

            pmgui::FileDialog m_fileDialog { pmgui::DialogType::SaveFile ,"file_exporter_dialog", "Export" };

            pmgui::Label m_pathLabel {"path_label", "Path:", "", LabelType::OnlyLabel};
            pmgui::Textbox m_pathText {"path_textbox", "", 0, 666}; //Need index to be able to hide label
            pmgui::Button m_pathButton {"path_button", "...", {60, 20}};
            pmgui::Checkbox m_useCustomLength {"use_custom_song_length", "Use custom song length", false};
            pmgui::DragInt m_customStart {"custom_start", "Start (ms)", 0, 500000, 100};
            pmgui::DragInt m_customStop {"custom_stop", "Stop (ms)", 0, 1000000, 100};
            pmgui::Label m_tempoLabel {"tempo_label", "Tempo", "", LabelType::OnlyLabel};
            pmgui::InputFloat m_tempo {"export_tempo", "###export_tempo", 0.1f, 5.f, 0.1f, 0.2f};

            pmgui::Label m_sampleRateLabel {"sample_rate_label", "Sample rate:", "", LabelType::OnlyLabel};
            pmgui::Combobox m_sampleRateCombobox {"sample_rate_combobox", ""};

            pmgui::Button m_exportButton {"path_button", "Export", {120, 40}};

            EmuFile m_file;
    };
}

#endif //EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H
