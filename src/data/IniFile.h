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
            void setLastOpenedFile(const filesystem::path &lastOpenedFile);
            void setCurrentFont(const string &currentFont);
            void setLoopPreviewTracksForever(bool loopPreviewTracksForever);
            void setOpenLastOpenedItemOnStartup(bool openLastOpenedFolderOnStartup);
            void setBackgroundColor(const sf::Color &backgroundColor);
            void setLastItemIsFolder(bool lastItemIsFolder);
            void setLastVolume(float lastVolume);

            const filesystem::path &getPath() const;
            const filesystem::path &getLastOpenedFolder() const;
            const filesystem::path &getLastOpenedFile() const;
            const string &getCurrentFont() const;
            bool loopPreviewTracksForever() const;
            bool openLastOpenedItemOnStartup() const;
            const sf::Color &getBackgroundColor() const;
            bool isLastItemFolder() const;
            float getLastVolume() const;

        protected:
            const string FILENAME = "ebox.ini";

            void parseData();

            filesystem::path m_path = "./";
            filesystem::path m_lastOpenedFolder = "";
            filesystem::path m_lastOpenedFile = "";
            bool m_lastItemIsFolder = true;
            bool m_loopPreviewTracksForever = true;
            bool m_openLastOpenedItemOnStartup = false;
            sf::Color m_backgroundColor {35, 65, 90, 255};
            std::string m_currentFont = "";
            float m_lastVolume = 100.f;

    };
}

#endif //EMU_JUKEBOX_INIFILE_H
