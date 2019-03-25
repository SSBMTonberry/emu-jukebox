//
// Created by robin on 25.03.19.
//

#ifndef EMU_JUKEBOX_INIFILE_H
#define EMU_JUKEBOX_INIFILE_H

#include "JsonFile.h"
#include <map>
#include <any>

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

            const filesystem::path &getPath() const;
            const filesystem::path &getLastOpenedFolder() const;
            const string &getCurrentFont() const;

        protected:
            const string FILENAME = "ebox.ini";

            void parseData();

            filesystem::path m_path = "./";
            filesystem::path m_lastOpenedFolder = "";
            std::string m_currentFont = "";
    };
}

#endif //EMU_JUKEBOX_INIFILE_H
