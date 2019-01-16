//
// Created by robin on 16.01.19.
//

#include "EmuEqualizer.h"

ebox::EmuEqualizer::EmuEqualizer()
{

}

ebox::EmuEqualizer::EmuEqualizer(Music_Emu *emu)
{
    initialize(emu);
}

void ebox::EmuEqualizer::draw()
{
    //ImGui::VSliderScalar("Treble",{30, 200}, ImGuiDataType_Double, &m_equalizer.treble, (double *)-100, (double *)100, "%.3f", 5);
    //ImGui::VSliderScalar("Bass",{30, 200}, ImGuiDataType_Double, &m_equalizer.bass, (double *)0, (double *)1000, "%.3f", 5);
    ImGui::Text("-50.0 = muffled, 0 = flat, +5.0 = extra-crisp");
    if(ImGui::InputDouble("Treble", &m_equalizer.treble, 1, 5)) m_emu->set_equalizer(m_equalizer);
    ImGui::Text("1 = full bass, 90 = average, 16000 = almost no bass");
    if(ImGui::InputDouble("Bass", &m_equalizer.bass, 1, 5)) m_emu->set_equalizer(m_equalizer);
}

void ebox::EmuEqualizer::initialize(Music_Emu *emu)
{
    m_emu = emu;
    m_equalizer = emu->equalizer();
}

