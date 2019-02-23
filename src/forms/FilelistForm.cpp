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
    for(auto &[id, value]: m_filelist)
    {
        value.process();
        if(value.isOpen() && m_fileMap[id].loadEmuDataIfNotLoaded())
        {
            addTracksToFileList(id, m_fileMap[id]);
        }
    }
    return true;
}

void ebox::FilelistForm::initialize()
{
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
            m_filelist[path.filename().string()] = {path.filename().string(), path.filename().string()};

            /*auto tracks = m_fileMap[path.filename().string()].getTracks();
            for(int i = 0; i < tracks.size(); ++i)
            {
                std::string track = tracks[i];
                //std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
                //auto *item = m_filelist[path.filename().string()].add(fmt::format("{0} - {1}", trackNumber, track.getSong()), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                auto *item = m_filelist[path.filename().string()].add(track, files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                item->getImage()->setHasZoomTooltip(false);
                item->setId(path.filename().string());

                item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
                item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
                item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
                item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
            }*/
            timer.end();
            SystemLog::get()->addInfo(timer.getTimeElapsedMessage(fmt::format("Processed file '{0}' - ", path.string())));
            //m_filelist.add(path.filename().string(), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
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
                    m_filelist[entry.path().filename().string()] = {entry.path().filename().string(), entry.path().filename().string()};

                    /*auto tracks = m_fileMap[entry.path().filename().string()].getTracks();

                    for(int i = 0; i < tracks.size(); ++i)
                    {
                        std::string track = tracks[i];
                        //std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
                        //auto *item = m_filelist[entry.path().filename().string()].add(fmt::format("{0} - {1}", trackNumber, track.getSong()), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                        auto *item = m_filelist[entry.path().filename().string()].add(track, files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                        item->getImage()->setHasZoomTooltip(false);
                        item->setId(entry.path().filename().string());

                        item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
                        item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
                        item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
                        item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
                    }*/
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
    sender->createRightClickContextItems({"Dummy1", "Dummy2"});
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
                m_audioPlayer->createStream(*emuFile);
                if (m_audioPlayer->getStream() != nullptr)
                {
                    m_audioPlayer->getStream()->stop();
                    m_audioPlayer->getStream()->setTrack(trackNo);
                    m_audioPlayer->getStream()->play();
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

void FilelistForm::setAudioPlayer(AudioPlayerForm *audioPlayer)
{
    m_audioPlayer = audioPlayer;
}

void FilelistForm::addTracksToFileList(const std::string &id, const EmuFileInfo &info)
{
    auto tracks = info.getTracks();

    for(int i = 0; i < tracks.size(); ++i)
    {
        std::string track = tracks[i];
        //std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
        //auto *item = m_filelist[entry.path().filename().string()].add(fmt::format("{0} - {1}", trackNumber, track.getSong()), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
        auto *item = m_filelist[id].add(track, files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
        item->getImage()->setHasZoomTooltip(false);
        item->setId(id);

        item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
        item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
        item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
        item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
    }
}
