# Emu-Jukebox ![alt text](https://github.com/SSBMTonberry/emu-jukebox/blob/master/logo/logo_64x64.png?raw=true "Emu Jukebox logo") 

#### THIS IS A WORK IN PROGRESS! A LOT OF FUNCTIONALITY IS WORKING "OK" AS IS, BUT EXPECT BUGS AND/OR PARTIAL FUNCTIONALITY! IF YOU FIND ANY BUGS THAT ARE NOT LISTED UNDER ISSUES, PLEASE REPORT THEM, SO THEY CAN BE SOLVED :)

Emu-Jukebox is a *cross-platform* music player that is intended to emulate the sound of old gaming consoles, using files that are read by a sound engine and converted into actual sound waves that you can play on your PC. The purpose of this project is to make a player that is able to play these retro file formats on a computer as if they were regular music files. 

The file formats that are supported:
- AY        - ZX Spectrum/Amstrad CPC
- GBS       - Nintendo Game Boy
- GYM       - Sega Genesis/Mega Drive
- HES       - NEC TurboGrafx-16/PC Engine
- KSS       - MSX Home Computer/other Z80 systems (doesn't support FM sound)
- NSF/NSFE  - Nintendo NES/Famicom (with VRC 6, Namco 106, and FME-7 sound)
- SAP       - Atari systems using POKEY sound chip
- SPC       - Super Nintendo/Super Famicom
- VGM       - Sega Master System/Mark III, Sega Genesis/Mega Drive,BBC Micro

## Cross-platform
Emu-Jukebox is designed to be cross-platform. That means that whether you use Windows, Linux or Mac (OS X), you should be able to use this program! This project utilizes CMake to make it possible to easily compile the program on different systems without any problem!

## Features that are implemented or partially implemented (as of version 0.6):
- The possibility to load either single files or entire folders of files.
- The possibility to play all formats either from a file explorer or an own playlist.
- The possibility to control the tempo of the files you play.
- The possibility to mute voices/channels in a emulated file.
- The possibility to do simple equalization on files.
- The possibility to shuffle and repeat songs that have been put on the playlist
- Audio visualizer by [Alexander Brevig](https://github.com/AlexanderBrevig/) ([#28](https://github.com/SSBMTonberry/emu-jukebox/issues/28))
- Note: Files loaded from the file explorer ("Files") will run indefinitely. This is intentional, as it's only meant for previewing of songs, and some songs do loop indefinitely. When you however to play songs from a playlist, the next song will automatically be calle after end of track. 

## Known critical issues (as of version 0.6):
- If you build the `Debug`-version, a crash will happen if you skip time/fast forward on SNES/.spc-file. This is however not a problem when built in `Release`, so building in `Release` is highly recommended for maximum stability.
- ~~"Reset layout" will crash the program. This will be fixed in version 0.7 for sure~~ ([#2](https://github.com/SSBMTonberry/emu-jukebox/issues/2)).
- In a few cases, when you call a lot of "next song" commands, you will end up with a crash ([#24](https://github.com/SSBMTonberry/emu-jukebox/issues/24)).
- ~~If you remove a lot of random elements from a big playlist, the program might crash~~ ([#7](https://github.com/SSBMTonberry/emu-jukebox/issues/7))

## Screenshot:
![alt text](https://raw.githubusercontent.com/SSBMTonberry/emu-jukebox/master/logo/emu-jukebox_screen.png?token=AY_g1U1rkkxq0Ol-rTrvSQXLo_rKv8Jzks5cjBMZwA%3D%3D "Emu Jukebox Screenshot") 

## Compiling
Since Emu-Jukebox is using CMake, it should be pretty straightforward to compile, as long as CMake is installed. Since Emu-Jukebox is using C++17 functionality, like `std::filesystem`, a compiler that is supporting this is required. By design Emu-Jukebox is copiled with static libraries, and is compiling all its resources statically, the program should (at least in version 1.0) be able to work as one single executable! Emu-Jukebox is using [f2src](https://github.com/SSBMTonberry/f2src) to generate header files with its file data. The required external dependencies are included in this project, and should make the compilation pretty traight forward. 

### Windows
*NB! Currently only got support for builing with Win32/x86 settings.*

Load the CMakeLists.txt into `CMake`, then generate a `Visual Studio 2017 project`. Then you should be all good. There are also libs for `MinGW`, but these are not compiling as of now. The application is almost fully statically linked, except for `openal32.dll` (OpenAL-Soft), which sadly is a standalone dependency due to its license. This can however be solved by either including the openal.dll in the same folder, or just put it inside `System32`-folder and make it a part of your system wide libraries. There are plans to make this a statically part of the application in the future, as it doesn't violate the license due to being a totally open-sourced application for anyone to build or modify, but it will require some extra work. 

### Linux
Emu-Jukebox has primarily been developed on Linux (Manjaro / Arch Linux), with `GCC 8.1.1`. Thus it's recommended using `GCC 8.X something` for compilation. Nevertheless, you will need a compiler that supports the features of `std::filesystem`.

### Mac (OS X)
Requires the `llvm`/`clang` version shipped with (XCode 10) (OS X Mojave), or a newer version obtained by `homebrew`. You will need to either put the third party libraries provided in this project in a common `Library` folder, or in the same folder as the .app file is built, to make the program run without problems. 

## Libraries used by Emu-Jukebox
- [Game_Music_Emu](http://blargg.8bitalley.com/libs/audio.html#Game_Music_Emu) - Used for emulating the sound chip of each retro console.
- [SFML](https://github.com/SFML/SFML) - For sound streaming, window, clipboard and displaying graphics.
- [Dear ImGui](https://github.com/ocornut/imgui) - For anything GUI related.
