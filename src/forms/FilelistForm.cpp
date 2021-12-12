//
// Created by robin on 03.02.19.
//

#include "FilelistForm.h"

const std::string ebox::FilelistForm::ID = "FilelistForm";

ebox::FilelistForm::FilelistForm(const std::string &id, const std::string &title) : Form(id, title)
{
    initialize();
}

ebox::FilelistForm::FilelistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title)
                                 : Form(position, size, id, title)
{
    initialize();
}

bool ebox::FilelistForm::onDraw()
{
    float scaleFactor = m_iniFile->getFontManager()->getFontSizeFactor();

    if (m_eraseItems.size() > 0) {
        for (auto id : m_eraseItems) {
            m_fileMap.erase(id);
            m_filelist[id].clear();
            m_filelist.erase(id);
            SystemLog::get()->addInfo(fmt::format("'{0}' removed!", id));
        }
        m_lastChosenEmuFile = nullptr;
        m_lastChosenTreeList = nullptr;
        m_lastTrackNo = 0;
        m_eraseItems.clear();
    }


    //m_filelist.process();
    ImGui::BeginChild("filelist_btn_panel", {-1, 30}, false, 0);
    if (m_filterTextbox.process()) {
        for (auto &[id, value] : m_filelist) {
            auto haystack = value.getLabel().begin();
            auto haystackEnd = value.getLabel().end();
            auto needle = m_filterTextbox.getValue().begin();
            auto needleEnd = m_filterTextbox.getValue().end();
            auto predicate = [](char ch1, char ch2) -> int { return std::toupper(ch1) == std::toupper(ch2); };
            bool isVisible = (m_filterTextbox.getValue().empty() || haystackEnd != std::search(haystack, haystackEnd, needle, needleEnd, predicate));
            value.setIsVisible(isVisible);
        }
    }

    int buttonSpace = 32;
    int spacing = getCurrentWindowSize().x - m_filterTextbox.getControlSize().x - (45 * scaleFactor) - buttonSpace;

    //m_addAllButton.setSpacing(spacing); //(40); //getCurrentWindowSize().x);
    if(m_addAllButton.process() && !m_isAddingTracksToPlaylist)
    {
        m_isAddingTracksToPlaylist = true;
        m_progressbar.setCurrentProgress(0.f);
        m_filesLoaded = 0;
        m_totalTracks = 0;
        m_fileLoadTimer.reset();
        m_fileLoadTimer.start();
    }

    m_removeAllButton.setSpacing(spacing); //(40); //getCurrentWindowSize().x);
    if(m_removeAllButton.process())
        removeAllTracks();

    ImGui::EndChild();

    ImGui::Separator();
    if(m_isAddingTracksToPlaylist)
    {
        addAllTracksToPlaylist();
        m_progressbar.process();
        ImGui::Separator();
    }

    ImGui::BeginChild("filelist_panel", {-1, -1}, false, 0);
    for (auto &[id, value] : m_filelist)
    {
        value.process();
        if (value.isOpen() && m_fileMap[id].loadEmuDataIfNotLoaded())
        {
            addTracksToFileList(id, m_fileMap[id]);
        }
    }
    ImGui::EndChild();
    return true;
}

void ebox::FilelistForm::initialize()
{
    m_addAllButton.setOnSameLine(true);
    m_addAllButton.setTooltip(pmgui::Tooltip("Add all tracks to playlist"));
    m_removeAllButton.setOnSameLine(true);
    m_removeAllButton.setTooltip(std::make_optional<pmgui::Tooltip>("Remove all"));
    m_progressbar.setCurrentProgress(10.f);
    //m_filelist.setHasParentNode(false);
}

void ebox::FilelistForm::handleEvents()
{

}

void ebox::FilelistForm::loadFile(const fs::path &path)
{
    if(fs::is_regular_file(path))
    {
        Timer timer {true};
        //auto item = m_fileMap.emplace(path.filename().string(), EmuFileInfo(path.string()));
        m_fileMap[path.filename().string()] = EmuFileInfo(path.string());
        if(!m_fileMap[path.filename().string()].isValid())
            m_fileMap.erase(path.filename().string());
        else
        {
            m_fileMap[path.filename().string()].setId(path.filename().string());
            m_filelist[path.filename().string()] = {path.filename().string(), path.filename().string()};

            m_filelist[path.filename().string()].registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedParentNode, this, std::placeholders::_1));
            m_filelist[path.filename().string()].registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenParentRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));

            timer.end();
            SystemLog::get()->addInfo(timer.getTimeElapsedMessage(fmt::format("Processed file '{0}' - ", path.string())));
        }
    }
}

