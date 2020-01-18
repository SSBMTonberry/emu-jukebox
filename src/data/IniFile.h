//
// Created by robin on 25.03.19.
//

#ifndef EMU_JUKEBOX_INIFILE_H
#define EMU_JUKEBOX_INIFILE_H

#include "JsonFile.h"
#include <map>
#include <any>
#include "SFML/Graphics.hpp"
#include "../misc/EmuThemes.hpp"
#include "../managers/FontManager.h"
#include "../misc/Tools.hpp"
#include "../forms/SystemLog.h"

#if APPLE
#include <mach-o/dyld.h>
#endif

#include <climits>

namespace ebox
{
    class IniFile : public JsonFile
    {
        public:
            IniFile();

            void load();
            void write();
            void reset();

            void setPath(const fs::path &path);
            void setLastOpenedFolder(const fs::path &lastOpenedFolder);
            void setLastOpenedFile(const fs::path &lastOpenedFile);
            void setCurrentFont(const std::string &currentFont);
            void setLoopPreviewTracksForever(bool loopPreviewTracksForever);
            void setOpenLastOpenedItemOnStartup(bool openLastOpenedFolderOnStartup);
            void setBackgroundColor(const sf::Color &backgroundColor);
            void setLastItemIsFolder(bool lastItemIsFolder);
            void setLastVolume(float lastVolume);
            void setPlaylistData(const json &playlistData);
            void setCurrentTheme(const std::string &currentTheme);
            void setNumberOfRepeats(int numberOfRepeats);
            void setOpenLastPlaylistOnStartup(bool openLastPlaylistOnStartup);

            const fs::path &getPath() const;
            const fs::path &getLastOpenedFolder() const;
            const fs::path &getLastOpenedFile() const;
            const std::string &getCurrentFont() const;
            bool loopPreviewTracksForever() const;
            bool openLastOpenedItemOnStartup() const;
            const sf::Color &getBackgroundColor() const;
            bool isLastItemFolder() const;
            float getLastVolume() const;
            json getPlaylistData();
            const std::string &getCurrentTheme() const;
            ebox::FontManager *getFontManager();
            int getNumberOfRepeats() const;
            bool openLastPlaylistOnStartup() const;

            void applyTheme();

        protected:
            #if APPLE
            fs::path getMacApplicationFolder();
            #endif

            const std::string FILENAME = "ebox.ini";

            void parseData();

            fs::path m_path =  "./";
            fs::path m_lastOpenedFolder = "";
            fs::path m_lastOpenedFile = "";
            bool m_lastItemIsFolder = true;
            bool m_loopPreviewTracksForever = true;
            bool m_openLastOpenedItemOnStartup = false;
            bool m_openLastPlaylistOnStartup = true;
            sf::Color m_backgroundColor {35, 65, 90, 255};
            std::string m_currentFont = "";
            std::string m_currentTheme = "dark";
            float m_lastVolume = 100.f;
            int m_numberOfRepeats = 0; //0 = infinite, 1 = once(like no repeat), 2 = twice etc...

            ebox::FontManager m_fonts;

    };
}

#endif //EMU_JUKEBOX_INIFILE_H
