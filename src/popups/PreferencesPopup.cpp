//
// Created by robin on 26.03.19.
//

#include "PreferencesPopup.h"

ebox::PreferencesPopup::PreferencesPopup(const std::string &id, const std::string &title) : Popup(id, title)
{

}

ebox::PreferencesPopup::PreferencesPopup(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id,
                                         const std::string &title) : Popup(position, size, id, title)
{

}

bool ebox::PreferencesPopup::onDraw()
{
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("PreferencesTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("General"))
        {
            drawGeneralTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Themes"))
        {
            drawThemesTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Fonts"))
        {
            drawFontsTab();
            drawButtonBar();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    m_resetPopup.draw();
    return true;
}

void ebox::PreferencesPopup::initialize(const sf::Vector2<int> &size)
{
    setSize(size);
    setFormFlags(FormFlags::NoDocking | FormFlags::NoCollapse | FormFlags::NoResize);
    m_okButton.setOnSameLine(false);
    m_applyButton.setOnSameLine(true);
    m_cancelButton.setOnSameLine(true);

    m_totalButtonWidth = m_okButton.getSize().x + m_applyButton.getSize().x + m_cancelButton.getSize().x + (20 * m_scaleFactor);
    m_buttonOffset = (m_scaledSize.x / 2) - (m_totalButtonWidth / 2);

    m_themes.addValueRange({"dark", "light", "classic", "modern"});
    m_themes.setValue(0);

    m_resetPopup.setMessage("Do you want to reset your preferences?\nThis cannot be undone! ");
    m_resetPopup.registerOnMsgResponseCallback(std::bind(&PreferencesPopup::onMessageResponse, this, std::placeholders::_1, std::placeholders::_2));
}

void ebox::PreferencesPopup::setIniFile(ebox::IniFile *iniFile)
{
    m_iniFile = iniFile;
}

void ebox::PreferencesPopup::drawGeneralTab()
{
    ImGui::BeginChild("preferences_general_tab", {-1, (float)(m_scaledSize.y * 0.82)}, true, 0);
    m_loadLastFileOnStartup.process();
    m_loadLastPlaylistOnStartup.process();
    //m_filePreviewsPlayForever.process();

    ImGui::PushItemWidth(100.f * m_scaleFactor);
    m_numberOfRepeats.process();

    ImGui::PushItemWidth(100.f * m_scaleFactor);
    m_defaultTrackLength.process();

    ImGui::NewLine();
    if(m_resetButton.process())
        m_resetPopup.setOpen(true);

    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawThemesTab()
{
    ImGui::BeginChild("themes_general_tab", {-1, (float)(m_scaledSize.y * 0.82)}, true, 0);
    m_themes.process();
    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawFontsTab()
{
    ImGui::BeginChild("fonts_general_tab", {-1, (float)(m_scaledSize.y * 0.82)}, true, 0);
    m_iniFile->getFontManager()->process();
    ImGui::EndChild();
}

void ebox::PreferencesPopup::drawButtonBar()
{
    ImGui::BeginChild("button_offset", {(float) m_buttonOffset, -1}, false, 0);
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("preferences_buttons", {-1, -1}, false, 0);
    if(m_okButton.process())
    {
        updateIniData();
        setOpen(false);
    }
    if(m_applyButton.process())
    {
        updateIniData();
    }
    if(m_cancelButton.process())
        setOpen(false);
    ImGui::EndChild();
}

void ebox::PreferencesPopup::onOpen()
{
    //General
    m_loadLastFileOnStartup.setChecked(m_iniFile->openLastOpenedItemOnStartup());
    m_loadLastPlaylistOnStartup.setChecked(m_iniFile->openLastPlaylistOnStartup());
    //m_filePreviewsPlayForever.setChecked(m_iniFile->loopPreviewTracksForever());
    m_backgroundColor.setColor(m_iniFile->getBackgroundColor());
    m_themes.setValue(m_iniFile->getCurrentTheme());
    m_numberOfRepeats.setValue(m_iniFile->getNumberOfRepeats());
    m_defaultTrackLength.setValue(m_iniFile->getDefaultTrackLength());
}

void ebox::PreferencesPopup::updateIniData()
{
    float scaleFactor = m_iniFile->getFontManager()->getFontSizeFactor();

    //General
    m_iniFile->setOpenLastOpenedItemOnStartup(m_loadLastFileOnStartup.isChecked());
    m_iniFile->setOpenLastPlaylistOnStartup(m_loadLastPlaylistOnStartup.isChecked());
    //m_iniFile->setLoopPreviewTracksForever(m_filePreviewsPlayForever.isChecked());
    m_iniFile->setBackgroundColor(m_backgroundColor.getColor());
    m_iniFile->setCurrentTheme(m_themes.getValue());
    m_iniFile->applyTheme();
    m_iniFile->getFontManager()->setChosenFontAsDefaultFont();
    m_iniFile->setNumberOfRepeats(m_numberOfRepeats.getValue());
    m_iniFile->setDefaultTrackLength(m_defaultTrackLength.getValue());

    Font *font = m_iniFile->getFontManager()->getChosenFont();
    m_iniFile->setCurrentFont((font == nullptr) ? "" : font->getName());
    setScaleFactor(m_iniFile->getFontManager()->getFontSizeFactor());
    m_iniFile->write();

    for(auto const &callback : m_callbackOnChanged)
        callback(this);
}

void ebox::PreferencesPopup::setScaleOnAllItems(float scaleFactor)
{
    //float scale = 1 + ((scaleFactor - 1) / 2);
    //if(scale < 1)
    //    scale = 1;
    float scale = scaleFactor;

    m_okButton.setSize({(int)(90 * scale), (int)(30 * scale)});
    m_applyButton.setSize({(int)(90 * scale), (int)(30 * scale)});
    m_cancelButton.setSize({(int)(90 * scale), (int)(30 * scale)});
    m_resetButton.setSize({(int)(260 * scale), (int)(30 * scale)});

    m_resetPopup.setSize({(int)(450 * scale), (int)(150 * scale)});
    m_resetPopup.refresh();

    m_totalButtonWidth = m_okButton.getSize().x + m_applyButton.getSize().x + m_cancelButton.getSize().x + (20 * m_scaleFactor);
    m_buttonOffset = (m_scaledSize.x / 2) - (m_totalButtonWidth / 2);
}

void ebox::PreferencesPopup::registerOnChangedCallback(const func_on_changed &cb)
{
    m_callbackOnChanged.emplace_back(cb);
}

void ebox::PreferencesPopup::setScaleFactor(float scaleFactor)
{
    Form::setScaleFactor(scaleFactor);
    setScaleOnAllItems(scaleFactor);
}

void ebox::PreferencesPopup::reset()
{
    if(m_iniFile != nullptr)
    {
        m_iniFile->reset();

        float scaleFactor = m_iniFile->getFontManager()->getFontSizeFactor();

        m_loadLastFileOnStartup.setChecked(m_iniFile->openLastOpenedItemOnStartup());
        m_loadLastPlaylistOnStartup.setChecked(m_iniFile->openLastPlaylistOnStartup());
        //m_filePreviewsPlayForever.setChecked(m_iniFile->loopPreviewTracksForever());
        m_backgroundColor.setColor(m_iniFile->getBackgroundColor());
        m_themes.setValue(m_iniFile->getCurrentTheme());
        m_iniFile->getFontManager()->setChosenFontAsDefaultFont();
        m_numberOfRepeats.setValue(m_iniFile->getNumberOfRepeats());
        m_iniFile->write();
//
        //Font *font = m_iniFile->getFontManager()->getChosenFont();
        //m_iniFile->setCurrentFont((font == nullptr) ? "" : font->getName());
        //setScaleFactor(m_iniFile->getFontManager()->getFontSizeFactor());
        //m_iniFile->write();

        for (auto const &callback : m_callbackOnChanged)
            callback(this);
    }
}

void ebox::PreferencesPopup::onMessageResponse(const Button *btn, const MessagePopupResponse &response)
{
    if(btn->getParentId() == "msg_popup_reset" && response == MessagePopupResponse::Yes)
        reset();
}
