//
// Created by robin on 26.03.19.
//

#ifndef EMU_JUKEBOX_PREFERENCESPOPUP_H
#define EMU_JUKEBOX_PREFERENCESPOPUP_H

#include "../gui/forms/Popup.h"
#include "../data/IniFile.h"

namespace ebox
{
    class PreferencesPopup : public Popup
    {
        public:
            PreferencesPopup(const std::string &id, const std::string &title, const std::string &imguiId = "");

            PreferencesPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                             const std::string &imguiId = "");

            void initialize(const sf::Vector2<int> &size);
            void setIniFile(IniFile *iniFile);

        protected:
            bool customDraw() override;

        private:
            void drawGeneralTab();
            void drawThemesTab();
            void drawFontsTab();

            IniFile *m_iniFile;
    };
}

#endif //EMU_JUKEBOX_PREFERENCESPOPUP_H
