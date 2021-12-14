//
// Created by robin on 17.02.19.
//

#include "AudioPlayerForm.h"

const std::string ebox::AudioPlayerForm::ID = "AudioPlayer";

ebox::AudioPlayerForm::AudioPlayerForm(const std::string &id, const std::string &title) : pmgui::Form(id, title)
{
    initialize();
}

ebox::AudioPlayerForm::AudioPlayerForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title) : pmgui::Form(position, size, id, title)
{
    initialize();
}

void ebox::AudioPlayerForm::initialize()
{
    const sf::Rect rect = m_previousButton.getImage()->getTextureRect();
    //m_previousButton.getImage()->setTextureRect(sf::IntRect(rect.width, 0, -rect.width, rect.height)); //Flip sprite
    m_previousButton.setTooltip(std::make_optional<pmgui::Tooltip>("Previous track (<Alt>+<Left>)"));
    m_stopButton.setOnSameLine(true);
    m_stopButton.setTooltip(std::make_optional<pmgui::Tooltip>("Stop (<Ctrl>+<Space>)"));
    m_pauseButton.setOnSameLine(true);
    m_pauseButton.setTooltip(std::make_optional<pmgui::Tooltip>("Pause (<Alt>+<Space>)"));
    m_playButton.setOnSameLine(true);
    m_playButton.setTooltip(std::make_optional<pmgui::Tooltip>("Play (<Alt>+<Space>)"));
    m_nextButton.setOnSameLine(true);
    m_nextButton.setTooltip(std::make_optional<pmgui::Tooltip>("Next track (<Alt>+<Right>)"));

    m_playButton.getImage()->setColor(sf::Color::Green);
    m_pauseButton.getImage()->setColor(sf::Color::Yellow);
    m_stopButton.getImage()->setColor(sf::Color::Red);

    m_tempo.setOnSameLine(true);
    m_tempo.setValue(1);
    m_state = AudioPlayerState::Stopped;
}

void ebox::AudioPlayerForm::handleEvents()
{
    processHotkeys();
}

void ebox::AudioPlayerForm::processHotkeys()
{
    if(m_stream != nullptr)
    {
        bool abort = false;
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::PreviousTrack))
        {
            for(auto const &callback : m_callbackOnPrevious)
                abort = callback(this) ? true : abort;

            if(!abort) m_stream->previousTrack();
        }
        else if(Hotkeys::get()->isPlayerHotkeyPressed(key::NextTrack))
        {
            for(auto const &callback : m_callbackOnNext)
                abort = callback(this) ? true : abort;

            if(!abort) m_stream->nextTrack();
        }
        else if(Hotkeys::get()->isPlayerHotkeyPressed(key::Stop))
        {
            for(auto const &callback : m_callbackOnStop)
                abort = callback(this) ? true : abort;

            if(!abort) stop();
        }
        else if(Hotkeys::get()->isPlayerHotkeyPressed(key::TogglePlayAndPause))
        {
            if(m_state == AudioPlayerState::Play)
            {
                for(auto const &callback : m_callbackOnPause)
                    abort = callback(this) ? true : abort;

                if(!abort) pause();
            }
            else
            {
                for(auto const &callback : m_callbackOnPlay)
                    abort = callback(this) ? true : abort;

                if(!abort) play();
            }
        }

        //Voices
        size_t voices = m_stream->getNumberOfVoices();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute1) && voices > 0) m_stream->getVoices()->at(0).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute2) && voices > 1) m_stream->getVoices()->at(1).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute3) && voices > 2) m_stream->getVoices()->at(2).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute4) && voices > 3) m_stream->getVoices()->at(3).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute5) && voices > 4) m_stream->getVoices()->at(4).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute6) && voices > 5) m_stream->getVoices()->at(5).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute7) && voices > 6) m_stream->getVoices()->at(6).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute8) && voices > 7) m_stream->getVoices()->at(7).toggleMute();
        if(Hotkeys::get()->isPlayerHotkeyPressed(key::ToggleVoiceMute9) && voices > 8) m_stream->getVoices()->at(8).toggleMute();

    }
}

