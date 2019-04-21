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
}

void ebox::EmuFileExporterPopup::handleEvents()
{

}

bool ebox::EmuFileExporterPopup::customDraw()
{
    m_pathLabel.process();
    m_pathText.process();
    m_pathButton.process();

    m_sampleRateLabel.process();
    m_sampleRateCombobox.process();

    ImGui::BeginChild("file_exporter_voices", {-1, -1}, true, 0);
    ImGui::Text("Voices:");
    for(auto &voice : *m_file.getVoices())
    {
        voice.showCheckbox();
    }
    ImGui::EndChild();

    m_exportButton.process();
    m_fileDialog.draw();
    return true;
}

void ebox::EmuFileExporterPopup::onOpen()
{
    m_file.initialize(m_path.u8string(), m_trackNo);
}
