//
// Created by robin on 22.02.19.
//

#ifndef EMU_JUKEBOX_EMUFILEINFO_H
#define EMU_JUKEBOX_EMUFILEINFO_H
#include "../../EmuJukeboxConfig.h"

//#if MSVC
//#include <filesystem>
//    namespace fs = std::filesystem;
//#elif MINGW
//#if __MINGW64_VERSION_MAJOR > 6
//        #include <filesystem>
//        namespace fs = std::filesystem;
//    #else
//        #include <experimental/filesystem>
//        namespace fs = std::experimental::filesystem;
//    #endif
//#elif APPLE
//#include <experimental/filesystem>
//        namespace fs = std::experimental::filesystem;
//#else
//#if __GNUC__ < 8 //GCC major version less than 8
//#include <experimental/filesystem>
//                namespace fs = std::experimental::filesystem;
//#else
//#include <filesystem>
//namespace fs = std::filesystem;
//#endif
//#endif

//#include "libgme/gme_types.h"
#include <Music_Emu.h>

#include "../forms/SystemLog.h"

namespace ebox
{
    class EmuFileInfo
    {
        public:
            EmuFileInfo();
            EmuFileInfo(const fs::path &path, bool runLoadEmu = false);

            bool loadFile(const fs::path &path);
            bool loadEmuData();
            bool loadEmuDataIfNotLoaded();

            void setId(const std::string &id);

            const std::string &getId() const;
            const std::filesystem::path &getPath() const;
            const std::string &getFilename() const;
            const std::string &getGameName() const;
            const std::string &getExtension() const;
            int getNumberOfTracks() const;
            const std::string &getDisplayName() const;
            const std::vector<std::string> &getTracks() const;
            const std::vector<int> &getTrackPlayLengths() const;

            bool isValid() const;
            bool exists();

        private:
            void freeEmu(Music_Emu *emu);
            bool isValidFileType();
            bool handleError(const char *errorText);

            fs::path m_path;
            std::string m_id;
            std::string m_filename;
            std::string m_gameName;
            std::string m_extension; //.nsf/.nsfe/.spc etc...
            int m_numberOfTracks {0};
            bool m_isValid = false;
            bool m_emuDataLoaded = false;


            std::string m_displayName; //Name displayed in list
            std::vector<std::string> m_tracks;
            std::vector<int> m_trackPlayLengths;
            std::vector<bool> m_trackLengthDefined;
    };
}

#endif //EMU_JUKEBOX_EMUFILEINFO_H
