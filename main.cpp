
#include "EmuJukeboxConfig.h"
#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
//#include "fmt/format.h"
#include "src/managers/ProgramManager.h"

int main(int argc, char **argv, char** envp)
{
    ebox::ProgramManager program(argc, argv, envp);
    program.initialize("Emu Jukebox");//, {mode.width, mode.height});

    ebox::SystemLog::get()->addDebug("DEBUG on!");

    program.run();
    return 0;
}