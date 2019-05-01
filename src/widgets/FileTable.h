//
// Created by robin on 20.01.19.
//

#ifndef EMU_JUKEBOX_FILETABLE_H
#define EMU_JUKEBOX_FILETABLE_H

#include "../../EmuJukeboxConfig.h"
#include "../gui/controls/DataTable.h"
#include "../../content/files_mapper.h"

#include <map>
#include <cpplinq.hpp>
#include <fmt/time.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>

//namespace fs = std::experimental::filesystem;
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

namespace fm = files_mapper;
using namespace cpplinq;

#if MSVC
#include <Windows.h>
#endif


namespace ebox
{

    class FileTable : public DataTable
    {
        public:
            FileTable(const std::string &id, const std::string &label, bool useFileIcons = true);

            void listFilesByDirectory(const fs::path &path, const fs::path &parentDirectory);
            std::pair<const unsigned char *, size_t> getFileIcon(const std::string &key);
            ebox::Image *getImgFileIcon(const std::string &key);

            void sort();
            void sort(const std::string &columnName, bool sortDesc = false);
            void sortAsInt(const std::string &columnName, bool sortDesc = false);

            void resetPathOpeningCall();
            void resetRowChangeCall();

            void setFileFilter(const std::string &filter);
            void setUseFileIcons(bool useFileIcons);
            void setScaleFactor(float scaleFactor);

            bool canCallPathOpening() const;
            const fs::path &getPathToOpen() const;
            const fs::path &getLastOpenedPath() const;
            const std::string &getFileFilter() const;
            const std::string &getSelectedFile() const;
            bool useFileIcons() const;
            bool canCallRowChangeEvent() const;
            float getScaleFactor() const;

        protected:
            void create();
            void onHeaderColumnClicked(const std::string &id) override;
            void onRowDoubleClicked(DataRow *row) override;

#if MSVC
            std::string getWindowsTimeStampString(const fs::path &path);
#elif APPLE
            std::string getOsxTimeStampString(const fs::path &path);
#endif
            void onRowMarked(DataRow *row) override;

            const std::string generatePathId(const DataRow &row) const ;

            void initializeFilemap();
            void initializeImgFilemap();
            std::map<std::string, std::pair<const unsigned char *, size_t>> m_fileMap;
            std::map<std::string, ebox::Image> m_imgFileMap;
            std::map<std::string, fs::path> m_pathMap;
            std::pair<std::string, bool> m_previousSortAction = {"filename", false}; //first: columnName, second: orderDesc

            std::string m_selectedFile = "";

            bool m_sortDesc = false;
            bool m_callPathOpening = false;
            bool m_callRowChangeEvent = false;

            bool m_useFileIcons = true;
            std::string m_fileFilter = "*.*"; //Shows all as standard
            float m_scaleFactor = 1.f;

            fs::path m_lastOpenedPath;
            fs::path m_pathToOpen;
            fs::path m_parentDirectory;
    };
}

#endif //EMU_JUKEBOX_FILETABLE_H
