//
// Created by robin on 18.04.19.
//

#ifndef EMU_JUKEBOX_PLAYLISTFILE_H
#define EMU_JUKEBOX_PLAYLISTFILE_H

#include "JsonFile.h"
#include "../classes/PlaylistData.h"
#include <vector>

namespace ebox
{
    class PlaylistFile : public JsonFile
    {
        public:
            PlaylistFile(const fs::path &path);

            void load();
            void write();
            void clearPlaylist();

            void add(const fs::path &path, const std::string &name, int trackNumber);

        protected:
            void parseData();

            fs::path m_path;
            std::string m_name;
            std::vector<PlaylistData> m_playlistData;
    };
}

#endif //EMU_JUKEBOX_PLAYLISTFILE_H
