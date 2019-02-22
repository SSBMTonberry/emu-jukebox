cmake_minimum_required(VERSION 3.13)
project(emu-jukebox)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC -DEBOX_DEBUG")

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
    link_directories(/usr/local/opt/llvm/lib/)
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

configure_file (
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h.in"
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h"
)

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/ ${PROJECT_SOURCE_DIR}/external_libs/include/libgme/)

if(LINUX)
    set(SFML_DEPENDENCIES jpeg X11 Xrandr freetype xcb X11-xcb xcb-randr xcb-image GL FLAC ogg vorbis vorbisenc vorbisfile openal pthread)
    set(SFML_REST udev) #libudev
elseif(WIN32)
    if(MSVC)
        message("USING MSVC")

        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/msvc/sfml)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/msvc/sfml)
        endif()

        set(SFML_DEPENDENCIES opengl32.lib winmm.lib gdi32.lib ${PATH_SFML_DEPEND}/freetype.lib ${PATH_SFML_DEPEND}/openal32.lib ${PATH_SFML_DEPEND}/flac.lib ${PATH_SFML_DEPEND}/vorbisenc.lib ${PATH_SFML_DEPEND}/vorbisfile.lib ${PATH_SFML_DEPEND}/vorbis.lib ${PATH_SFML_DEPEND}/ogg.lib ws2_32.lib )
        #set(SFML_DEPENDENCIES  ${PATH_SFML_DEPEND}/freetype.lib ${PATH_SFML_DEPEND}/openal32.lib ${PATH_SFML_DEPEND}/flac.lib ${PATH_SFML_DEPEND}/vorbisenc.lib ${PATH_SFML_DEPEND}/vorbisfile.lib ${PATH_SFML_DEPEND}/vorbis.lib ${PATH_SFML_DEPEND}/ogg.lib ws2_32.lib )
        #set(SFML_DEPEND_2 opengl32 winmm gdi32 )
    else()
        message("USING MINGW")
        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/mingw/sfml)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/mingw/sfml)
        endif()
        message("PATH: " ${PATH_SFML_DEPEND})
        set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/libfreetype.a ${PATH_SFML_DEPEND}/libFLAC.a ${PATH_SFML_DEPEND}/libogg.a ${PATH_SFML_DEPEND}/libopenal32.a ${PATH_SFML_DEPEND}/libvorbis.a ${PATH_SFML_DEPEND}/libvorbisenc.a ${PATH_SFML_DEPEND}/libvorbisfile.a)
        set(SFML_DEPEND_2 opengl32 winmm gdi32 freetype jpeg)
    endif()
elseif(APPLE)
    message("USING CLANG!")
    set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/frameworks)

    set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/FLAC.framework ${PATH_SFML_DEPEND}/freetype.framework ${PATH_SFML_DEPEND}/ogg.framework ${PATH_SFML_DEPEND}/OpenAL.framework ${PATH_SFML_DEPEND}/vorbis.framework ${PATH_SFML_DEPEND}/vorbisenc.framework ${PATH_SFML_DEPEND}/vorbisfile.framework)
endif()

set(FMT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/source/fmt/format.cc ${PROJECT_SOURCE_DIR}/external_libs/source/fmt/posix.cc)

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

set(IMGUI_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imconfig.h
        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_draw.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_demo.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/misc/cpp/imgui_stdlib.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui-SFML.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui-SFML.cpp)

