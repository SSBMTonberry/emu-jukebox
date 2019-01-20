#define CATCH_CONFIG_MAIN

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include "catch.hpp"

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

TEST_CASE( "Test-test!", "[42][theAnswer]" ) {
    REQUIRE( theAnswer() == 54 );
}

TEST_CASE( "Test timestring", "[time][string]" ) {
    std::string timeStr = getMillisecondsAsTimeString(150256);
    REQUIRE( timeStr == "00:02:30.256");
}