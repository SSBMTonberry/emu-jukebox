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

void EmuFileExporterPopup::setExportInfo(const fs::path &path, int trackNo, float tempo)
{
    m_path = path;
    m_trackNo = trackNo;

    std::string suggestedPath = fmt::format("{0}/{1}.ogg", m_path.parent_path().u8string(), m_path.stem().u8string());
    m_pathText.setValue(suggestedPath);
    m_fileDialog.setPath(fs::path(m_path.parent_path().u8string()));
    m_fileDialog.setFilename(m_path.stem().u8string());
    m_file.initialize(m_path.u8string(), m_trackNo);

    m_useCustomLength.setChecked(false);
    m_customStart.setValues({0});
    m_customStart.setWidth(100);
    m_customStop.setValues({m_file.getInfoFromCurrentTrack()->getPlayLength()});
    m_customStop.setWidth(100);
    m_tempo.setValue(tempo);
    m_tempo.setOnSameLine(true);
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

    m_customStop.setOnSameLine(true);
}

void ebox::EmuFileExporterPopup::handleEvents()
{
    m_fileDialog.handleEvents();
}

void ebox::EmuFileExporterPopup::onFileChosen(const fs::path& path)//(const std::string &path)
{
    m_pathText.setValue(path.u8string());
}

bool ebox::EmuFileExporterPopup::customDraw()
{
    ImGui::Text(fmt::format("Song: {0}", m_file.getInfoFromCurrentTrack()->getSong()).c_str());
    ImGui::Text(fmt::format("Game: {0}", m_file.getInfoFromCurrentTrack()->getGame()).c_str());

    ImGui::Separator();
    m_pathLabel.process();
    m_pathText.process();
    if(m_pathButton.process())
        m_fileDialog.setOpen(true);

    m_sampleRateLabel.process();
    m_sampleRateCombobox.process();
    m_tempoLabel.process();
    m_tempo.process();

    ImGui::BeginChild("file_exporter_custom_length", {-1.f, 60.f * m_scaleFactor}, true, 0);
    m_useCustomLength.process();
    if(m_useCustomLength.isChecked())
    {
        m_customStart.process();
        m_customStop.process();
        int start = m_customStart.getValues()[0];
        int stop = m_customStop.getValues()[0];
        if(start > stop)
            m_customStart.setValues({stop});
    }
    ImGui::EndChild();

    ImGui::BeginChild("file_exporter_voices", {-1.f, (float)(40 + (m_file.getVoices()->size() * 30)) * m_scaleFactor}, true, 0);
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
            m_file.reload(sampleRate, m_tempo.getValue());
            uint64_t startPos = 0;
            if(m_useCustomLength.isChecked())
            {
                startPos = m_customStart.getValues()[0];
                m_file.getInfoFromCurrentTrack()->setPlayLength(m_customStop.getValues()[0]);
            }
            if(m_file.createSamplesAndFillBuffer(startPos, m_tempo.getValue()))
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

void EmuFileExporterPopup::setScaleFactor(float scaleFactor)
{
    Form::setScaleFactor(scaleFactor);
    m_exportButton.setSize({(int)(120 * scaleFactor), (int)(40 * scaleFactor)});
    m_pathButton.setSize({(int)(60 * scaleFactor), (int)(20 * scaleFactor)});
    m_customStart.setWidth(100.f * scaleFactor);
    m_customStop.setWidth(100.f * scaleFactor);
}
