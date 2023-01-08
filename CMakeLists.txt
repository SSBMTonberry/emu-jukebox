cmake_minimum_required(VERSION 3.11)
project(emu-jukebox)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 9)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_IS_ALPHA 1)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC -DEBOX_DEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG 1)
    message(DEBUGGIN')
else()
    set(RELEASE 1)
endif()

if(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
elseif(APPLE)
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 1)
    set(MSVC 0)
    set(MINGW 0)
elseif(WIN32)
    set(LINUX 0)
    set(WINDOWS 1)
    set(APPLE 0)
    if(MSVC)
        set(MSVC 1)
        set(MINGW 0)
    elseif(MINGW)
        set(MINGW 1)
        set(MSVC 0)
    endif()
else()
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
endif()

add_subdirectory(external_libs/submodules/pmgui)

configure_file (
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h.in"
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h"
)

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/ ${PROJECT_SOURCE_DIR}/external_libs/include/libgme/ ${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/src)

set(GME_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Blip_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Classic_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Data_Reader.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Dual_Resampler.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Effects_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Fir_Resampler.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gbs_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/gme.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gme_File.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gym_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Scc_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/M3u_Playlist.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Multi_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Music_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Fme7_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Namco_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Vrc6_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsf_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsfe_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sms_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Snes_Spc.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Dsp.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Filter.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu_Impl.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2413_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_GENS.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_MAME.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_Nuked.cpp)




set(GUI_SOURCE_FILES src/gui_/controls/Visualizer.cpp src/gui_/controls/Visualizer.h)

set(SOURCE_FILES src/managers/ProgramManager.cpp src/managers/ProgramManager.h src/audio/Voice.cpp src/audio/Voice.h
                  src/managers/FormManager.cpp src/managers/FormManager.h
                  src/forms/AudioTestForm.cpp src/forms/AudioTestForm.h src/audio/EmuStream.cpp src/audio/EmuStream.h src/audio/EmuTrackInfo.cpp
                  src/audio/EmuTrackInfo.h src/audio/AudioCommon.h src/managers/ClipboardManager.cpp src/managers/ClipboardManager.h src/audio/EmuEqualizer.cpp
                  src/audio/EmuEqualizer.h src/forms/SystemLog.cpp src/forms/SystemLog.h src/forms/FilelistForm.cpp src/forms/FilelistForm.h src/forms/PlaylistForm.cpp
                  src/forms/PlaylistForm.h src/classes/Timer.cpp src/classes/Timer.h src/forms/AudioPlayerForm.cpp src/forms/AudioPlayerForm.h
                  src/audio/EmuFileInfo.cpp src/audio/EmuFileInfo.h src/classes/Hotkey.cpp src/classes/Hotkey.h src/managers/Hotkeys.cpp
                  src/managers/Hotkeys.h src/data/JsonFile.cpp src/data/JsonFile.h src/data/IniFile.cpp src/data/IniFile.h src/popups/PreferencesPopup.cpp
                  src/popups/PreferencesPopup.h src/data/PlaylistFile.cpp src/data/PlaylistFile.h src/classes/PlaylistData.cpp src/classes/PlaylistData.h
                  src/audio/EmuFile.cpp src/audio/EmuFile.h src/popups/EmuFileExporterPopup.cpp src/popups/EmuFileExporterPopup.h
                  src/misc/EmuThemes.hpp src/classes/Font.cpp src/classes/Font.h src/managers/FontManager.cpp src/managers/FontManager.h
                  src/popups/AboutPopup.cpp src/popups/AboutPopup.h src/misc/Math.hpp)

if(LINUX)
    set(MY_STATIC_LIBS sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
    add_executable(emu-jukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})
    target_link_libraries(emu-jukebox pmgui stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        set(MY_STATIC_LIBS sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
        add_executable(EmuJukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/logo/icon.rc)
        target_link_libraries(EmuJukebox pmgui ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        set(MY_STATIC_LIBS sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
        add_executable(EmuJukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/logo/icon.rc)
        target_link_libraries(EmuJukebox pmgui stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    set(SFML_BUILD_STATIC 1)

    set(MY_STATIC_LIBS sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
    set(FRAMEWORK_LIBS_BASE "-framework Carbon" "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation")

    set(MACOSX_BUNDLE_BUNDLE_NAME EmuJukebox)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "robin.jukebox.emu")
    set(MACOSX_BUNDLE_INFO_STRING "A jukebox for them old games")
    set(MACOSX_BUNDLE_ICON_FILE "AppIcon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

    set_source_files_properties(${PROJECT_SOURCE_DIR}/logo/AppIcon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(EmuJukebox MACOSX_BUNDLE main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})

    #stdc++
#    if(SFML_BUILD_STATIC)
#        target_link_libraries(EmuJukebox pmgui stdc++ -ObjC ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
#    else()
#        target_link_libraries(EmuJukebox pmgui stdc++ -ObjC ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
#        set_target_properties(EmuJukebox PROPERTIES
#                MACOSX_BUNDLE TRUE
#                MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
#                FRAMEWORK ${MY_DYNAMIC_LIBS})
#
#    endif()
    target_link_libraries(EmuJukebox pmgui stdc++ -ObjC ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
    set_target_properties(EmuJukebox PROPERTIES
            MACOSX_BUNDLE TRUE)
    file(COPY ${CMAKE_SOURCE_DIR}/logo/AppIcon.icns DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/EmuJukebox.app/Contents/Resources)
    file(COPY ${CMAKE_SOURCE_DIR}/external_libs/osx-frameworks/Frameworks DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/EmuJukebox.app/Contents)

endif()

add_subdirectory(tests)