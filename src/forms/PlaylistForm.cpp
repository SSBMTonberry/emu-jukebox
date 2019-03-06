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
    processPlaylistButtonPanel();
    ImGui::BeginChild("playlist_panel", {-1, -1}, false, 0);
    m_filemapping.process();
    ImGui::EndChild();
    return true;
}

void PlaylistForm::processPlaylistButtonPanel()
{
    ImGui::BeginChild("playlist_btn_panel", {-1, 40}, true, 0);
    if(m_shuffleButton.process())
        setShuffle(!m_hasShuffle);
    if(m_repeatButton.process())
        setRepeat(!m_hasRepeat);

    if(m_moveUpButton.process())
        moveItemUp();

    if(m_moveDownButton.process())
        moveItemDown();

    ImGui::EndChild();
}

void ebox::PlaylistForm::initialize()
{
    m_filemapping.setHasParentNode(false);
    m_shuffleButton.setOnSameLine(true);
    m_repeatButton.setOnSameLine(true);
    m_moveUpButton.setOnSameLine(true);
    m_moveDownButton.setOnSameLine(true);

    setShuffle(m_hasShuffle);
    setRepeat(m_hasRepeat);
}

void ebox::PlaylistForm::handleEvents()
{

}

void PlaylistForm::setPlayer(AudioPlayerForm *player)
{
    m_player = player;
    m_player->registerOnNextTrackCallback(std::bind(&PlaylistForm::onNextTrack, this, std::placeholders::_1));
    m_player->registerOnPreviousTrackCallback(std::bind(&PlaylistForm::onPreviousTrack, this, std::placeholders::_1));
    m_player->registerOnTrackEndedCallback(std::bind(&PlaylistForm::onTrackEnded, this, std::placeholders::_1, std::placeholders::_2));
}

void ebox::PlaylistForm::add(const ebox::EmuFileInfo &fileInfo, int trackNumber)
{
    m_playlist.emplace_back(fileInfo, trackNumber);
    std::string id = getId(m_playlist.size()-1);
    m_playlist[m_playlist.size()-1].first.setId(id);

    auto *item = m_filemapping.add(id, fmt::format("{0} - {1}", fileInfo.getGameName(), fmt::format("{0} ({1})", fileInfo.getTracks()[trackNumber],
                                       tools::string::GetMillisecondsAsTimeString(fileInfo.getTrackPlayLengths()[trackNumber], false))));

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
    sender->createRightClickContextItems({"Play", "Remove"});
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
                loadEmuFile(&emuFile, trackNo);
            }
        }
    }
    else if(sender->getId() == "remove")
    {
        for(int i = 0; i < m_playlist.size(); ++i)
            if(m_playlist[i].first.getId() == owner->getId()) m_playlist.erase(m_playlist.begin()+i);

        m_filemapping.remove(owner->getId());

    }
}

void ebox::PlaylistForm::setAsSelectedChildNode(ebox::Selectable *child)
{
    for (auto const &item : m_filemapping.getItems())
    {
        item->setSelected(item == child);
    }
}

void PlaylistForm::setAsSelectedChildNode(const std::string &id)
{
    for (auto const &item : m_filemapping.getItems())
    {
        item->setSelected(item->getId() == id);
    }
}

bool PlaylistForm::onNextTrack(AudioPlayerForm *player)
{
    if(m_player != nullptr && containsId(m_player->getStream()->getId()))
    {
        if(m_hasShuffle)
            startRandomTrack(m_player->getStream()->getId());
        else
            startNextTrack(m_player->getStream()->getId());
        return true;
    }

    return false;
}

bool PlaylistForm::onPreviousTrack(AudioPlayerForm *player)
{
    if(m_player != nullptr && containsId(m_player->getStream()->getId()))
    {
        if(m_hasShuffle)
            startRandomTrack(m_player->getStream()->getId());
        else
            startPreviousTrack(m_player->getStream()->getId());
        return true;
    }

    return false;
}

bool PlaylistForm::containsId(const std::string &id)
{
    for(auto const &[emu, trackNo] : m_playlist)
        if(emu.getId() == id) return true;

    return false;
}

bool PlaylistForm::onTrackEnded(AudioPlayerForm *player, EmuStream *stream)
{
    if(m_player != nullptr && containsId(stream->getId()))
    {
        if(m_hasRepeat)
            startTrack(m_player->getStream()->getId());
        else if(m_hasShuffle)
            startRandomTrack(m_player->getStream()->getId());
        else
            startNextTrack(stream->getId());
        return true;
    }
    return false;
}

