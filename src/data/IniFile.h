//
// Created by robin on 25.03.19.
//

#ifndef EMU_JUKEBOX_INIFILE_H
#define EMU_JUKEBOX_INIFILE_H

#include "JsonFile.h"
#include <map>
#include <any>
#include "SFML/Graphics.hpp"

namespace ebox
{
    class IniFile : public JsonFile
    {
        public:
            IniFile();

            void load();

            void write();

            void setPath(const filesystem::path &path);
            void setLastOpenedFolder(const filesystem::path &lastOpenedFolder);
            void setCurrentFont(const string &currentFont);
            void setLoopPreviewTracksForever(bool loopPreviewTracksForever);
            void setOpenLastOpenedFolderOnStartup(bool openLastOpenedFolderOnStartup);
            void setBackgroundColor(const sf::Color &backgroundColor);

            const filesystem::path &getPath() const;
            const filesystem::path &getLastOpenedFolder() const;
            const string &getCurrentFont() const;
            bool loopPreviewTracksForever() const;
            bool openLastOpenedFolderOnStartup() const;
            const sf::Color &getBackgroundColor() const;

        protected:
            const string FILENAME = "ebox.ini";

            void parseData();

            filesystem::path m_path = "./";
            filesystem::path m_lastOpenedFolder = "";
            bool m_loopPreviewTracksForever = true;
            bool m_openLastOpenedFolderOnStartup = false;
            sf::Color m_backgroundColor {35, 65, 90, 255};
            std::string m_currentFont = "";
    };
}

#endif //EMU_JUKEBOX_INIFILE_H
