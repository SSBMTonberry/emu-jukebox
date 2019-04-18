//
// Created by robin on 18.04.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTDATA_H
#define EMU_JUKEBOX_PLAYLISTDATA_H

#include "../audio/EmuFileInfo.h"
#include "../data/JsonFile.h"

namespace ebox
{
    class PlaylistData
    {
        public:
            PlaylistData() = default;
            PlaylistData(const fs::path &path, const std::string &name, int trackNumber, bool loadFile);

            bool loadEmuFile();
            void setPath(const fs::path &path);
            void setName(const std::string &name);
            void setTrackNumber(int trackNumber);

            const fs::path &getPath() const;
            const std::string &getName() const;
            int getTrackNumber() const;
            json getAsJson() const;

            const EmuFileInfo &getEmuFileInfo() const;

        private:
            fs::path m_path;
            EmuFileInfo m_emuFileInfo;
            std::string m_name;
            int m_trackNumber = 0;
    };
}

#endif //EMU_JUKEBOX_PLAYLISTDATA_H
