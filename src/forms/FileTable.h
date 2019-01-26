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
using namespace std;
using namespace cpplinq;



namespace ebox
{

    class FileTable : public DataTable
    {
        public:
            FileTable(const string &id, const string &label);

            void listFilesByDirectory(const fs::path &path, const fs::path &parentDirectory);
            pair<const unsigned char *, size_t> getFileIcon(const string &key);

            void sort();
            void sort(const string &columnName, bool sortDesc = false);
            void sortAsInt(const string &columnName, bool sortDesc = false);

            void resetPathOpeningCall();
            void resetRowChangeCall();

            void setFileFilter(const std::string &filter);

            bool canCallPathOpening() const;
            const fs::path &getPathToOpen() const;
            const fs::path &getLastOpenedPath() const;

            const string &getFileFilter() const;

            const string &getSelectedFile() const;

            bool canCallRowChangeEvent() const;


        protected:
            void create();
            void onHeaderColumnClicked(const string &id) override;
            void onRowDoubleClicked(DataRow *row) override;

            void onRowMarked(DataRow *row) override;

            const std::string generatePathId(const DataRow &row) const ;

            void initializeFilemap();
            map<string, pair<const unsigned char *, size_t>> m_fileMap;
            map<std::string, fs::path> m_pathMap;
            pair<std::string, bool> m_previousSortAction = {"filename", false}; //first: columnName, second: orderDesc

            std::string m_selectedFile = "";

            bool m_sortDesc = false;
            bool m_callPathOpening = false;
            bool m_callRowChangeEvent = false;

            std::string m_fileFilter = "*.*"; //Shows all as standard

            fs::path m_lastOpenedPath;
            fs::path m_pathToOpen;
            fs::path m_parentDirectory;
    };
}

#endif //EMU_JUKEBOX_FILETABLE_H