void PlaylistForm::startNextTrack(const std::string &currentId)
{
    if(m_playlist.size() > 0)
    {
        int index = getIndex(currentId);
        ++index;
        if (index > m_playlist.size() - 1)
            loadEmuFile(&m_playlist[0].first, m_playlist[0].second);
        else
            loadEmuFile(&m_playlist[index].first, m_playlist[index].second);
    }
}

void PlaylistForm::startPreviousTrack(const std::string &currentId)
{
    if(m_playlist.size() > 0)
    {
        int maxIndex = m_playlist.size() - 1;
        int index = getIndex(currentId);
        --index;

        if (index < 0)
            loadEmuFile(&m_playlist[maxIndex].first, m_playlist[maxIndex].second);
        else
            loadEmuFile(&m_playlist[index].first, m_playlist[index].second);
    }
}

void PlaylistForm::startTrack(const std::string &currentId)
{
    if(m_playlist.size() > 0)
    {
        int index = getIndex(currentId);
        loadEmuFile(&m_playlist[index].first, m_playlist[index].second);
    }
}

void PlaylistForm::startRandomTrack(const std::string &currentId)
{
    if(m_playlist.size() > 1)
    {
        std::random_device device;
        std::mt19937 gen(device()); //std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, m_playlist.size() - 1);
        int number = distribution(gen);
        startTrack(m_playlist[number].first.getId());
    }
    else if(m_playlist.size() == 1)
    {
        startTrack(currentId);
    }
}

int PlaylistForm::getIndex(const std::string &id)
{
    for(int i = 0; i < m_playlist.size(); ++i)
    {
        if (m_playlist[i].first.getId() == id)
            return i;
    }

    return -1;
}

bool PlaylistForm::loadEmuFile(EmuFileInfo *emuFileInfo, int trackNo)
{
    if(emuFileInfo->exists())
    {
        setAsSelectedChildNode(emuFileInfo->getId());

        SystemLog::get()->addInfo(fmt::format("'{0}' loaded! Track number: {1}", emuFileInfo->getFilename(), trackNo));
        bool isValid = m_player->createStream(*emuFileInfo);
        if (isValid && m_player->getStream() != nullptr)
        {
            m_player->getStream()->stop();
            m_player->getStream()->setTrack(trackNo);
            m_player->getStream()->play();
            return true;
        }
    }
    else
        SystemLog::get()->addError(fmt::format("File '{0}' no longer exists!", emuFileInfo->getPath().string()));

    return false;
}

void PlaylistForm::setShuffle(bool shuffle)
{
    m_hasShuffle = shuffle;
    m_shuffleButton.getImage()->setColor(shuffle ? sf::Color(242, 242, 242, 255) : sf::Color(173, 22, 22, 255));
}

void PlaylistForm::setRepeat(bool repeat)
{
    m_hasRepeat = repeat;
    m_repeatButton.getImage()->setColor(repeat ? sf::Color(242, 242, 242, 255) : sf::Color(173, 22, 22, 255));
}

void PlaylistForm::moveItemUp()
{
    int index = getSelectedIndex();
    if(index > -1 && index > 0)
    {
        int swapIndex = index - 1;
        auto selected = m_filemapping.getItemId(index);
        auto toSwap = m_filemapping.getItemId(swapIndex);

        //Swap the actual items
        m_filemapping.swap(selected.data(), toSwap.data());
    }
}

void PlaylistForm::moveItemDown()
{
    int index = getSelectedIndex();
    if(index > -1 && index < (m_filemapping.getItems().size() - 1))
    {
        int swapIndex = index + 1;
        auto selected = m_filemapping.getItemId(index);
        auto toSwap = m_filemapping.getItemId(swapIndex);

        //Swap the actual items
        m_filemapping.swap(selected.data(), toSwap.data());
    }
}

Selectable *PlaylistForm::getSelected()
{
    for (int i = 0; i < m_filemapping.getItems().size(); ++i)
    {
        auto item = m_filemapping.getItems()[i];
        if(item->isSelected())
            return item;
    }

    return nullptr;
}

int PlaylistForm::getSelectedIndex()
{
    for (int i = 0; i < m_filemapping.getItems().size(); ++i)
    {
        auto item = m_filemapping.getItems()[i];
        if(item->isSelected())
            return i;
    }
    return -1;
}

EmuFileInfo *PlaylistForm::getEmuFileInfo(const std::string &id)
{
    for(int i = 0; i < m_playlist.size(); ++i)
    {
        if(m_playlist[i].first.getId() == id)
            return &m_playlist[i].first;
    }

    return nullptr;
}
