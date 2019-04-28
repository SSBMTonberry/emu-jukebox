//
// Created by robin on 26.03.19.
//

#ifndef EMU_JUKEBOX_PREFERENCESPOPUP_H
#define EMU_JUKEBOX_PREFERENCESPOPUP_H

#include "../gui/forms/Popup.h"
#include "../data/IniFile.h"

#include "../gui/controls/ColorButton.h"
#include "../gui/controls/ColorPicker.h"
#include "../gui/controls/Checkbox.h"
#include "../gui/controls/Button.h"
#include "../gui/controls/Combobox.h"
#include "../gui/controls/InputInt.h"
#include "../classes/Font.h"

namespace ebox
{
    class PreferencesPopup : public Popup
    {
            typedef std::function<void(ebox::PreferencesPopup*)> func_on_changed; //OnPressed(), for instance
        public:
            PreferencesPopup(const std::string &id, const std::string &title, const std::string &imguiId = "");

            PreferencesPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                             const std::string &imguiId = "");

            void initialize(const sf::Vector2<int> &size);
            void setIniFile(IniFile *iniFile);

            void registerOnChangedCallback(const func_on_changed &cb);

            void setScaleFactor(float scaleFactor) override;

        protected:
            bool customDraw() override;

            void onOpen() override;

        private:
            void drawGeneralTab();
            void drawThemesTab();
            void drawFontsTab();
            void drawButtonBar();

            void updateIniData();

            void setScaleOnAllItems(float scaleFactor);

            IniFile *m_iniFile;
            std::vector<func_on_changed> m_callbackOnChanged;

            //General
            Checkbox m_loadLastFileOnStartup {"load_last_file_on_startup", "Load last opened file/folder on startup"};
            Checkbox m_loadLastPlaylistOnStartup {"load_last_playlist_on_startup", "Store current playlist on shutdown and load on startup"};
            Checkbox m_filePreviewsPlayForever {"file_previews_plays_forever", "Play tracks from file explorer forever"};
            ColorPicker m_backgroundColor {"background_color", "Background color", ColorPicker::ColorPickerType::ColorEdit3, {35, 65, 90, 255}};
            InputInt m_numberOfRepeats {"no_of_repeats", "Number of repeats (0 = infinite)", 0, 100, 1, 2};

            //Themes
            Combobox m_themes {"themes_combo", "Theme"};

            //Buttons
            int m_buttonOffset = 0;
            int m_totalButtonWidth = 0;
            Button m_okButton {"preferences_ok_button", "OK", {90, 30}};
            Button m_applyButton {"preferences_apply_button", "Apply", {90, 30}};
            Button m_cancelButton {"preferences_cancel_button", "Cancel", {90, 30}};
    };
}

#endif //EMU_JUKEBOX_PREFERENCESPOPUP_H