bool ebox::AudioPlayerForm::onDraw()
{
    drawAudioPanel();
    drawAudioVisualizer();
    if(m_stream != nullptr)
    {
        drawAudioInfo();
        drawEqualizer();
    }
    return true;
}

void ebox::AudioPlayerForm::drawAudioPanel()
{
    float scaleFactor = m_iniFile->getFontManager()->getFontSizeFactor();
    ImGui::PushAllowKeyboardFocus(false);

    int numberOfButtons = 4;
    size_t spacingLength = (getCurrentWindowSize().x / 2) - (numberOfButtons * 20);
    size_t spacingLength2 = (size_t) ((spacingLength - (160 * 2)) / scaleFactor);

    ImGui::BeginChild("audio_player_panel", {-1, 90 * scaleFactor}, true, 0);
    ImGui::SameLine(0, spacingLength);
    if(m_previousButton.process() && m_stream != nullptr)
    {
        bool abort = false;
        for(auto const &callback : m_callbackOnPrevious)
            abort = callback(this) ? true : abort;

        if(!abort) m_stream->previousTrack();
    }
    if(m_stopButton.process() && m_stream != nullptr)
    {
        bool abort = false;
        for(auto const &callback : m_callbackOnStop)
            abort = callback(this) ? true : abort;

        if(!abort) stop();
    }
    if(m_state == AudioPlayerState::Play && m_pauseButton.process() && m_stream != nullptr)
    {
        bool abort = false;
        for(auto const &callback : m_callbackOnPause)
            abort = callback(this) ? true : abort;

        if(!abort) pause();
    }
    if(m_state != AudioPlayerState::Play && m_playButton.process() && m_stream != nullptr)
    {
        bool abort = false;
        for(auto const &callback : m_callbackOnPlay)
            abort = callback(this) ? true : abort;

        if(!abort) play();
    }
    if(m_nextButton.process() && m_stream != nullptr)
    {
        bool abort = false;
        for(auto const &callback : m_callbackOnNext)
            abort = callback(this) ? true : abort;

        if(!abort) m_stream->nextTrack();
    }

    //ImGui::SameLine(0, spacingLength2);


    ImGui::PushItemWidth(-1);
    int dummy = 0;
    if(ImGui::SliderInt("###Time: ", (m_stream != nullptr) ? m_stream->getTimePlayedPtr() : &dummy, 0,
            (m_stream != nullptr) ? m_stream->getInfoFromCurrentTrack().getPlayLength() : 0, getAudioTimestamp().c_str()))
    {
        if(m_stream != nullptr)
            m_stream->setPlayingOffset(sf::milliseconds(m_stream->getTimePlayed()));
    }

    if(m_stream != nullptr && m_stream->getTimePlayed() >= m_stream->getInfoFromCurrentTrack().getPlayLength())
    {
        m_stream->incrementNumberOfPlays();

        //TODO: Make this only check when repeat is on.
        if(*m_playlistRepeat && m_stream->getNumberOfPlays() < m_iniFile->getNumberOfRepeats())
        {
            m_stream->setPlayingOffset(sf::milliseconds(0));
        }
        else
        {
            bool proceedAfterEnd = false;
            for (auto const &callback : m_callbackOnTrackEnded)
                proceedAfterEnd = callback(this, m_stream.get()) ? true : proceedAfterEnd;

            if (!proceedAfterEnd) m_stream->stop();
        }
    }
    ImGui::NewLine();
    ImGui::SameLine(0, spacingLength + spacingLength2);
    ImGui::PushItemWidth(100 * scaleFactor);
    if(m_volume.process())
    {
        m_iniFile->setLastVolume(m_volume.getValues()[0]);
        if(m_stream != nullptr)
            m_stream->setVolume(m_iniFile->getLastVolume());
    }

    ImGui::PushItemWidth(100 * scaleFactor);
    ImGui::SameLine(0, 10 * scaleFactor);
    if(m_tempo.process() && m_stream != nullptr)
    {
        m_stream->setTempo(m_tempo.getValue());
    }

    ImGui::EndChild();

    ImGui::PopAllowKeyboardFocus();
}

