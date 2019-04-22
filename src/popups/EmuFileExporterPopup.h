//
// Created by robin on 21.04.19.
//

#ifndef EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H
#define EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H

#include "../gui/forms/Popup.h"
#include "../gui/controls/DragInt.h"
#include "../gui/controls/InputFloat.h"
#include "../audio/EmuFile.h"
#include "../gui/controls/Button.h"
#include "../gui/controls/Textbox.h"
#include "../gui/controls/Combobox.h"
#include "../widgets/FileDialog.h"

namespace ebox
{
    class EmuFileExporterPopup : public Popup
    {
        public:
            EmuFileExporterPopup(const std::string &id, const std::string &title, const std::string &imguiId = "");

            EmuFileExporterPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                 const std::string &imguiId = "");

            void setExportInfo(const fs::path &path, int trackNo, float tempo);
            void transferVoiceStates(std::vector<Voice> * voices);

            void initialize(const sf::Vector2<int> &size);
            void handleEvents() override;

            void onFileChosen(const std::string &path);

        protected:

            bool customDraw() override;
            void onOpen() override;

            fs::path m_path;
            int m_trackNo = 0;
            sf::Vector2<int> m_size {200, 200};

            FileDialog m_fileDialog { DialogType::SaveFile ,"file_exporter_dialog", "Export", "file_exporter_dialog" };

            Label m_pathLabel {"path_label", "Path:", "", LabelType::OnlyLabel};
            Textbox m_pathText {"path_textbox", ""};
            Button m_pathButton {"path_button", "...", {60, 20}};
            Checkbox m_useCustomLength {"use_custom_song_length", "Use custom song length", false};
            DragInt m_customStart {"custom_start", "Start (ms)", 0, 500000, 100};
            DragInt m_customStop {"custom_stop", "Stop (ms)", 0, 1000000, 100};
            Label m_tempoLabel {"tempo_label", "Tempo", "", LabelType::OnlyLabel};
            InputFloat m_tempo {"export_tempo", "###export_tempo", 0.1f, 5.f, 0.1f, 0.2f};

            Label m_sampleRateLabel {"sample_rate_label", "Sample rate:", "", LabelType::OnlyLabel};
            Combobox m_sampleRateCombobox {"sample_rate_combobox", ""};

            Button m_exportButton {"path_button", "Export", {120, 40}};

            EmuFile m_file;
    };
}

#endif //EMU_JUKEBOX_EMUFILEEXPORTERPOPUP_H
