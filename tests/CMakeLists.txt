cmake_minimum_required(VERSION 3.11)
project(tests_emu-jukebox)

set(TEST_SOURCE_FILES tests_main.cpp)

set (GUI_SOURCE_FILES ../src/gui_/controls/Visualizer.cpp ../src/gui_/controls/Visualizer.h)

set(SOURCE_FILES ../src/managers/ProgramManager.cpp ../src/managers/ProgramManager.h ../src/audio/Voice.cpp ../src/audio/Voice.h
        ../src/managers/FormManager.cpp ../src/managers/FormManager.h ../src/managers/EventManager.cpp ../src/managers/EventManager.h
        ../src/forms/AudioTestForm.cpp ../src/forms/AudioTestForm.h ../src/audio/EmuStream.cpp ../src/audio/EmuStream.h ../src/audio/EmuTrackInfo.cpp
        ../src/audio/EmuTrackInfo.h ../src/audio/AudioCommon.h ../src/managers/ClipboardManager.cpp ../src/managers/ClipboardManager.h ../src/audio/EmuEqualizer.cpp
        ../src/audio/EmuEqualizer.h
        ../src/forms/SystemLog.cpp ../src/forms/SystemLog.h ../src/forms/FilelistForm.cpp ../src/forms/FilelistForm.h ../src/forms/PlaylistForm.cpp
        ../src/forms/PlaylistForm.h ../src/classes/Timer.cpp ../src/classes/Timer.h ../src/forms/AudioPlayerForm.cpp ../src/forms/AudioPlayerForm.h
        ../src/audio/EmuFileInfo.cpp ../src/audio/EmuFileInfo.h ../src/classes/Hotkey.cpp ../src/classes/Hotkey.h ../src/managers/Hotkeys.cpp
        ../src/managers/Hotkeys.h ../src/data/JsonFile.cpp ../src/data/JsonFile.h ../src/data/IniFile.cpp ../src/data/IniFile.h ../src/popups/PreferencesPopup.cpp
        ../src/popups/PreferencesPopup.h ../src/data/PlaylistFile.cpp ../src/data/PlaylistFile.h ../src/classes/PlaylistData.cpp ../src/classes/PlaylistData.h
        ../src/audio/EmuFile.cpp ../src/audio/EmuFile.h ../src/popups/EmuFileExporterPopup.cpp ../src/popups/EmuFileExporterPopup.h
        ../src/misc/EmuThemes.hpp ../src/classes/Font.cpp ../src/classes/Font.h ../src/managers/FontManager.cpp ../src/managers/FontManager.h
        ../src/popups/AboutPopup.cpp)

add_executable(tests_emu-jukebox ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})

if(LINUX)
    target_link_libraries(tests_emu-jukebox pmgui stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        target_link_libraries(tests_emu-jukebox pmgui ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(tests_emu-jukebox pmgui stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    target_link_libraries(tests_emu-jukebox pmgui stdc++ -ObjC ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
endif()