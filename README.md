# Emu-Jukebox ![alt text](https://github.com/SSBMTonberry/emu-jukebox/blob/master/logo/logo_64x64.png?raw=true "Emu Jukebox logo") 

#### THIS IS A WORK IN PROGRESS! IF YOU FIND ANY BUGS THAT ARE NOT LISTED UNDER ISSUES, PLEASE REPORT THEM, SO THEY CAN BE SOLVED :)

Emu-Jukebox is a *cross-platform* music player that emulates the sound of old gaming consoles, using files that are read by a sound engine and converted into actual sound waves that you can play on your PC. The purpose of this project is to make a player that is able to play these retro file formats on a computer as if they were regular music files. 

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

## What's new in v0.9.0 alpha?
- Infinite play toggle button ([#79](https://github.com/SSBMTonberry/emu-jukebox/issues/79))
- A custom length can now be defined for songs with undefined lengths ([#59](https://github.com/SSBMTonberry/emu-jukebox/issues/59))
- Filename of current track is now displayed in track info ([#82](https://github.com/SSBMTonberry/emu-jukebox/issues/82))
- Playlists now stores relative paths ([#57](https://github.com/SSBMTonberry/emu-jukebox/issues/57))
- There is now a button to transfer all tracks from file explorer to playlist ([#74](https://github.com/SSBMTonberry/emu-jukebox/issues/74))
- Better handling of multiple monitors ([#81](https://github.com/SSBMTonberry/emu-jukebox/issues/81))
- Greatly improved CMake script, which should introduce proper support for 64-bit windows builds. ([#78](https://github.com/SSBMTonberry/emu-jukebox/issues/78))
- Likely fixed a strange bug where the application would appear as frozen on startup, and you would have to re-focus it to make it respond ([#80](https://github.com/SSBMTonberry/emu-jukebox/issues/80), [#58](https://github.com/SSBMTonberry/emu-jukebox/issues/58)) 

## Other features
- The possibility to load either single files or entire folders of files.
- The possibility to play all formats either from a file explorer or an own playlist.
- The possibility to control the tempo of the files you play.
- The possibility to mute voices/channels in a emulated file.
- The possibility to do simple equalization on files.
- The possibility to shuffle and repeat songs that have been put on the playlist
- Audio visualizer by [Alexander Brevig](https://github.com/AlexanderBrevig/) ([#28](https://github.com/SSBMTonberry/emu-jukebox/issues/28))
- Hotkey support for common actions (see tooltips on buttons and controls).
- Filter search on files (by [Alexander Brevig](https://github.com/AlexanderBrevig/))
- You can clear filelists and playlists. 
- You can move playlist items up and down.
- Playlists can be saved to and loaded from files.
- You can control program settings via **Preferences**, including fonts and themes. This is stored into an .ini file that is checked when loading the application.
- Multi-selection of Playlist items using the Ctrl key + mouse click.
- You can choose number of times you want a Playlist song to be repeated in **Preferences**. This is only considered if a song is loaded from a Playlist and **Repeat** is active.
- Emu file data can now be exported to music files. Supported file types to export to are .ogg, .FLAC and .wav. Note that you need to open a file in the Player to be able to export it.
- You can optionally make the program load data from the previously opened folder, or store the current Playlist when shutting down. Check **Preferences**. Playlist items are stored by default.
- You can control the internal volume of the application.
- File Dialog now supports file dates for all platforms, but the Windows implementation is a bit slow. Which you will notice if you load a folder with an insane number of files. Like 30000+. 
- Paths with special letters should now load properly on all platforms.

- Note: Files loaded from the file explorer ("Files") will run indefinitely. This is intentional, as it's only meant for previewing of songs, and some songs do loop indefinitely. When you however to play songs from a playlist, the next song will automatically be called after end of track. This can as of version 0.8 be turned off via "Preferences". 

## Known issues (as of version 0.8.1):
- There is a problem occuring a few times when you start the application, where it appears "frozen". To fix this issue, you simply just have to unfocus then re-focus the application to be able to use the gui-controls. I've tried a couple of things to fix this, but with no luck. Issue: [#58](https://github.com/SSBMTonberry/emu-jukebox/issues/58) 


## Screenshot (default look):
![alt text](https://github.com/SSBMTonberry/emu-jukebox/blob/master/logo/emu-jukebox_0.8.0_1.png "Emu Jukebox Screenshot") 
## Screenshot (custom theme and custom large font):
![alt text](https://github.com/SSBMTonberry/emu-jukebox/blob/master/logo/emu-jukebox_0.8.0_2.png "Emu Jukebox Screenshot") 

## Compiling
Since Emu-Jukebox is using CMake, it should be pretty straightforward to compile, as long as CMake is installed. Since Emu-Jukebox is using C++17 functionality, like `std::filesystem`, a compiler that is supporting this is required. By design Emu-Jukebox is copiled with static libraries, and is compiling all its resources statically, the program should (at least in version 1.0) be able to work as one single executable! Emu-Jukebox is using [f2src](https://github.com/SSBMTonberry/f2src) to generate header files with its file data. The required external dependencies are included in this project, and should make the compilation pretty traight forward. 

### Windows
Load the CMakeLists.txt into `CMake`, then generate a `Visual Studio 20xx project`. Then you should be all good. The application is almost fully statically linked, except for `openal32.dll` (OpenAL-Soft), which sadly is a standalone dependency due to its license. This can however be solved by either including the openal.dll in the same folder, or just put it inside `System32`-folder and make it a part of your system wide libraries. There are plans to make this a statically part of the application in the future, as it doesn't violate the license due to being a totally open-sourced application for anyone to build or modify, but it will require some extra work. 

### Linux
Emu-Jukebox has primarily been developed on Linux (Manjaro / Arch Linux), with `GCC` using the `C++17` standard. You will especially need a compiler that supports the features of `std::filesystem`. You can easily compile the program by console by going into the directory of the project, where the `CMakeLists.txt`file is located and call these commands:
- `cmake ./`
- `make`

### Mac (OS X)
Requires the `llvm`/`clang` version obtained by `homebrew` (worked for some years now). If you have MacOS 10.15 (Catalina) with XCode 11, you should also be able to compile this program (untested). You will need to either put the third party libraries provided in this project in a common `Library` folder, or in the same folder as the .app file is built, to make the program run without problems. You can, alternatively, just use the .app file attached to a release (includes all dependencies).

## Libraries used by Emu-Jukebox
- [Game_Music_Emu](http://blargg.8bitalley.com/libs/audio.html#Game_Music_Emu) - Used for emulating the sound chip of each retro console.
- [SFML](https://github.com/SFML/SFML) - For sound streaming, window, clipboard and displaying graphics.
- [Dear ImGui](https://github.com/ocornut/imgui) - For anything GUI related.
- [Catch2](https://github.com/catchorg/Catch2/) - For testing.
- [json](https://github.com/nlohmann/json) - For JSON read/write.
- [fmt](https://github.com/fmtlib/fmt) - For formatting.
- [imgui-sfml](https://github.com/eliasdaler/imgui-sfml) - To use ImGui with SFML.