set(GUI_SOURCE_FILES src/gui/controls/Button.cpp src/gui/controls/Button.h src/gui/controls/Checkbox.cpp src/gui/controls/Checkbox.h
                     src/gui/controls/CheckboxSection.cpp src/gui/controls/CheckboxSection.h src/gui/controls/Child.cpp src/gui/controls/Child.h
                     src/gui/controls/ColorButton.cpp src/gui/controls/ColorButton.h src/gui/controls/ColoredText.cpp src/gui/controls/ColoredText.h
                     src/gui/controls/ColorPicker.cpp src/gui/controls/ColorPicker.h src/gui/controls/Column.cpp src/gui/controls/Column.h
                     src/gui/controls/Combobox.cpp src/gui/controls/Combobox.h src/gui/controls/Control.cpp src/gui/controls/Control.h
                     src/gui/controls/DataColumn.cpp src/gui/controls/DataColumn.h src/gui/controls/DataColumnDefinition.cpp
                     src/gui/controls/DataColumnDefinition.h src/gui/controls/DataRow.cpp src/gui/controls/DataRow.h src/gui/controls/DataTable.cpp
                     src/gui/controls/DataTable.h src/gui/controls/DragFloat.cpp src/gui/controls/DragFloat.h src/gui/controls/DragInt.cpp
                     src/gui/controls/DragInt.h src/gui/controls/Group.cpp src/gui/controls/Group.h src/gui/controls/Image.cpp src/gui/controls/Image.h
                     src/gui/controls/ImageButton.cpp src/gui/controls/ImageButton.h src/gui/controls/InputFloat.cpp src/gui/controls/InputFloat.h
                     src/gui/controls/InputInt.cpp src/gui/controls/InputInt.h src/gui/controls/Label.cpp src/gui/controls/Label.h
                     src/gui/controls/Listbox.cpp src/gui/controls/Listbox.h src/gui/controls/MenuBar.cpp src/gui/controls/MenuBar.h
                     src/gui/controls/MenuItem.cpp src/gui/controls/MenuItem.h src/gui/controls/MenuItemCollection.cpp
                     src/gui/controls/MenuItemCollection.h src/gui/controls/Progressbar.cpp src/gui/controls/Progressbar.h
                     src/gui/controls/RadioSection.cpp src/gui/controls/RadioSection.h src/gui/controls/Row.cpp src/gui/controls/Row.h
                     src/gui/controls/Selectable.cpp src/gui/controls/Selectable.h src/gui/controls/SliderFloat.cpp src/gui/controls/SliderFloat.h
                     src/gui/controls/SliderInt.cpp src/gui/controls/SliderInt.h src/gui/controls/Table.cpp src/gui/controls/Table.h
                     src/gui/controls/Textbox.cpp src/gui/controls/Textbox.h src/gui/controls/TreeList.cpp src/gui/controls/TreeList.h
                     src/gui/controls/TreeNode.cpp src/gui/controls/TreeNode.h src/gui/forms/Form.cpp src/gui/forms/Form.h
                     src/gui/forms/MessagePopup.cpp src/gui/forms/MessagePopup.h src/gui/forms/Popup.cpp src/gui/forms/Popup.h
                     src/gui/forms/TextEditorForm.cpp src/gui/forms/TextEditorForm.h src/gui/properties/RadioData.cpp src/gui/properties/RadioData.h
                     src/gui/properties/Tooltip.cpp src/gui/properties/Tooltip.h src/gui/themes/Theme.cpp src/gui/themes/Theme.h
                     src/gui/TextEditor.cpp src/gui/TextEditor.h)

set(SOURCE_FILES main.cpp src/managers/ProgramManager.cpp src/managers/ProgramManager.h src/audio/Voice.cpp src/audio/Voice.h
                          src/managers/FormManager.cpp src/managers/FormManager.h src/managers/EventManager.cpp src/managers/EventManager.h
                          src/forms/AudioTestForm.cpp src/forms/AudioTestForm.h src/audio/EmuStream.cpp src/audio/EmuStream.h src/audio/EmuTrackInfo.cpp
                          src/audio/EmuTrackInfo.h src/audio/AudioCommon.h src/managers/ClipboardManager.cpp src/managers/ClipboardManager.h src/audio/EmuEqualizer.cpp
                          src/audio/EmuEqualizer.h src/widgets/FileDialog.cpp src/widgets/FileDialog.h src/widgets/FileTable.cpp src/widgets/FileTable.h
                          src/forms/SystemLog.cpp src/forms/SystemLog.h src/forms/FilelistForm.cpp src/forms/FilelistForm.h src/forms/PlaylistForm.cpp
                          src/forms/PlaylistForm.h src/classes/Timer.cpp src/classes/Timer.h src/forms/AudioPlayerForm.cpp src/forms/AudioPlayerForm.h)



