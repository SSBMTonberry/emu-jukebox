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

    m_tempo.setValue(1);

    m_fileDialog.registerOnFileChosenCallback(std::bind(&ebox::AudioTestForm::onFileChosen, this, std::placeholders::_1));
}

bool ebox::AudioTestForm::customDraw()
{
    drawAudioPanel();
    drawAudioButtons();
    drawAudioInfo();
    drawEqualizer();

    m_fileDialog.draw();

    return true;
}

void ebox::AudioTestForm::drawAudioPanel()
{
    ImGui::BeginChild("test_audio_panel", {-1, 80}, true, 0);
    int numberOfButtons = 5;
    size_t spacingLength = (getCurrentWindowSize().x / 2) - (numberOfButtons * 20);
    size_t spacingLength2 = (getCurrentWindowSize().x / 6);

    ImGui::SameLine(0, spacingLength);
    if(m_previousButton.process())
        m_stream.previousTrack();
    if(m_stopButton.process())
        m_stream.stop();
    if(m_pauseButton.process())
        m_stream.pause();
    if(m_playButton.process())
        m_stream.play();
    if(m_nextButton.process())
        m_stream.nextTrack();

    ImGui::SameLine(0, spacingLength2);
    ImGui::PushItemWidth(100);
    if(m_tempo.process())
    {
        m_stream.setTempo(m_tempo.getValue());
    }
    if(!m_hasItemsFocused)
        m_hasItemsFocused = ImGui::IsItemActive();

    ImGui::PushItemWidth(-1);
    if(ImGui::SliderInt("###Time: ", m_stream.getTimePlayedPtr(), 0, m_stream.getInfo().getPlayLength(), getAudioTimestamp().c_str()))//"%d"))
    {
        m_stream.setPlayingOffset(sf::milliseconds(m_stream.getTimePlayed()));
    }
    if(!m_hasItemsFocused)
        m_hasItemsFocused = ImGui::IsItemActive();
    ImGui::EndChild();
}

void ebox::AudioTestForm::drawAudioInfo()
{
    ImGui::BeginChild("test_audio_2", {-1, 250}, true, 0);
    ImGui::BeginChild("test_audio_2_sub1", {(getCurrentWindowSize().x / 2), -1}, true, 0);
    ImGui::Text(fmt::format("Track: {0} of {1}", m_stream.getInfo().getTrackNumber() + 1, m_stream.getInfo().getNumberOfTracks()).c_str());
    ImGui::Text(fmt::format("Song: {0}", m_stream.getInfo().getSong()).c_str());
    ImGui::Text(fmt::format("Intro length: {0}", m_stream.getInfo().getIntroLength()).c_str());
    ImGui::Text(fmt::format("Loop length: {0}", m_stream.getInfo().getLoopLength()).c_str());
    ImGui::Text(fmt::format("Play length: {0}", m_stream.getInfo().getPlayLength()).c_str());
    ImGui::Text(fmt::format("Game: {0}", m_stream.getInfo().getGame()).c_str());
    ImGui::Text(fmt::format("Author: {0}", m_stream.getInfo().getAuthor()).c_str());
    ImGui::Text(fmt::format("Comment: {0}", m_stream.getInfo().getComment()).c_str());
    ImGui::Text(fmt::format("Dumper: {0}", m_stream.getInfo().getDumper()).c_str());
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("test_audio_2_sub2", {-1, -1}, true, 0);
    ImGui::Text("Voices:");
    for(auto &voice : *m_stream.getVoices())
    {
        if(m_formIsActive && !m_hasItemsFocused)
            voice.checkHotkeyPress();
        voice.showCheckbox();
    }
    ImGui::EndChild();
    ImGui::EndChild();
}

void ebox::AudioTestForm::drawEqualizer()
{
    ImGui::BeginChild("test_audio_eq", {-1, -1}, true, 0);
    m_hasItemsFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
    m_stream.getEqualizer()->draw();
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
    m_loadFromFileText.setTextboxFlags(TextboxFlags::ReadOnly);
    ImGui::SameLine();
    if(ImGui::SmallButton("..."))
    {
        m_fileDialog.setOpen(true);
    }
    ImGui::SameLine(0, 5);
    if(ImGui::SmallButton("LOAD"))
    {
        fs::path path = m_loadFromFileText.getValue();
        if(fs::exists(path) && fs::is_regular_file(path))
        {
            m_stream.initializeFile(path.string(), m_stream.getInfo().getTrackNumber());
        }
    }
    ImGui::EndChild();
}

std::string ebox::AudioTestForm::getAudioTimestamp()
{
    return fmt::format("{0}/{1}", getMillisecondsAsTimeString(m_stream.getTimePlayed()), getMillisecondsAsTimeString(m_stream.getInfo().getPlayLength()));
}

std::string ebox::AudioTestForm::getMillisecondsAsTimeString(int milliseconds)
{
    if(milliseconds < 0)
        return "00:00.000";
    else
    {
        int hours = (milliseconds / 3600000);
        std::string hourStr = (hours < 10) ? fmt::format("0{0}", hours) : fmt::format("{0}", hours);
        milliseconds -= (hours * 3600000);
        int minutes = (milliseconds / 60000);
        std::string minuteStr = (minutes < 10) ? fmt::format("0{0}", minutes) : fmt::format("{0}", minutes);
        milliseconds -= (minutes * 60000);
        int seconds = (milliseconds / 1000);
        std::string secondStr = (seconds < 10) ? fmt::format("0{0}", seconds) : fmt::format("{0}", seconds);
        milliseconds -= (seconds * 1000);
        std::string millisecondStr;

        if (milliseconds < 100)
            millisecondStr = (milliseconds < 10) ? fmt::format("00{0}", milliseconds) : fmt::format("0{0}", milliseconds);
        else
            millisecondStr = fmt::format("{0}", milliseconds);

        return (hours > 0) ? fmt::format("{0}:{1}:{2}.{3}", hourStr, minuteStr, secondStr, millisecondStr) :
                             fmt::format("{0}:{1}.{2}", minuteStr, secondStr, millisecondStr);
    }
}

void AudioTestForm::handleEvents()
{
    m_fileDialog.handleEvents();
}

void AudioTestForm::onFileChosen(const std::string &path)
{
    m_loadFromFileText.setValue(path);
}
