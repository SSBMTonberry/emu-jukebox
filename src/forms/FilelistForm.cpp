//
// Created by robin on 03.02.19.
//

#include "FilelistForm.h"

const std::string ebox::FilelistForm::ID = "FilelistForm";

ebox::FilelistForm::FilelistForm(const std::string &id, const std::string &title, const std::string &imguiId) : Form(id, title, imguiId)
{
    initialize();
}

ebox::FilelistForm::FilelistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                 const std::string &imguiId) : Form(position, size, id, title, imguiId)
{
    initialize();
}

bool ebox::FilelistForm::customDraw()
{
    //m_filelist.process();
    ImGui::BeginChild("filelist_btn_panel", {-1, 30}, false, 0);
    ImGui::InputText("Filter search", &m_filter);
    m_removeAllButton.setSpacing(getCurrentWindowSize().x - 40);
    if(m_removeAllButton.process())
        removeAllTracks();
    ImGui::EndChild();
    ImGui::Separator();

    ImGui::BeginChild("filelist_panel", {-1, -1}, false, 0);
    for(auto &[id, value]: m_filelist)
    {
        bool didAddTrack = false;
        if (((m_filter.length() == 0 && value.isOpen()) || m_filter.length() > 0)) {
            m_fileMap[id].loadEmuDataIfNotLoaded();
            didAddTrack = addTracksToFileList(id, m_fileMap[id]);
        }
        if (m_filter.length() == 0 || (didAddTrack || value.getLabel().find(m_filter) != std::string::npos)) {
            value.process();
        }
    }
    ImGui::EndChild();
    return true;
}

void ebox::FilelistForm::initialize()
{
    m_removeAllButton.setOnSameLine(true);
    m_removeAllButton.setTooltip(std::make_optional<Tooltip>("Remove all"));
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

void ebox::FilelistForm::onChosenChildNode(Selectable *sender)
{
    setAsSelectedChildNode(sender);
}

bool ebox::FilelistForm::onRightClickedChildNode(Selectable *sender)
{
    setAsSelectedChildNode(sender);
    sender->createRightClickContextItems({"Add to playlist"});
    return true;
}

void FilelistForm::onChosenParentRightClickContextItems(TreeList *owner, MenuItem *sender)
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
        m_fileMap.erase(owner->getId());
        m_filelist[owner->getId()].clear();
        m_filelist.erase(owner->getId());
        m_lastChosenEmuFile = nullptr;
        m_lastChosenTreeList = nullptr;
        m_lastTrackNo = 0;
        SystemLog::get()->addInfo(fmt::format("'{0}' removed!", id));
    }
}

bool FilelistForm::onRightClickedParentNode(TreeList *sender)
{
    sender->createRightClickContextItems({"Add all songs to playlist", "Remove"});
    return true;
}

void ebox::FilelistForm::onDoubleClickChildNode(Selectable *sender)
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

void ebox::FilelistForm::onChosenRightClickContextItems(Selectable* owner, MenuItem *sender)
{
    if(sender->getLabel() == "Add to playlist" && m_playlist != nullptr)
        addToPlaylist(owner);
}

void FilelistForm::addToPlaylist(Selectable *item)
{
    if(m_fileMap.count(item->getId()) > 0)
    {
        auto *emuFile = &m_fileMap[item->getId()];
        auto *filelistItem = &m_filelist[item->getId()];
        std::vector<Selectable *> songs = filelistItem->getItems();
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

void ebox::FilelistForm::setAsSelectedChildNode(Selectable *child)
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
void FilelistForm::setAudioPlayer(AudioPlayerForm *audioPlayer)
{
    m_audioPlayer = audioPlayer;
    m_audioPlayer->registerOnNextTrackCallback(std::bind(&FilelistForm::onNextTrack, this, std::placeholders::_1));
    m_audioPlayer->registerOnPreviousTrackCallback(std::bind(&FilelistForm::onPreviousTrack, this, std::placeholders::_1));
    m_audioPlayer->registerOnTrackEndedCallback(std::bind(&FilelistForm::onTrackEnded, this, std::placeholders::_1, std::placeholders::_2));
    m_playlist->setPlayer(m_audioPlayer);
}

void FilelistForm::setPlaylist(PlaylistForm *playlist)
{
    m_playlist = playlist;
}

bool FilelistForm::addTracksToFileList(const std::string &id, const EmuFileInfo &info)
{
    bool addedTrack = false;
    auto tracks = info.getTracks();

    for(int i = 0; i < tracks.size(); ++i)
    {
        std::string track = tracks[i];
        if (m_filter.length() == 0 || (m_filter.length() > 0 && track.find(m_filter) != std::string::npos)) {
            int playLength = info.getTrackPlayLengths()[i];
            //std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
            //auto *item = m_filelist[entry.path().filename().string()].add(fmt::format("{0} - {1}", trackNumber, track.getSong()), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
            auto *item = m_filelist[id].add(fmt::format("{0} ({1})", track, tools::string::GetMillisecondsAsTimeString(playLength, false)), &audioImg); //files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
            item->setId(id);
            item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
            item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
            item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
            item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
            addedTrack = true;
        }
    }
    return addedTrack;
}

bool FilelistForm::onNextTrack(AudioPlayerForm *player)
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

bool FilelistForm::onPreviousTrack(AudioPlayerForm *player)
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

bool FilelistForm::onTrackEnded(AudioPlayerForm *player, EmuStream *stream)
{
    return true;
}

void FilelistForm::removeAllTracks()
{
    m_lastChosenTreeList = nullptr;
    m_lastChosenEmuFile = nullptr;
    m_lastTrackNo = 0;
    m_fileMap.clear();
    m_filelist.clear();
    SystemLog::get()->addInfo("Removed all tracks!");
}


