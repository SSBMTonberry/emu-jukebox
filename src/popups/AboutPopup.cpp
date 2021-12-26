//
// Created by robin on 01.01.2020.
//

#include "AboutPopup.h"

ebox::AboutPopup::AboutPopup(const std::string &id, const std::string &title) : Popup(id, title)
{

}

ebox::AboutPopup::AboutPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title) : Popup(
        position, size, id, title)
{

}

void ebox::AboutPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);
}

bool ebox::AboutPopup::onDraw()
{
    #if PROJECT_VERSION_IS_ALPHA
    const std::string a = "alpha";
    #else
    const std::string a = "";
    #endif
    ImGui::Text(fmt::format("EMU-JUKEBOX v{0}.{1}.{2} {3}", EBOX_PROJECT_VERSION_MAJOR,
                                EBOX_PROJECT_VERSION_MINOR, EBOX_PROJECT_VERSION_PATCH, a).c_str());
    ImGui::Text("Project URL: https://github.com/SSBMTonberry/emu-jukebox");
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::TextWrapped("Emu-Jukebox is a cross-platform music player that emulates the sound "
                       "of old gaming consoles, using files that are read by a sound engine and "
                       "converted into actual sound waves that you can play on your PC. The purpose "
                       "of this project is to make a player that is able to play these retro file "
                       "formats on a computer as if they were regular music files.");
    ImGui::NewLine();
    ImGui::Text("Supported formats: ");
    ImGui::Text("AY  - ZX Spectrum/Amstrad CPC");
    ImGui::Text("GBS - Nintendo Game Boy");
    ImGui::Text("GYM - Sega Genesis/Mega Drive");
    ImGui::Text("HES - NEC TurboGrafx-16/PC Engine");
    ImGui::Text("KSS - MSX Home Computer/other Z80 systems (doesn't support FM sound)");
    ImGui::Text("NSF/NSFE - Nintendo NES/Famicom (with VRC 6, Namco 106, and FME-7 sound)");
    ImGui::Text("SAP - Atari systems using POKEY sound chip");
    ImGui::Text("SPC - Super Nintendo/Super Famicom");
    ImGui::Text("VGM - Sega Master System/Mark III, Sega Genesis/Mega Drive,BBC Micro");

    return true;
}

