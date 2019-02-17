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
        auto item = m_filemap.emplace(path.filename().string(), EmuStream(path.string()));
        if(!item.first->second.isValid())
            m_filemap.erase(path.filename().string());
        else
        {
            m_filelist[path.filename().string()] = {path.filename().string(), path.filename().string()};

            //for(auto const &item : m_filemap[path.filename().string()].getTrack())
            int numberOfTracks = m_filemap[path.filename().string()].getInfo().getNumberOfTracks();
            for(int i = 0; i < numberOfTracks; ++i)
            {
                std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
                auto *item = m_filelist[path.filename().string()].add(fmt::format("Track {0}", trackNumber), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                item->getImage()->setHasZoomTooltip(false);

                item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
                item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
                item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
                item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
            }
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

                auto item = m_filemap.emplace(entry.path().filename().string(), EmuStream(entry.path().string()));
                if(!item.first->second.isValid())
                    m_filemap.erase(entry.path().filename().string());
                else
                {
                    m_filelist[entry.path().filename().string()] = {entry.path().filename().string(), entry.path().filename().string()};

                    //for(auto const &item : m_filemap[path.filename().string()].getTrack())
                    int numberOfTracks = m_filemap[entry.path().filename().string()].getInfo().getNumberOfTracks();
                    for(int i = 0; i < numberOfTracks; ++i)
                    {
                        std::string trackNumber = (i < 9) ? fmt::format("0{0}", i+1) : fmt::format("{0}", i+1);
                        auto *item = m_filelist[entry.path().filename().string()].add(fmt::format("Track {0}", trackNumber), files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                        item->getImage()->setHasZoomTooltip(false);

                        item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
                        item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
                        item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
                        item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
                    }
                    //auto *item = m_filelist.add(entry.path().filename().string(), files_mapper::gui::filetypes::_AUDIO_PNG,
                    //               files_mapper::gui::filetypes::_AUDIO_PNG_SIZE);
                    //item->getImage()->setHasZoomTooltip(false);
//
                    //item->registerOnChosenCallback(std::bind(&FilelistForm::onChosenChildNode, this, std::placeholders::_1));
                    //item->registerOnRightClickCallback(std::bind(&FilelistForm::onRightClickedChildNode, this, std::placeholders::_1));
                    //item->registerOnDoubleClickCallback(std::bind(&FilelistForm::onDoubleClickChildNode, this, std::placeholders::_1));
                    //item->registerOnChosenContextItemCallback(std::bind(&FilelistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));
                }
                ++processedFiles;
            }
        }
        timer.end();
        SystemLog::get()->addInfo(timer.getTimeElapsedMessage(fmt::format("Processed {0} files from {1} - ",processedFiles, folder.string())));
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
