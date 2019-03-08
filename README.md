# emu-jukebox ![alt text](https://github.com/SSBMTonberry/emu-jukebox/blob/master/logo/logo_64x64.png?raw=true "Emu Jukebox logo") 

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
- Note: Files loaded from the file explorer ("Files") will run indefinitely. This is intentional, as it's only meant for previewing of songs, and some songs do loop indefinitely. When you however to play songs from a playlist, the next song will automatically be calle after end of track. 

## Known critical issues (as of version 0.6):
- "Reset layout" will crash the program. This will be fixed in version 0.7 for sure ([#2](https://github.com/SSBMTonberry/emu-jukebox/issues/2)).
- In a few cases, when you call a lot of "next song" commands, you will end up with a crash ([#24](https://github.com/SSBMTonberry/emu-jukebox/issues/24)).
- If you remove a lot of random elements from a big playlist, the program might crash ([#7](https://github.com/SSBMTonberry/emu-jukebox/issues/7))

## Screenshot:
![alt text](https://raw.githubusercontent.com/SSBMTonberry/emu-jukebox/master/logo/emu-jukebox_screen.png?token=AY_g1U1rkkxq0Ol-rTrvSQXLo_rKv8Jzks5cjBMZwA%3D%3D "Emu Jukebox Screenshot") 

## Libraries used by Emu-Jukebox
- [Game_Music_Emu](http://blargg.8bitalley.com/libs/audio.html#Game_Music_Emu) - Used for emulating the sound chip of each retro console.
- [SFML](https://github.com/SFML/SFML) - For sound streaming, window, clipboard and displaying graphics.
- [Dear ImGui](https://github.com/ocornut/imgui) - For anything GUI related.
