//
// Created by robin on 03.02.19.
//

#include "PlaylistForm.h"

const std::string ebox::PlaylistForm::ID = "PlaylistForm";

ebox::PlaylistForm::PlaylistForm(const std::string &id, const std::string &title, const std::string &imguiId) : Form(id, title, imguiId)
{
    initialize();
}

ebox::PlaylistForm::PlaylistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                                 const std::string &imguiId) : Form(position, size, id, title, imguiId)
{
    initialize();
}

bool ebox::PlaylistForm::customDraw()
{
    m_filemapping.process();
    return true;
}

void ebox::PlaylistForm::initialize()
{
    m_filemapping.setHasParentNode(false);
}

void ebox::PlaylistForm::handleEvents()
{

}

void PlaylistForm::setPlayer(AudioPlayerForm *player)
{
    m_player = player;
}

void ebox::PlaylistForm::add(const ebox::EmuFileInfo &fileInfo, int trackNumber)
{
    m_playlist.emplace_back(fileInfo, trackNumber);
    std::string id = getId(m_playlist.size()-1);
    m_playlist[m_playlist.size()-1].first.setId(id);
    auto *item = m_filemapping.add(id, fmt::format("{0} - {1}", fileInfo.getGameName(), fileInfo.getTracks()[trackNumber]));

    item->registerOnChosenCallback(std::bind(&PlaylistForm::onChosenChildNode, this, std::placeholders::_1));
    item->registerOnRightClickCallback(std::bind(&PlaylistForm::onRightClickedChildNode, this, std::placeholders::_1));
    item->registerOnDoubleClickCallback(std::bind(&PlaylistForm::onDoubleClickChildNode, this, std::placeholders::_1));
    item->registerOnChosenContextItemCallback(std::bind(&PlaylistForm::onChosenRightClickContextItems, this, std::placeholders::_1, std::placeholders::_2));

    SystemLog::get()->addDebug(fmt::format("Playlist - added item with id '{0}': {1}", id, item->getLabel()));
}

std::string ebox::PlaylistForm::getId(size_t number, int digits)
{
    std::string num = fmt::format("{0}", number);
    int remainingDigits = digits - num.length();
    std::string zeroes = "";
    for(int i = 0; i < remainingDigits; ++i)
        zeroes += "0";

    return fmt::format("{0}{1}", zeroes, num);
}

std::string PlaylistForm::getId(const std::pair<EmuFileInfo, int> &item)
{
    return fmt::format("{0} - {1}", item.first.getGameName(), item.first.getTracks()[item.second]);
}


void ebox::PlaylistForm::onChosenChildNode(ebox::Selectable *sender)
{
    setAsSelectedChildNode(sender);
}

bool ebox::PlaylistForm::onRightClickedChildNode(ebox::Selectable *sender)
{
    setAsSelectedChildNode(sender);
    sender->createRightClickContextItems({"Play"});
    return true;
}

void ebox::PlaylistForm::onDoubleClickChildNode(ebox::Selectable *sender)
{
    for(auto &[emuFile, trackNo] : m_playlist)
    {
        if (sender->getId() == emuFile.getId())
        {
            if(emuFile.exists())
            {
                SystemLog::get()->addInfo(fmt::format("'{0}' loaded! Track number: {1}", sender->getLabel(), trackNo));
                bool isValid = m_player->createStream(emuFile);
                if (isValid && m_player->getStream() != nullptr)
                {
                    m_player->getStream()->stop();
                    m_player->getStream()->setTrack(trackNo);
                    m_player->getStream()->play();
                }
            }
            else
                SystemLog::get()->addError(fmt::format("File '{0}' no longer exists!", emuFile.getPath().string()));
        }
    }
}

void ebox::PlaylistForm::onChosenRightClickContextItems(ebox::Selectable *owner, ebox::MenuItem *sender)
{
    if(sender->getId() == "play")
    {
        for(auto &[emuFile, trackNo] : m_playlist)
        {
            if (owner->getId() == emuFile.getId())
            {
                if(emuFile.exists())
                {
                    SystemLog::get()->addInfo(fmt::format("'{0}' loaded! Track number: {1}", sender->getLabel(), trackNo));
                    bool isValid = m_player->createStream(emuFile);
                    if (isValid && m_player->getStream() != nullptr)
                    {
                        m_player->getStream()->stop();
                        m_player->getStream()->setTrack(trackNo);
                        m_player->getStream()->play();
                    }
                }
                else
                    SystemLog::get()->addError(fmt::format("File '{0}' no longer exists!", emuFile.getPath().string()));
            }
        }
    }
}

void ebox::PlaylistForm::setAsSelectedChildNode(ebox::Selectable *child)
{
    for (auto const &item : m_filemapping.getItems())
    {
        item->setSelected(item == child);
    }
}
