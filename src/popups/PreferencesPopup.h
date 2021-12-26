//
// Created by robin on 26.03.19.
//

#ifndef EMU_JUKEBOX_PREFERENCESPOPUP_H
#define EMU_JUKEBOX_PREFERENCESPOPUP_H

#include "../data/IniFile.h"
#include "../classes/Font.h"

namespace ebox
{
    class PreferencesPopup : public pmgui::Popup
    {
            typedef std::function<void(ebox::PreferencesPopup*)> func_on_changed; //OnPressed(), for instance
        public:
            PreferencesPopup(const std::string &id, const std::string &title);

            PreferencesPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title);

            void initialize(const sf::Vector2<int> &size);
            void setIniFile(IniFile *iniFile);

            void registerOnChangedCallback(const func_on_changed &cb);

            void setScaleFactor(float scaleFactor) override;

        protected:
            bool onDraw() override;
            void onOpen() override;

        private:
            void onMessageResponse(const Button *btn, const MessagePopupResponse &response);

            void drawGeneralTab();
            void drawThemesTab();
            void drawFontsTab();
            void drawButtonBar();

            void reset();
            void updateIniData();

            void setScaleOnAllItems(float scaleFactor);

            IniFile *m_iniFile;
            std::vector<func_on_changed> m_callbackOnChanged;

            //General
            pmgui::Checkbox m_loadLastFileOnStartup {"load_last_file_on_startup", "Load last opened file/folder on startup"};
            pmgui::Checkbox m_loadLastPlaylistOnStartup {"load_last_playlist_on_startup", "Store current playlist on shutdown and load on startup"};
            //pmgui::Checkbox m_filePreviewsPlayForever {"file_previews_plays_forever", "Play tracks from file explorer forever"};
            pmgui::ColorPicker m_backgroundColor {"background_color", "Background color", ColorPicker::ColorPickerType::ColorEdit3, {35, 65, 90, 255}};
            pmgui::InputInt m_numberOfRepeats {"no_of_repeats", "Number of repeats (0 = infinite)", 0, 100, 1, 2};
            pmgui::InputInt m_defaultTrackLength {"default_track_length", "Default track length (seconds)", 150, 1000, 1, 10};
            pmgui::Button m_resetButton {"reset_button", "Reset to default values", {200, 30}};

            MessagePopup m_resetPopup {"msg_popup_reset", "Reset preferences?", MessagePopupType::YesNo};

            //Themes
            pmgui::Combobox m_themes {"themes_combo", "Theme"};

            //Buttons
            int m_buttonOffset = 0;
            int m_totalButtonWidth = 0;
            pmgui::Button m_okButton {"preferences_ok_button", "OK", {90, 30}};
            pmgui::Button m_applyButton {"preferences_apply_button", "Apply", {90, 30}};
            pmgui::Button m_cancelButton {"preferences_cancel_button", "Cancel", {90, 30}};
    };
}

#endif //EMU_JUKEBOX_PREFERENCESPOPUP_H