void ebox::FilelistForm::loadAllFilesInFolder(const fs::path &folder)
{
    if(fs::is_directory(folder))
    {
        Timer timer {true};
        int processedFiles = 0;
        for (const auto &entry : fs::directory_iterator(folder))
        {
            if (fs::is_regular_file(entry.status()))
            {
                //m_fileMap.emplace(entry.path().filename().string(), EmuFileInfo(entry.path().string()));
                m_fileMap[entry.path().filename().string()] = EmuFileInfo(entry.path().string());
                if(!m_fileMap[entry.path().filename().string()].isValid())
                    m_fileMap.erase(entry.path().filename().string());
                else
                {
                    m_fileMap[entry.path().filename().string()].setId(entry.path().filename().string());
                    m_filelist[entry.path().filename().string()] = {entry.path().filename().string(), entry.path().filename().string()};
                    m_filelist[entry.path().filename().string()].registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedParentNode, this, std::placeholders::_1));
                    m_filelist[entry.path().filename().string()].registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenParentRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
                }
                ++processedFiles;
            }
        }
        timer.end();
        SystemLog::get()->addInfo(timer.getTimeElapsedMessage(fmt::format("Processed {0} files from {1}. File list size is now: {2} ",processedFiles, folder.string(), m_filelist.size())));
    }
}

void ebox::FilelistForm::onChosenChildNode(pmgui::Selectable *sender)
{
    setAsSelectedChildNode(sender);
}

bool ebox::FilelistForm::onRightClickedChildNode(pmgui::Selectable *sender)
{
    setAsSelectedChildNode(sender);
    sender->createRightClickContextItems({"Add to playlist"});
    return true;
}

void ebox::FilelistForm::onChosenParentRightClickContextItems(pmgui::TreeList *owner, pmgui::MenuItem *sender)
{
    if(sender->getId() == "add all songs to playlist")
    {
        if(m_fileMap[owner->getId()].loadEmuDataIfNotLoaded())
            addTracksToFileList(owner->getId(), m_fileMap[owner->getId()]);

        for(auto item : owner->getItems())
            addToPlaylist(item);
    }
    else if(sender->getId() == "remove")
    {
        std::string id = owner->getId();
        m_eraseItems.push_back(id);
    }
}

bool ebox::FilelistForm::onRightClickedParentNode(pmgui::TreeList *sender)
{
    sender->createRightClickContextItems({"Add all songs to playlist", "Remove"});
    return true;
}

void ebox::FilelistForm::onDoubleClickChildNode(pmgui::Selectable *sender)
{
    setAsSelectedChildNode(sender);
    if(m_fileMap.count(sender->getId()) > 0)
    {
        auto *emuFile = &m_fileMap[sender->getId()];
        auto *filelistItem = &m_filelist[sender->getId()];
        std::vector<Selectable*> songs = filelistItem->getItems();
        int trackNo = 0;
        bool songFound = false;
        for(int i = 0; i < songs.size(); ++i)
        {
            if(sender == songs[i])
            {
                songFound = true;
                trackNo = i;
            }
        }

        if(songFound)
        {
            if(emuFile->exists())
            {
                SystemLog::get()->addInfo(fmt::format("'{0}' loaded! Track number: {1}", sender->getLabel(), trackNo));
                bool isValid = m_audioPlayer->createStream(*emuFile);
                if (isValid)
                {
                    m_lastChosenEmuFile = emuFile;
                    m_lastChosenTreeList = filelistItem;
                    m_lastTrackNo = trackNo;

                    m_audioPlayer->stop();
                    m_audioPlayer->setTrack(trackNo);
                    m_audioPlayer->play();
                }
            }
            else
                SystemLog::get()->addError(fmt::format("File '{0}' no longer exists!", emuFile->getPath().string()));

            //emuFile->setTrack(trackNo);
            //if(m_audioPlayer->getStream() != nullptr) m_audioPlayer->getStream()->stop();
            //m_audioPlayer->setStream(emuFile);
            //if(m_audioPlayer->getStream() != nullptr) m_audioPlayer->getStream()->play();
        }
        else
            SystemLog::get()->addError(fmt::format("Could not identify track '{0}' related to '{1}'!", sender->getLabel(), sender->getId()));
    }
    else
        SystemLog::get()->addError(fmt::format("{0} does not exist!", sender->getId()));
}

void ebox::FilelistForm::onChosenRightClickContextItems(pmgui::Selectable* owner, pmgui::MenuItem *sender)
{
    if(sender->getLabel() == "Add to playlist" && m_playlist != nullptr)
        addToPlaylist(owner);
}

void ebox::FilelistForm::addToPlaylist(pmgui::Selectable *item)
{
    if(m_fileMap.count(item->getId()) > 0)
    {
        auto *emuFile = &m_fileMap[item->getId()];
        auto *filelistItem = &m_filelist[item->getId()];
        std::vector<pmgui::Selectable *> songs = filelistItem->getItems();
        int trackNo = 0;
        bool songFound = false;
        for (int i = 0; i < songs.size(); ++i)
        {
            if (item == songs[i])
            {
                songFound = true;
                trackNo = i;
            }
        }

        if (songFound)
        {
            m_playlist->add(*emuFile, trackNo);
        }
    }
}

