#define CATCH_CONFIG_MAIN

#include <fmt/format.h>
#include <fmt/printf.h>
#include "catch.hpp"

int theAnswer() { return 6*9; }

std::string getMillisecondsAsTimeString(int milliseconds)
{
    int hours = (milliseconds / 3600000);
    milliseconds -= (hours * 3600000);
    int minutes = (milliseconds / 60000);
    milliseconds -= (minutes * 60000);
    int seconds = (milliseconds / 1000);
    milliseconds -= (seconds * 1000);

    //return fmt::format("{0:.2d}:{1:.2d}:{2:.2d}.{3:.3d}", hours, minutes, seconds, milliseconds);
    return fmt::sprintf("%2d:.%2d:.%2d..%3d", hours, minutes, seconds, milliseconds);
}

TEST_CASE( "Test-test!", "[42][theAnswer]" ) {
    REQUIRE( theAnswer() == 54 );
}

TEST_CASE( "Test timestring", "[time][string]" ) {
    std::string timeStr = getMillisecondsAsTimeString(150000);
    REQUIRE( timeStr == "00:02:30.000");
}