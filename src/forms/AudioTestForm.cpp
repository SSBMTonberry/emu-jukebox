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

}

bool ebox::AudioTestForm::customDraw()
{
    ImGui::BeginChild("test_audio_1", {-1, 150}, true, 0);
    if(m_ayButton.process())
        ;
    if(m_gbsButton.process())
        ;
    if(m_gymButton.process())
        ;
    if(m_hesButton.process())
        ;
    if(m_kssButton.process())
        ;
    if(m_nsfButton.process())
        ;
    if(m_nsfeButton.process())
        ;
    if(m_sapButton.process())
        ;
    if(m_spcButton.process())
        ;
    if(m_vgmButton.process())
        ;
    ImGui::EndChild();

    ImGui::BeginChild("test_audio_2", {-1, -1}, true, 0);

    ImGui::EndChild();
    return true;
}




