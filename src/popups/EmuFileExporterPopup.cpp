//
// Created by robin on 21.04.19.
//

#include "EmuFileExporterPopup.h"

ebox::EmuFileExporterPopup::EmuFileExporterPopup(const std::string &id, const std::string &title, const std::string &imguiId) : Popup(id, title,
                                                                                                                                      imguiId)
{

}

ebox::EmuFileExporterPopup::EmuFileExporterPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id,
                                                 const std::string &title, const std::string &imguiId) : Popup(position, size, id, title, imguiId)
{

}

void EmuFileExporterPopup::setExportInfo(const fs::path &path, int trackNo)
{
    m_path = path;
    m_trackNo = trackNo;

    std::string suggestedPath = fmt::format("{0}/{1}.ogg", m_path.parent_path().u8string(), m_path.stem().u8string());
    m_pathText.setValue(suggestedPath);
    m_fileDialog.setPath(fs::path(m_path.parent_path().u8string()));
    m_fileDialog.setFilename(m_path.stem().u8string());
    m_file.initialize(m_path.u8string(), m_trackNo);
}

void EmuFileExporterPopup::transferVoiceStates(std::vector<Voice> *voices)
{
    if(voices->size() == m_file.getVoices()->size())
    {
        for(int i = 0; i < m_file.getVoices()->size(); ++i)
        {
            m_file.getVoices()->at(i).setMuted(voices->at(i).isMuted());
            m_file.getVoices()->at(i).getCheckbox()->setChecked(!voices->at(i).isMuted());
        }
    }
}

void EmuFileExporterPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);

    m_pathText.setOnSameLine(true);
    m_pathText.setTextboxFlags(TextboxFlags::ReadOnly);
    m_pathText.setHasLabel(false, true);
    m_pathButton.setOnSameLine(true);

    m_sampleRateCombobox.setOnSameLine(true);
    m_sampleRateCombobox.setHasLabel(false, true);
    m_sampleRateCombobox.addValueRange({"44100", "32000", "22050", "11025", "8000"});
    m_sampleRateCombobox.setValue(0);

    m_fileDialog.setFileTypes(FileTypeMode::SoundFiles);
    m_fileDialog.registerOnFileChosenCallback(std::bind(&EmuFileExporterPopup::onFileChosen, this, std::placeholders::_1));
}

void ebox::EmuFileExporterPopup::handleEvents()
{
    m_fileDialog.handleEvents();
}

void ebox::EmuFileExporterPopup::onFileChosen(const std::string &path)
{
    m_pathText.setValue(path);
}

bool ebox::EmuFileExporterPopup::customDraw()
{
    ImGui::Text(fmt::format("Song: {0}", m_file.getInfoFromCurrentTrack().getSong()).c_str());
    ImGui::Text(fmt::format("Game: {0}", m_file.getInfoFromCurrentTrack().getGame()).c_str());

    ImGui::Separator();
    m_pathLabel.process();
    m_pathText.process();
    if(m_pathButton.process())
        m_fileDialog.setOpen(true);

    m_sampleRateLabel.process();
    m_sampleRateCombobox.process();

    ImGui::BeginChild("file_exporter_voices", {-1, 40 + (m_file.getVoices()->size() * 30)}, true, 0);
    ImGui::Text("Voices:");
    for(auto &voice : *m_file.getVoices())
    {
        voice.showCheckbox();
    }
    ImGui::EndChild();

    if(m_exportButton.process())
    {
        fs::path path{m_pathText.getValue()};
        if(fs::exists(path.parent_path()))
        {
            int sampleRate = std::stoi(m_sampleRateCombobox.getValue());
            m_file.reload(sampleRate);
            if(m_file.createSamplesAndFillBuffer())
            {
                if(m_file.exportToSoundFile(path.u8string()))
                    SystemLog::get()->addSuccess(fmt::format("Track successfully exported to: {0}", path.u8string()));
                else
                    SystemLog::get()->addError(fmt::format("Unable to export track to: {0}", path.u8string()));
            }
        }
        else
            SystemLog::get()->addError(fmt::format("Directory '{0}' does not exist!", path.parent_path().u8string()));
        setOpen(false);
    }
    m_fileDialog.draw();
    return true;
}

void ebox::EmuFileExporterPopup::onOpen()
{

}