if(LINUX)
    if(DEBUG)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/debug)
        set(PATH_SFML_LIB ${PATH_LIBS}/sfml)
        set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
    elseif(RELEASE)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/release)
        set(PATH_SFML_LIB ${PATH_LIBS}/sfml)
        set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    endif()
    #set(MY_STATIC_LIBS ${PATH_LIBS}/libclip.a ${PATH_LIBS}/libfmt.a ${PATH_LIBS}/libgme.a ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    #target_link_libraries(emu-jukebox stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})

    add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES} src/audio/EmuFileInfo.cpp src/audio/EmuFileInfo.h)
    target_link_libraries(emu-jukebox stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win)
        if(DEBUG)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/msvc/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/sfml-network-s-d.lib ${PATH_SFML_LIB}/sfml-audio-s-d.lib ${PATH_SFML_LIB}/sfml-main-d.lib ${PATH_SFML_LIB}/sfml-graphics-s-d.lib ${PATH_SFML_LIB}/sfml-window-s-d.lib ${PATH_SFML_LIB}/sfml-system-s-d.lib)
        elseif(RELEASE)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/msvc/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/sfml-network-s.lib ${PATH_SFML_LIB}/sfml-audio-s.lib ${PATH_SFML_LIB}/sfml-main.lib ${PATH_SFML_LIB}/sfml-graphics-s.lib ${PATH_SFML_LIB}/sfml-window-s.lib ${PATH_SFML_LIB}/sfml-system-s.lib)
        endif()
        add_executable(EmuJukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES})
        target_link_libraries(EmuJukebox ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        #set(MY_STATIC_LIBS ${PATH_LIBS}/libfmt.a ${PATH_SFML_LIB}/libsfml-network.a ${PATH_SFML_LIB}/libsfml-audio.a ${PATH_SFML_LIB}/libsfml-graphics.a ${PATH_SFML_LIB}/libsfml-window.a ${PATH_SFML_LIB}/libsfml-system.a)
        if(DEBUG)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
        elseif(RELEASE)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
        endif()

        add_executable(EmuJukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES})
        target_link_libraries(EmuJukebox stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    set(SFML_BUILD_STATIC 1)
    if(DEBUG)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/debug/sfml)
        if(SFML_BUILD_STATIC)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
        else()
            set(MY_DYNAMIC_LIBS ${PATH_SFML_LIB}/libsfml-network-d.dylib ${PATH_SFML_LIB}/libsfml-audio-d.dylib ${PATH_SFML_LIB}/libsfml-graphics-d.dylib ${PATH_SFML_LIB}/libsfml-window-d.dylib ${PATH_SFML_LIB}/libsfml-system-d.dylib)
        endif()
    elseif(RELEASE)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/release/sfml)
        if(SFML_BUILD_STATIC)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
        else()
            set(MY_DYNAMIC_LIBS ${PATH_SFML_LIB}/libsfml-network.dylib ${PATH_SFML_LIB}/libsfml-audio.dylib ${PATH_SFML_LIB}/libsfml-graphics.dylib ${PATH_SFML_LIB}/libsfml-window.dylib ${PATH_SFML_LIB}/libsfml-system.dylib)
        endif()
    endif()

    set(FRAMEWORK_LIBS_BASE "-framework Carbon" "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation")

    set(MACOSX_BUNDLE_BUNDLE_NAME EmuJukebox)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "robin.jukebox.emu")
    set(MACOSX_BUNDLE_INFO_STRING "A jukebox for them old games")
    set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    #add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES})
    add_executable(EmuJukebox MACOSX_BUNDLE ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES})
    #target_link_libraries(emu-jukebox stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    #stdc++
    if(SFML_BUILD_STATIC)
        target_link_libraries(EmuJukebox stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(EmuJukebox stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
        set_target_properties(EmuJukebox PROPERTIES
                MACOSX_BUNDLE TRUE
                MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
                FRAMEWORK ${MY_DYNAMIC_LIBS})
    endif()
endif()

add_subdirectory(tests)