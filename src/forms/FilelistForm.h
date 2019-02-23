//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_FILELISTFORM_H
#define EMU_JUKEBOX_FILELISTFORM_H

#include "../gui/forms/Form.h"
#include "../gui/controls/TreeList.h"
#include "../gui/controls/Selectable.h"
#include "../audio/EmuStream.h"
#include "../audio/EmuFileInfo.h"
#include "../../content/files_mapper.h"
#include <map>
#include "../classes/Timer.h"
#include "AudioPlayerForm.h"

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

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();

            void onChosenChildNode(Selectable *sender);
            bool onRightClickedChildNode(Selectable *sender);
            void onDoubleClickChildNode(Selectable *sender);
            void onChosenRightClickContextItems(Selectable* owner, MenuItem *sender);

            void setAsSelectedChildNode(Selectable *child);

            //std::map<std::string, EmuStream> m_emuMap;
            std::map<std::string, EmuFileInfo> m_fileMap;
            std::map<std::string, TreeList> m_filelist;
            AudioPlayerForm *m_audioPlayer;

            //TreeList m_filelist {"filelist", "Files"};
            //std::vector<EmuStream> m_files;
    };
}

#endif //EMU_JUKEBOX_FILELISTFORM_H
