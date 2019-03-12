//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_FILELISTFORM_H
#define EMU_JUKEBOX_FILELISTFORM_H

#include "../misc/Tools.hpp"
#include "../gui/forms/Form.h"
#include "../gui/controls/TreeList.h"
#include "../gui/controls/Selectable.h"
#include "../audio/EmuStream.h"
#include "../audio/EmuFileInfo.h"
#include "../../content/files_mapper.h"
#include <map>
#include "../classes/Timer.h"
#include "AudioPlayerForm.h"
#include "PlaylistForm.h"

#if MSVC
#include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
#if __MINGW64_VERSION_MAJOR > 6
        #include <filesystem>
        namespace fs = std::filesystem;
    #else
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#elif APPLE
#include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
#else
#if __GNUC__ < 8 //GCC major version less than 8
#include <experimental/filesystem>
                namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif

namespace ebox
{
    class FilelistForm : public Form
    {
        public:
            FilelistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            FilelistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            void loadFile(const fs::path & path);
            void loadAllFilesInFolder(const fs::path & folder);

            void setAudioPlayer(AudioPlayerForm *audioPlayer);
            void setPlaylist(PlaylistForm *playlist);

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();

            void addTracksToFileList(const std::string &id, const EmuFileInfo &info);
            void addToPlaylist(Selectable* item);
            void removeAllTracks();

            bool onRightClickedParentNode(TreeList *sender);
            void onChosenParentRightClickContextItems(TreeList * owner, MenuItem *sender);

            void onChosenChildNode(Selectable *sender);
            bool onRightClickedChildNode(Selectable *sender);
            void onDoubleClickChildNode(Selectable *sender);
            void onChosenRightClickContextItems(Selectable* owner, MenuItem *sender);

            bool onNextTrack(AudioPlayerForm *player);
            bool onPreviousTrack(AudioPlayerForm *player);
            bool onTrackEnded(AudioPlayerForm *player, EmuStream *stream);

            void setAsSelectedChildNode(Selectable *child);

            //std::map<std::string, EmuStream> m_emuMap;
            std::map<std::string, EmuFileInfo> m_fileMap;
            std::map<std::string, TreeList> m_filelist;

            //Stored when choosing an item to play
            TreeList *m_lastChosenTreeList = nullptr;
            EmuFileInfo *m_lastChosenEmuFile = nullptr;
            int m_lastTrackNo = 0;

            AudioPlayerForm *m_audioPlayer;
            PlaylistForm *m_playlist;
            std::string m_filter;

            ebox::Image audioImg = {"audio_img", files_mapper::gui::filetypes::_AUDIO_PNG, files_mapper::gui::filetypes::_AUDIO_PNG_SIZE, false};

            ebox::ImageButton m_removeAllButton {"remove_all_button", files_mapper::gui::debugger::_KILLPROCESS_PNG, files_mapper::gui::debugger::_KILLPROCESS_PNG_SIZE, sf::Vector2i(30, 30)};
            //TreeList m_filelist {"filelist", "Files"};
            //std::vector<EmuStream> m_files;
    };
}

#endif //EMU_JUKEBOX_FILELISTFORM_H
