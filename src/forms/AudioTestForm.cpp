//
// Created by robin on 12.01.19.
//

#include "AudioTestForm.h"

ebox::AudioTestForm::AudioTestForm(const std::string &id, const std::string &title, const std::string &imguiId) : Form(id, title, imguiId)
{
    initialize();
}

ebox::AudioTestForm::AudioTestForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                   const std::string &imguiId) : Form(position, size, id, title, imguiId)
{
    initialize();
}

void ebox::AudioTestForm::initialize()
{
    m_gbsButton.setOnSameLine(true);
    m_gymButton.setOnSameLine(true);

    m_kssButton.setOnSameLine(true);
    m_nsfButton.setOnSameLine(true);

    m_sapButton.setOnSameLine(true);
    m_spcButton.setOnSameLine(true);

    m_loadFromFileText.setOnSameLine(true);
    m_loadFromFileText.setHasLabel(false, true);

    //m_previousButton.setOnSameLine(true);
    const sf::Rect rect = m_previousButton.getImage()->getTextureRect();
    m_previousButton.getImage()->setTextureRect(sf::IntRect(rect.width, 0, -rect.width, rect.height)); //Flip sprite
    m_stopButton.setOnSameLine(true);
    m_pauseButton.setOnSameLine(true);
    m_playButton.setOnSameLine(true);
    m_nextButton.setOnSameLine(true);
}

bool ebox::AudioTestForm::customDraw()
{
    drawAudioPanel();
    drawAudioButtons();
    drawAudioInfo();

    return true;
}

void ebox::AudioTestForm::drawAudioPanel()
{
    ImGui::BeginChild("test_audio_panel", {-1, 40}, true, 0);

    int numberOfButtons = 5;
    size_t spacingLength = (getCurrentWindowSize().x / 2) - (numberOfButtons * 20);

    ImGui::SameLine(0, spacingLength);
    if(m_previousButton.process())
        ;
    if(m_stopButton.process())
        m_stream.stop();
    if(m_pauseButton.process())
        m_stream.pause();
    if(m_playButton.process())
        m_stream.play();
    if(m_nextButton.process())
        ;
    ImGui::EndChild();
}

void ebox::AudioTestForm::drawAudioInfo()
{
    ImGui::BeginChild("test_audio_2", {-1, -1}, true, 0);

    ImGui::EndChild();
}

void ebox::AudioTestForm::drawAudioButtons()
{
    ImGui::BeginChild("test_audio_1", {-1, 200}, true, 0);
    if(m_ayButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_AY, files_mapper::test_files::_TEST_AY_SIZE);
    if(m_gbsButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_GBS, files_mapper::test_files::_TEST_GBS_SIZE);
    if(m_gymButton.process())
        ;//m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_GYM, files_mapper::test_files::_TEST_GYM_SIZE);
    if(m_hesButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_HES, files_mapper::test_files::_TEST_HES_SIZE);
    if(m_kssButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_KSS, files_mapper::test_files::_TEST_KSS_SIZE);
    if(m_nsfButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_NSF, files_mapper::test_files::_TEST_NSF_SIZE);
    if(m_nsfeButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_NSFE, files_mapper::test_files::_TEST_NSFE_SIZE);
    if(m_sapButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_SAP, files_mapper::test_files::_TEST_SAP_SIZE);
    if(m_spcButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_SPC, files_mapper::test_files::_TEST_SPC_SIZE);
    if(m_vgmButton.process())
        m_stream.initializeMemory((void *)files_mapper::test_files::_TEST_VGM, files_mapper::test_files::_TEST_VGM_SIZE);
    ImGui::Spacing();
    m_loadFromFileLabel.process();
    m_loadFromFileText.process();
    ImGui::SameLine();
    if(ImGui::SmallButton("LOAD"))
        ;
    ImGui::EndChild();
}




