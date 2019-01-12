//
// Created by robin on 12.01.19.
//

#ifndef EMU_JUKEBOX_AUDIOTESTFORM_H
#define EMU_JUKEBOX_AUDIOTESTFORM_H

#include "../gui/forms/Form.h"
#include "../gui/controls/Button.h"
#include "../../content/files_mapper.h"

namespace ebox
{
    class AudioTestForm : public Form
    {
        public:
            AudioTestForm(const std::string &id, const std::string &title, const std::string &imguiId = "");

            AudioTestForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                          const std::string &imguiId = "");

        protected:
            bool customDraw() override;

        private:
            void initialize();

            ebox::Button m_ayButton {"test_btn_ay", "Test Amstrad CPC (AY)", {200, 30}};
            ebox::Button m_gbsButton {"test_btn_gbs", "Test Gameboy (GBS)", {200, 30}};
            ebox::Button m_gymButton {"test_btn_gym", "Sega Mega Drive (GYM)", {200, 30}};
            ebox::Button m_hesButton {"test_btn_hes", "NEC TurboGrafx-16 (HES)", {200, 30}};
            ebox::Button m_kssButton {"test_btn_kss", "MSX Home Computer (KSS)", {200, 30}};
            ebox::Button m_nsfButton {"test_btn_nsf", "Nintendo NES (NSF)", {200, 30}};
            ebox::Button m_nsfeButton {"test_btn_nsfe", "Nintendo NES (NSFE)", {200, 30}};
            ebox::Button m_sapButton {"test_btn_sap", "Atari (SAP)", {200, 30}};
            ebox::Button m_spcButton {"test_btn_spc", "Super NES (SPC)", {200, 30}};
            ebox::Button m_vgmButton {"test_btn_vgm", "Video Game Music (VGM)", {200, 30}};
    };
}

#endif //EMU_JUKEBOX_AUDIOTESTFORM_H