void ebox::FilelistForm::setAsSelectedChildNode(pmgui::Selectable *child)
{
    for(auto &[id, value]: m_filelist)
    {
        for(auto const &item : value.getItems())
        {
            item->setSelected(item == child);
        }
    }
    //for(auto const &item : m_filelist.getItems())
    //{
    //    item->setSelected(item == child);
    //}
}

/*!
 * Remember to call setPlaylist() first, as this sets the playlist of both.
 * @param audioPlayer
 */
void ebox::FilelistForm::setAudioPlayer(AudioPlayerForm *audioPlayer)
{
    m_audioPlayer = audioPlayer;
    m_audioPlayer->registerOnNextTrackCallback(std::bind(&FilelistForm::onNextTrack, this, std::placeholders::_1));
    m_audioPlayer->registerOnPreviousTrackCallback(std::bind(&FilelistForm::onPreviousTrack, this, std::placeholders::_1));
    m_audioPlayer->registerOnTrackEndedCallback(std::bind(&FilelistForm::onTrackEnded, this, std::placeholders::_1, std::placeholders::_2));
    m_playlist->setPlayer(m_audioPlayer);
}

void ebox::FilelistForm::setPlaylist(PlaylistForm *playlist)
{
    m_playlist = playlist;
}

void ebox::FilelistForm::addTracksToFileList(const std::string &id, const EmuFileInfo &info)
{
    auto tracks = info.getTracks();

    for(int i = 0; i < tracks.size(); ++i)
    {
        std::string track = tracks[i];
        int playLength = info.getTrackPlayLengths()[i];
        //std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
        //auto *item = m_filelist[entry.path().filename().string()].add(fmt::format("{0} - {1}", trackNumber, track.getSong()), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
        auto *item = m_filelist[id].add(fmt::format("{0} ({1})", track, tools::string::GetMillisecondsAsTimeString(playLength, false)), &audioImg); //files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
        item->setId(id);
        item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
        item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
        item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
        item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
    }
}

bool ebox::FilelistForm::onNextTrack(AudioPlayerForm *player)
{
    if(m_lastChosenTreeList != nullptr && m_lastChosenEmuFile != nullptr && m_lastChosenEmuFile->getId() == player->getStreamId())
    {
        auto items = m_lastChosenTreeList->getItems();
        ++m_lastTrackNo;
        if (m_lastTrackNo > items.size() - 1)
            m_lastTrackNo = 0;

        setAsSelectedChildNode(items[m_lastTrackNo]);
    }
    return false;
}

bool ebox::FilelistForm::onPreviousTrack(AudioPlayerForm *player)
{
    if(m_lastChosenTreeList != nullptr && m_lastChosenEmuFile != nullptr && m_lastChosenEmuFile->getId() == player->getStreamId())
    {
        auto items = m_lastChosenTreeList->getItems();
        --m_lastTrackNo;
        if (m_lastTrackNo < 0)
            m_lastTrackNo = items.size() - 1;

        setAsSelectedChildNode(items[m_lastTrackNo]);
    }
    return false;
}

bool ebox::FilelistForm::onTrackEnded(AudioPlayerForm *player, EmuStream *stream)
{
    return (m_iniFile->loopPreviewTracksForever()) ? true : false;
}

void ebox::FilelistForm::removeAllTracks()
{
    m_lastChosenTreeList = nullptr;
    m_lastChosenEmuFile = nullptr;
    m_lastTrackNo = 0;
    m_fileMap.clear();
    m_filelist.clear();
    SystemLog::get()->addInfo("Removed all tracks!");
}

void ebox::FilelistForm::addAllTracksToPlaylist()
{
    size_t totalFiles = m_fileMap.size();
    int currentlyLoadedFiles = 0;
    int fileBatchSize = 100;
    //for(auto &[id, emuFile] : m_fileMap)
    for(int i = m_filesLoaded; i < totalFiles; ++i)
    {
        auto it = std::next(m_fileMap.begin(), i);
        auto &id = it->first;
        auto &emuFile = it->second;

        if(emuFile.loadEmuDataIfNotLoaded())
            addTracksToFileList(id, m_fileMap[id]);

        size_t tracks = emuFile.getTracks().size();
        for(int i = 0; i < tracks; ++i)
        {
            m_playlist->add(emuFile, i);
            ++m_totalTracks;
        }
        ++m_filesLoaded;
        ++currentlyLoadedFiles;
        if(currentlyLoadedFiles >= fileBatchSize)
            break;
    }

    float progress = ((float)m_filesLoaded / (float)totalFiles) * 100;
    m_progressbar.setCurrentProgress(progress);

    if(m_filesLoaded >= totalFiles)
    {
        m_isAddingTracksToPlaylist = false;
        m_fileLoadTimer.end();
        std::string msg = fmt::format("Added a total of {0} tracks from {1} files (of {2}) to playlist!", m_totalTracks, m_filesLoaded, totalFiles);
        SystemLog::get()->addInfo(m_fileLoadTimer.getTimeElapsedMessage(msg));
    }
}

void ebox::FilelistForm::setIniFile(IniFile *iniFile)
{
    m_iniFile = iniFile;
}