void ebox::AudioPlayerForm::drawAudioVisualizer()
{

    ImGui::BeginChild("visualizer_panel", { -1, 100 }, true, 0);
    if (m_visualizer.process() && m_stream != nullptr) {
        //???
    }
    ImGui::EndChild();
}

void ebox::AudioPlayerForm::drawAudioInfo()
{
    float scaleFactor = m_iniFile->getFontManager()->getFontSizeFactor();
    ImGui::BeginChild("audio_info", {-1, 250 * scaleFactor}, true, 0);
    ImGui::BeginChild("audio_info_sub1", {(static_cast<float>(getCurrentWindowSize().x) / 2), -1}, true, 0);
    ImGui::Text(fmt::format("Filename: {0}", m_stream->getInfoFromCurrentTrack().getFilename()).c_str());
    ImGui::Text(fmt::format("Track: {0} of {1}", m_stream->getInfoFromCurrentTrack().getTrackNumber() + 1, m_stream->getNumberOfTracks()).c_str());
    ImGui::Text(fmt::format("Song: {0}", m_stream->getInfoFromCurrentTrack().getSong()).c_str());
    ImGui::Text(fmt::format("Intro length: {0}", m_stream->getInfoFromCurrentTrack().getIntroLength()).c_str());
    ImGui::Text(fmt::format("Loop length: {0}", m_stream->getInfoFromCurrentTrack().getLoopLength()).c_str());
    ImGui::Text(fmt::format("Play length: {0}", m_stream->getInfoFromCurrentTrack().getPlayLength()).c_str());
    ImGui::Text(fmt::format("Game: {0}", m_stream->getInfoFromCurrentTrack().getGame()).c_str());
    ImGui::Text(fmt::format("Author: {0}", m_stream->getInfoFromCurrentTrack().getAuthor()).c_str());
    ImGui::Text(fmt::format("Comment: {0}", m_stream->getInfoFromCurrentTrack().getComment()).c_str());
    ImGui::Text(fmt::format("Dumper: {0}", m_stream->getInfoFromCurrentTrack().getDumper()).c_str());
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("audio_info_sub2", {-1, -1}, true, 0);
    ImGui::Text("Voices:");
    for(auto &voice : *m_stream->getVoices())
    {
        voice.showCheckbox();
    }
    ImGui::EndChild();
    ImGui::EndChild();
}

void ebox::AudioPlayerForm::drawEqualizer()
{
    ImGui::BeginChild("audio_eq", {-1, -1}, true, 0);
    //m_hasItemsFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
    m_stream->getEqualizer()->draw();
    ImGui::EndChild();
}

std::string ebox::AudioPlayerForm::getAudioTimestamp()
{
    return fmt::format("{0}/{1}", getMillisecondsAsTimeString((m_stream != nullptr) ? m_stream->getTimePlayed() : 0),
            getMillisecondsAsTimeString((m_stream != nullptr) ? m_stream->getInfoFromCurrentTrack().getPlayLength() : 0));
}

std::string ebox::AudioPlayerForm::getMillisecondsAsTimeString(int milliseconds)
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

bool ebox::AudioPlayerForm::createStream(const EmuFileInfo &info)
{
    m_stream = std::make_unique<EmuStream>(info.getPath().string());
    m_stream->setId(info.getId());
    m_state = AudioPlayerState::Stopped;
    m_visualizer.attachToStream(m_stream);
    m_stream->setVolume(m_iniFile->getLastVolume());
    m_volume.setValues({m_stream->getVolume()});
    return m_stream->isValid();
}

void ebox::AudioPlayerForm::setStream(std::unique_ptr<EmuStream> stream)
{
    m_stream = std::move(stream);
    m_visualizer.attachToStream(m_stream);
    m_stream->setVolume(m_iniFile->getLastVolume());
    m_volume.setValues({m_stream->getVolume()});
    m_state = AudioPlayerState::Stopped;
}

//EmuStream *ebox::AudioPlayerForm::getStream() const
//{
//    return m_stream.get();
//}

/*!
 * Register a callback that will be called right BEFORE the play-action, when clicking the Play-button.
 * The callback itself can return a bool, which will abort the default action (play) if returning true.
 *
 * @param cb The callback function. Example: bool onPlay(AudioPlayerForm *player)
 */
