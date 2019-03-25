//
// Created by robin on 25.03.19.
//

#ifndef EMU_JUKEBOX_JSONFILE_H
#define EMU_JUKEBOX_JSONFILE_H

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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <fmt/format.h>
#include <json.hpp>

using namespace nlohmann;
using namespace std;

namespace ebox
{
    class JsonFile
    {
        public:
            JsonFile() = default;

            void createByFile(const std::string &path);
            void createByMemory(const void * data, size_t size);
            void createDummyData();

            void add(const json &j);
            virtual void clear();

            bool hasKey(const std::string &key);
            size_t getKeyCount(const std::string &key);
            bool isArray(const std::string &key);

            void writeToFile(const std::string &path);

        protected:
            json m_data;
    };
}

#endif //EMU_JUKEBOX_JSONFILE_H
