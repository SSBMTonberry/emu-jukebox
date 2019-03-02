//
// Created by robin on 11.08.17.
//

#ifndef EBOX_TOOLS_H
#define EBOX_TOOLS_H

#include "../../EmuJukeboxConfig.h"

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <cctype>
#include <initializer_list>

#include <fmt/core.h>
#include <fmt/printf.h>
#include <regex>

#include <SFML/System.hpp>

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

namespace ebox::tools
{
    namespace string
    {
        inline std::string GetMillisecondsAsTimeString(int milliseconds, bool includeMilliseconds);

        namespace helper
        {
            //HELPER FUNCTION FOR SplitString
            template<typename Out>
            static void split(const std::string &s, char delim, Out result)
            {
                std::stringstream ss;
                ss.str(s);
                std::string item;

                while (std::getline(ss, item, delim))
                {
                    *(result++) = item;
                }
            }
        }

        static void StringReplace(std::string *str, const std::string &toReplace, const std::string &replaceWith)
        {
            //*str = std::regex_replace(*str, std::regex("\\" + toReplace), "\\" + replaceWith);
            *str = std::regex_replace(*str, std::regex(toReplace), replaceWith);
        }

        static bool StringContains(const std::string &str, const std::string &text)
        {
            size_t find = str.find(text);
            return (find != std::string::npos) ? true : false;
        }

        static std::vector<std::string> SplitString(const std::string &s, char delim)
        {
            std::vector<std::string> elems;
            helper::split(s, delim, std::back_inserter(elems));
            return elems;
        }

        std::string GetMillisecondsAsTimeString(int milliseconds, bool includeMilliseconds)
        {
            if(milliseconds < 0)
                return (includeMilliseconds) ? "00:00.000" : "00:00";
            else
            {
                int hours = (milliseconds / 3600000);
                std::string hourStr = (hours < 10) ? fmt::format("0{0}", hours) : fmt::format("{0}", hours);
                milliseconds -= (hours * 3600000);
                int minutes = (milliseconds / 60000);
                std::string minuteStr = (minutes < 10) ? fmt::format("0{0}", minutes) : fmt::format("{0}", minutes);
                milliseconds -= (minutes * 60000);
                int seconds = (milliseconds / 1000);
                std::string secondStr = (seconds < 10) ? fmt::format("0{0}", seconds) : fmt::format("{0}", seconds);
                milliseconds -= (seconds * 1000);
                std::string millisecondStr;

                if (milliseconds < 100)
                    millisecondStr = (milliseconds < 10) ? fmt::format("00{0}", milliseconds) : fmt::format("0{0}", milliseconds);
                else
                    millisecondStr = fmt::format("{0}", milliseconds);

                if (hours > 0)
                {
                    return (includeMilliseconds) ? fmt::format("{0}:{1}:{2}.{3}", hourStr, minuteStr, secondStr, millisecondStr) :
                                                   fmt::format("{0}:{1}:{2}", hourStr, minuteStr, secondStr);
                }
                else
                {
                    return (includeMilliseconds) ? fmt::format("{0}:{1}.{2}", minuteStr, secondStr, millisecondStr) :
                                                   fmt::format("{0}:{1}", minuteStr, secondStr);
                }
            }
        }
    }

    namespace filesystem
    {
        static bool IsDirectory(const fs::directory_entry &entry)
        {

            return fs::is_directory(entry);
        }

        static std::string GetPath(const fs::directory_entry &entry)
        {
            return entry.path().string();
        }
    }

    namespace vector
    {
        /*!
         * Checks if the first vector is equal to the second
         * @param first Main vector
         * @param second Second vector
         * @return Are the vectors equal?
         */
        static bool IsEqual(const sf::Vector2f &first, const sf::Vector2f &second)
        {
            return (first.x == second.x && first.y == second.y) ? true : false;
        }

        //Checks
        static bool IsSmallerThan(const sf::Vector2f &first, const sf::Vector2f &second)
        {
            return (first.x == second.x && first.y == second.y) ? true : false;
        }


    }

}

#endif //EBOX_TOOLS_H