void ebox::AudioPlayerForm::registerOnPlayCallback(const ebox::AudioPlayerForm::func_audioplayer &cb)
{
    m_callbackOnPlay.emplace_back(cb);
}

/*!
 * Register a callback that will be called right BEFORE the stop-action, when clicking the Stop-button.
 * The callback itself can return a bool, which will abort the default action (stop) if returning true.
 *
 * @param cb The callback function. Example: bool onStop(AudioPlayerForm *player)
 */
void ebox::AudioPlayerForm::registerOnStopCallback(const ebox::AudioPlayerForm::func_audioplayer &cb)
{
    m_callbackOnStop.emplace_back(cb);
}

/*!
 * Register a callback that will be called right BEFORE the pause-action, when clicking the Pause-button.
 * The callback itself can return a bool, which will abort the default action (pause) if returning true.
 *
 * @param cb The callback function. Example: bool onPause(AudioPlayerForm *player)
 */
void ebox::AudioPlayerForm::registerOnPauseCallback(const ebox::AudioPlayerForm::func_audioplayer &cb)
{
    m_callbackOnPause.emplace_back(cb);
}

/*!
 * Register a callback that will be called right BEFORE the "next track"-action, when clicking the "Next track"-button.
 * The callback itself can return a bool, which will abort the default action (next track) if returning true.
 *
 * @param cb The callback function. Example: bool onNextTrack(AudioPlayerForm *player)
 */
void ebox::AudioPlayerForm::registerOnNextTrackCallback(const ebox::AudioPlayerForm::func_audioplayer &cb)
{
    m_callbackOnNext.emplace_back(cb);
}

/*!
 * Register a callback that will be called right BEFORE the "previous track"-action, when clicking the "Previous track"-button.
 * The callback itself can return a bool, which will abort the default action (previous track) if returning true.
 *
 * @param cb The callback function. Example: bool onPreviousTrack(AudioPlayerForm *player)
 */
void ebox::AudioPlayerForm::registerOnPreviousTrackCallback(const ebox::AudioPlayerForm::func_audioplayer &cb)
{
    m_callbackOnPrevious.emplace_back(cb);
}

/*!
 * Register a callback that will be called when a track has ended (when time played is more than equal to the play length).
 *
 * @param cb The callback function. Example: bool onTrackEnded(AudioPlayerForm *player, EmuStream *stream)
 */
void ebox::AudioPlayerForm::registerOnTrackEndedCallback(const ebox::AudioPlayerForm::func_audioplayertrack &cb)
{
    m_callbackOnTrackEnded.emplace_back(cb);
}

void ebox::AudioPlayerForm::setTrack(int trackNo)
{
    if(m_stream != nullptr)
        m_stream->setTrack(trackNo);
}

void ebox::AudioPlayerForm::play()
{
    m_state = AudioPlayerState::Play;
    if(m_stream != nullptr)
        m_stream->play();
}

void ebox::AudioPlayerForm::stop()
{
    m_state = AudioPlayerState::Stopped;
    if(m_stream != nullptr)
        m_stream->stop();
}

void ebox::AudioPlayerForm::pause()
{
    m_state = AudioPlayerState::Pause;
    if(m_stream != nullptr)
        m_stream->pause();
}

std::string ebox::AudioPlayerForm::getStreamId()
{
    if(m_stream != nullptr)
        return m_stream->getId();

    return nullptr;
}

ebox::EmuStream *ebox::AudioPlayerForm::getCurrentStream()
{
    if(m_stream != nullptr)
        return m_stream.get();

    return nullptr;
}

void ebox::AudioPlayerForm::setIniFile(IniFile *iniFile)
{
    m_iniFile = iniFile;
    m_volume.setValues({m_iniFile->getLastVolume()});
}

float ebox::AudioPlayerForm::getTempo()
{
    return m_tempo.getValue();
}

void ebox::AudioPlayerForm::setPlaylistRepeatPtr(bool *playlistRepeat)
{
    m_playlistRepeat = playlistRepeat;
}
