cmake_minimum_required(VERSION 3.11)
project(emu-jukebox)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 8)
set(PROJECT_VERSION_PATCH 1)
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

if(DEBUG)
    message("Adding debug submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/cmake-build-debug)
else()
    message("Adding release submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/cmake-build-release)
endif()

configure_file (
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h.in"
        "${PROJECT_SOURCE_DIR}/EmuJukeboxConfig.h"
)

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/ ${PROJECT_SOURCE_DIR}/external_libs/include/libgme/ ${PROJECT_SOURCE_DIR}/external_libs/submodules/pmgui/src)

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

# Controlled by PMGUI
#set(FMT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/source/fmt/format.cc ${PROJECT_SOURCE_DIR}/external_libs/source/fmt/posix.cc)

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


#set(GME_PATH ${PROJECT_SOURCE_DIR}/external_libs/source/gme2)
#set(GME_SOURCE_FILES
#${GME_PATH}/higan/dsp/dsp.hpp
#${GME_PATH}/higan/dsp/dsp.cpp
#${GME_PATH}/higan/dsp/SPC_DSP.cpp
##${GME_PATH}/higan/processor/spc700/memory.hpp
##${GME_PATH}/higan/processor/spc700/registers.hpp
#${GME_PATH}/higan/processor/spc700/spc700.hpp
##${GME_PATH}/higan/processor/spc700/algorithms.cpp
##${GME_PATH}/higan/processor/spc700/disassembler.cpp
##${GME_PATH}/higan/processor/spc700/instructions.cpp
#${GME_PATH}/higan/processor/spc700/spc700.cpp
#
#${GME_PATH}/higan/smp/memory.cpp
#${GME_PATH}/higan/smp/smp.hpp
#${GME_PATH}/higan/smp/smp.cpp
#${GME_PATH}/higan/smp/timing.cpp
#${GME_PATH}/Ay_Apu.cpp
#${GME_PATH}/Ay_Core.cpp
#${GME_PATH}/Ay_Cpu.cpp
#${GME_PATH}/Ay_Emu.cpp
#${GME_PATH}/blargg_common.cpp
#${GME_PATH}/blargg_errors.cpp
#${GME_PATH}/Blip_Buffer.cpp
#${GME_PATH}/Bml_Parser.cpp
#${GME_PATH}/c140.c
#${GME_PATH}/C140_Emu.cpp
#${GME_PATH}/Classic_Emu.cpp
#${GME_PATH}/dac_control.c
#${GME_PATH}/dbopl.cpp
#${GME_PATH}/Downsampler.cpp
#${GME_PATH}/Data_Reader.cpp
#${GME_PATH}/Dual_Resampler.cpp
#${GME_PATH}/Effects_Buffer.cpp
#${GME_PATH}/Fir_Resampler.cpp
#${GME_PATH}/fm2612.c
#${GME_PATH}/fm.c
#${GME_PATH}/fmopl.cpp
#${GME_PATH}/Gb_Apu.cpp
#${GME_PATH}/Gb_Cpu.cpp
#${GME_PATH}/Gb_Oscs.cpp
#${GME_PATH}/Gbs_Core.cpp
#${GME_PATH}/Gbs_Cpu.cpp
#${GME_PATH}/Gbs_Emu.cpp
#${GME_PATH}/gme.cpp
#${GME_PATH}/gme_custom_dprintf.c
#${GME_PATH}/Gme_File.cpp
#${GME_PATH}/Gme_Loader.cpp
#${GME_PATH}/Gym_Emu.cpp
#${GME_PATH}/Hes_Apu_Adpcm.cpp
#${GME_PATH}/Hes_Apu.cpp
#${GME_PATH}/Hes_Core.cpp
#${GME_PATH}/Hes_Cpu.cpp
#${GME_PATH}/Hes_Emu.cpp
#${GME_PATH}/k051649.c
#${GME_PATH}/K051649_Emu.cpp
#${GME_PATH}/k053260.c
#${GME_PATH}/K053260_Emu.cpp
#${GME_PATH}/k054539.c
#${GME_PATH}/K054539_Emu.cpp
#${GME_PATH}/Kss_Core.cpp
#${GME_PATH}/Kss_Cpu.cpp
#${GME_PATH}/Kss_Emu.cpp
#${GME_PATH}/Kss_Scc_Apu.cpp
#${GME_PATH}/M3u_Playlist.cpp
#${GME_PATH}/Multi_Buffer.cpp
#${GME_PATH}/Music_Emu.cpp
#${GME_PATH}/Nes_Apu.cpp
#${GME_PATH}/Nes_Cpu.cpp
#${GME_PATH}/Nes_Fds_Apu.cpp
#${GME_PATH}/Nes_Fme7_Apu.cpp
#${GME_PATH}/Nes_Namco_Apu.cpp
#${GME_PATH}/Nes_Oscs.cpp
#${GME_PATH}/Nes_Vrc6_Apu.cpp
#${GME_PATH}/Nes_Vrc7_Apu.cpp
#${GME_PATH}/Nsf_Core.cpp
#${GME_PATH}/Nsf_Cpu.cpp
#${GME_PATH}/Nsfe_Emu.cpp
#${GME_PATH}/Nsf_Emu.cpp
#${GME_PATH}/Nsf_Impl.cpp
#${GME_PATH}/okim6258.c
#${GME_PATH}/Okim6258_Emu.cpp
#${GME_PATH}/okim6295.c
#${GME_PATH}/Okim6295_Emu.cpp
#${GME_PATH}/Opl_Apu.cpp
#${GME_PATH}/pwm.c
#${GME_PATH}/Pwm_Emu.cpp
#${GME_PATH}/qmix.c
#${GME_PATH}/Qsound_Apu.cpp
#${GME_PATH}/Resampler.cpp
#${GME_PATH}/Rf5C164_Emu.cpp
#${GME_PATH}/rf5c68.c
#${GME_PATH}/Rf5C68_Emu.cpp
#${GME_PATH}/Rom_Data.cpp
#${GME_PATH}/Sap_Apu.cpp
#${GME_PATH}/Sap_Core.cpp
#${GME_PATH}/Sap_Cpu.cpp
#${GME_PATH}/Sap_Emu.cpp
#${GME_PATH}/scd_pcm.c
#${GME_PATH}/s_deltat.c
#${GME_PATH}/segapcm.c
#${GME_PATH}/SegaPcm_Emu.cpp
#${GME_PATH}/Sgc_Core.cpp
#${GME_PATH}/Sgc_Cpu.cpp
#${GME_PATH}/Sgc_Emu.cpp
#${GME_PATH}/Sgc_Impl.cpp
#${GME_PATH}/s_logtbl.c
#${GME_PATH}/Sms_Apu.cpp
#${GME_PATH}/Sms_Fm_Apu.cpp
#${GME_PATH}/s_opl.c
#${GME_PATH}/s_opltbl.c
#
#${GME_PATH}/Spc_Emu.cpp
#${GME_PATH}/Spc_Filter.cpp
#${GME_PATH}/Spc_Sfm.cpp
#
##${GME_PATH}/Snes_Spc.cpp
##${GME_PATH}/Spc_Emu.cpp
##${GME_PATH}/Spc_Filter.cpp
##${GME_PATH}/Spc_Dsp.cpp
##${GME_PATH}/Spc_Cpu.cpp
#
#${GME_PATH}/Track_Filter.cpp
#${GME_PATH}/Upsampler.cpp
#${GME_PATH}/Vgm_Core.cpp
#${GME_PATH}/Vgm_Emu.cpp
#${GME_PATH}/ym2151.c
#${GME_PATH}/Ym2151_Emu.cpp
#${GME_PATH}/Ym2203_Emu.cpp
#${GME_PATH}/ym2413.c
#${GME_PATH}/Ym2413_Emu.cpp
#${GME_PATH}/Ym2608_Emu.cpp
#${GME_PATH}/Ym2610b_Emu.cpp
##${GME_PATH}/Ym2612_Emu.cpp
##${GME_PATH}/Ym2612_Emu_Gens.cpp
#${GME_PATH}/Ym2612_Emu_MAME.cpp
#${GME_PATH}/Ym3812_Emu.cpp
#${GME_PATH}/ymdeltat.cpp
#${GME_PATH}/Ymf262_Emu.cpp
#${GME_PATH}/ymz280b.c
#${GME_PATH}/Ymz280b_Emu.cpp
#${GME_PATH}/Z80_Cpu.cpp
#)

# Controlled by PMGUI now
#set(IMGUI_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imconfig.h
#        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_draw.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_widgets.cpp
#        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui_demo.cpp ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/misc/cpp/imgui_stdlib.cpp
#        ${PROJECT_SOURCE_DIR}/external_libs/include/imgui/imgui-SFML.cpp)

# Controlled by PMGUI now
#set(GUI_SOURCE_FILES src/gui/controls/Button.cpp src/gui/controls/Button.h src/gui/controls/Checkbox.cpp src/gui/controls/Checkbox.h
#                     src/gui/controls/CheckboxSection.cpp src/gui/controls/CheckboxSection.h src/gui/controls/Child.cpp src/gui/controls/Child.h
#                     src/gui/controls/ColorButton.cpp src/gui/controls/ColorButton.h src/gui/controls/ColoredText.cpp src/gui/controls/ColoredText.h
#                     src/gui/controls/ColorPicker.cpp src/gui/controls/ColorPicker.h src/gui/controls/Column.cpp src/gui/controls/Column.h
#                     src/gui/controls/Combobox.cpp src/gui/controls/Combobox.h src/gui/controls/Control.cpp src/gui/controls/Control.h
#                     src/gui/controls/DataColumn.cpp src/gui/controls/DataColumn.h src/gui/controls/DataColumnDefinition.cpp
#                     src/gui/controls/DataColumnDefinition.h src/gui/controls/DataRow.cpp src/gui/controls/DataRow.h src/gui/controls/DataTable.cpp
#                     src/gui/controls/DataTable.h src/gui/controls/DragFloat.cpp src/gui/controls/DragFloat.h src/gui/controls/DragInt.cpp
#                     src/gui/controls/DragInt.h src/gui/controls/Group.cpp src/gui/controls/Group.h src/gui/controls/Image.cpp src/gui/controls/Image.h
#                     src/gui/controls/ImageButton.cpp src/gui/controls/ImageButton.h src/gui/controls/InputFloat.cpp src/gui/controls/InputFloat.h
#                     src/gui/controls/InputInt.cpp src/gui/controls/InputInt.h src/gui/controls/Label.cpp src/gui/controls/Label.h
#                     src/gui/controls/Listbox.cpp src/gui/controls/Listbox.h src/gui/controls/MenuBar.cpp src/gui/controls/MenuBar.h
#                     src/gui/controls/MenuItem.cpp src/gui/controls/MenuItem.h src/gui/controls/MenuItemCollection.cpp
#                     src/gui/controls/MenuItemCollection.h src/gui/controls/Progressbar.cpp src/gui/controls/Progressbar.h
#                     src/gui/controls/RadioSection.cpp src/gui/controls/RadioSection.h src/gui/controls/Row.cpp src/gui/controls/Row.h
#                     src/gui/controls/Selectable.cpp src/gui/controls/Selectable.h src/gui/controls/SliderFloat.cpp src/gui/controls/SliderFloat.h
#                     src/gui/controls/SliderInt.cpp src/gui/controls/SliderInt.h src/gui/controls/Table.cpp src/gui/controls/Table.h
#                     src/gui/controls/Textbox.cpp src/gui/controls/Textbox.h src/gui/controls/TreeList.cpp src/gui/controls/TreeList.h
#                     src/gui/controls/TreeNode.cpp src/gui/controls/TreeNode.h src/gui/forms/Form.cpp src/gui/forms/Form.h
#                     src/gui/forms/MessagePopup.cpp src/gui/forms/MessagePopup.h src/gui/forms/Popup.cpp src/gui/forms/Popup.h
#                     src/gui/forms/TextEditorForm.cpp src/gui/forms/TextEditorForm.h src/gui/properties/RadioData.cpp src/gui/properties/RadioData.h
#                     src/gui/properties/Tooltip.cpp src/gui/properties/Tooltip.h src/gui/themes/Theme.cpp src/gui/themes/Theme.h
#                     src/gui/TextEditor.cpp src/gui/TextEditor.h src/gui/controls/Visualizer.cpp src/gui/controls/Visualizer.h)

set(GUI_SOURCE_FILES src/gui_/controls/Visualizer.cpp src/gui_/controls/Visualizer.h)

set(SOURCE_FILES src/managers/ProgramManager.cpp src/managers/ProgramManager.h src/audio/Voice.cpp src/audio/Voice.h
                  src/managers/FormManager.cpp src/managers/FormManager.h #src/managers/EventManager.cpp src/managers/EventManager.h
                  src/forms/AudioTestForm.cpp src/forms/AudioTestForm.h src/audio/EmuStream.cpp src/audio/EmuStream.h src/audio/EmuTrackInfo.cpp
                  src/audio/EmuTrackInfo.h src/audio/AudioCommon.h src/managers/ClipboardManager.cpp src/managers/ClipboardManager.h src/audio/EmuEqualizer.cpp
                  src/audio/EmuEqualizer.h #src/widgets/FileDialog.cpp src/widgets/FileDialog.h src/widgets/FileTable.cpp src/widgets/FileTable.h
                  src/forms/SystemLog.cpp src/forms/SystemLog.h src/forms/FilelistForm.cpp src/forms/FilelistForm.h src/forms/PlaylistForm.cpp
                  src/forms/PlaylistForm.h src/classes/Timer.cpp src/classes/Timer.h src/forms/AudioPlayerForm.cpp src/forms/AudioPlayerForm.h
                  src/audio/EmuFileInfo.cpp src/audio/EmuFileInfo.h src/classes/Hotkey.cpp src/classes/Hotkey.h src/managers/Hotkeys.cpp
                  src/managers/Hotkeys.h src/data/JsonFile.cpp src/data/JsonFile.h src/data/IniFile.cpp src/data/IniFile.h src/popups/PreferencesPopup.cpp
                  src/popups/PreferencesPopup.h src/data/PlaylistFile.cpp src/data/PlaylistFile.h src/classes/PlaylistData.cpp src/classes/PlaylistData.h
                  src/audio/EmuFile.cpp src/audio/EmuFile.h src/popups/EmuFileExporterPopup.cpp src/popups/EmuFileExporterPopup.h
                  src/misc/EmuThemes.hpp src/classes/Font.cpp src/classes/Font.h src/managers/FontManager.cpp src/managers/FontManager.h
                  src/popups/AboutPopup.cpp src/popups/AboutPopup.h)

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

    add_executable(emu-jukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})
    target_link_libraries(emu-jukebox pmgui stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
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
        add_executable(EmuJukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/logo/icon.rc)
        target_link_libraries(EmuJukebox pmgui ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        #set(MY_STATIC_LIBS ${PATH_LIBS}/libfmt.a ${PATH_SFML_LIB}/libsfml-network.a ${PATH_SFML_LIB}/libsfml-audio.a ${PATH_SFML_LIB}/libsfml-graphics.a ${PATH_SFML_LIB}/libsfml-window.a ${PATH_SFML_LIB}/libsfml-system.a)
        if(DEBUG)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
        elseif(RELEASE)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
        endif()

        add_executable(EmuJukebox main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/logo/icon.rc)
        target_link_libraries(EmuJukebox pmgui stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
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
    set(MACOSX_BUNDLE_ICON_FILE "AppIcon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    #add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})
    set_source_files_properties(${PROJECT_SOURCE_DIR}/logo/AppIcon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(EmuJukebox MACOSX_BUNDLE main.cpp ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${GME_SOURCE_FILES})
    #target_link_libraries(emu-jukebox stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    #stdc++
    if(SFML_BUILD_STATIC)
        target_link_libraries(EmuJukebox pmgui stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(EmuJukebox pmgui stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
        set_target_properties(EmuJukebox PROPERTIES
                MACOSX_BUNDLE TRUE
                MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
                FRAMEWORK ${MY_DYNAMIC_LIBS})

    endif()
endif()

add_subdirectory(tests)