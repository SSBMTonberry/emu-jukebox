//
// Created by robin on 22.02.19.
//

#ifndef EMU_JUKEBOX_EMUFILEINFO_H
#define EMU_JUKEBOX_EMUFILEINFO_H

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

#include "libgme/gme_types.h"
#include "libgme/Music_Emu.h"

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

        private:
            bool handleError(const char *errorText);

            fs::path m_path;
            std::string m_filename;
            int m_numberOfTracks;
            std::vector<std::string> m_tracks;
    };
}

#endif //EMU_JUKEBOX_EMUFILEINFO_H
