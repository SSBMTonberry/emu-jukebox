#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/printf.h>

#include "../src/forms/FilelistForm.h"
#include "../src/audio/EmuFile.h"

int theAnswer() { return 6*9; }

std::string getMillisecondsAsTimeString(int milliseconds)
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

    if(milliseconds < 100)
        millisecondStr = (milliseconds < 10) ? fmt::format("00{0}", milliseconds) : fmt::format("0{0}", milliseconds);
    else
        millisecondStr = fmt::format("{0}", milliseconds);

    return fmt::format("{0}:{1}:{2}.{3}", hourStr, minuteStr, secondStr, millisecondStr);
    //return fmt::sprintf("%2d:.%2d:.%2d..%3d", hours, minutes, seconds, milliseconds);
}

std::string getId(int number, int digits)
{
    std::string num = fmt::format("{0}", number);
    int remainingDigits = digits - num.length();
    std::string zeroes = "";
    for(int i = 0; i < remainingDigits; ++i)
        zeroes += "0";

    return fmt::format("{0}{1}", zeroes, num);
}

TEST_CASE( "Test-test!", "[42][theAnswer]" ) {
    REQUIRE( theAnswer() == 54 );
}

TEST_CASE( "Test timestring", "[time][string]" ) {
    std::string timeStr = getMillisecondsAsTimeString(150256);
    REQUIRE( timeStr == "00:02:30.256");
}

TEST_CASE( "Test digit string", "[string][digit]" ) {
    int number = 45;
    std::string result = getId(number, 6);
    REQUIRE( result == "000045" );
}

TEST_CASE( "Test file export", "[file_export]" )
{
    //TODO: Add file export code
    std::string path = "../../content/test_files/test.nsf";
    std::string exportPath = "./test.ogg";
    std::string exportPath2 = "./test.FLAC";
    std::string exportPath3 = "./test.wav";
    ebox::EmuFile file;
    bool success = true;

    success = file.initialize(path, 2);
    if(success)
    {
        success = file.createSamplesAndFillBuffer(0);
        if(success)
        {
            file.exportToSoundFile(exportPath);
            file.exportToSoundFile(exportPath2);
            file.exportToSoundFile(exportPath3);
        }
    }


    REQUIRE( success );
}