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
    if(m_emu != nullptr)
    {
        float treble = static_cast<float>(m_equalizer.treble);
        float bass = static_cast<float>(m_equalizer.bass);
        if (ImGui::SliderFloat("Treble", &treble, -50, 10, "%.0f")) m_emu->set_equalizer(m_equalizer);
        if (ImGui::SliderFloat("Bass", &bass, 16000, 1, "%.0f")) m_emu->set_equalizer(m_equalizer);
        m_equalizer.treble = treble;
        m_equalizer.bass = bass;
    }
    //ImGui::Text("-50.0 = muffled, 0 = flat, +5.0 = extra-crisp");
    //if(ImGui::InputDouble("Treble", &m_equalizer.treble, 1, 5)) m_emu->set_equalizer(m_equalizer);
    //ImGui::Text("1 = full bass, 90 = average, 16000 = almost no bass");
    //if(ImGui::InputDouble("Bass", &m_equalizer.bass, 1, 5)) m_emu->set_equalizer(m_equalizer);
}

void ebox::EmuEqualizer::initialize(Music_Emu *emu)
{
    m_emu = emu;
    m_equalizer = emu->equalizer();
}

