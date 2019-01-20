cmake_minimum_required(VERSION 3.13)
project(emu-jukebox)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

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

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/)

if(LINUX)
    set(SFML_DEPENDENCIES jpeg X11 Xrandr freetype xcb X11-xcb xcb-randr xcb-image GL FLAC ogg vorbis vorbisenc vorbisfile openal pthread)
    set(SFML_REST udev) #libudev
elseif(WIN32)
    if(MSVC)
        message("USING MSVC")
        set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/sfml)
        set(SFML_DEPENDENCIES opengl32.lib winmm.lib gdi32.lib ${PATH_SFML_DEPEND}/freetype.lib ${PATH_SFML_DEPEND}/jpeg.lib ${PATH_SFML_DEPEND}/openal32.lib ${PATH_SFML_DEPEND}/flac.lib ${PATH_SFML_DEPEND}/vorbisenc.lib ${PATH_SFML_DEPEND}/vorbisfile.lib ${PATH_SFML_DEPEND}/vorbis.lib ${PATH_SFML_DEPEND}/ogg.lib ws2_32.lib )
    else()
        message("USING MINGW")
        set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/mingw/sfml/libs-mingw/x64)
        set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/libfreetype.a ${PATH_SFML_DEPEND}/libFLAC.a ${PATH_SFML_DEPEND}/libjpeg.a ${PATH_SFML_DEPEND}/libogg.a ${PATH_SFML_DEPEND}/libopenal32.a ${PATH_SFML_DEPEND}/libvorbis.a ${PATH_SFML_DEPEND}/libvorbisenc.a ${PATH_SFML_DEPEND}/libvorbisfile.a)
        set(SFML_DEPEND_2 opengl32 winmm gdi32 freetype jpeg)
    endif()
endif()

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
                          src/managers/FormManager.cpp src/managers/FormManager.h src/managers/EventManager.cpp src/managers/EventManager.h src/forms/AudioTestForm.cpp src/forms/AudioTestForm.h src/audio/EmuStream.cpp src/audio/EmuStream.h src/audio/EmuTrackInfo.cpp src/audio/EmuTrackInfo.h src/audio/AudioCommon.h src/managers/ClipboardManager.cpp src/managers/ClipboardManager.h src/audio/EmuEqualizer.cpp src/audio/EmuEqualizer.h src/forms/FileDialog.cpp src/forms/FileDialog.h src/forms/FileTable.cpp src/forms/FileTable.h)

add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

if(LINUX)
    set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux)
    set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/sfml)
    set(MY_STATIC_LIBS ${PATH_LIBS}/libclip.a ${PATH_LIBS}/libfmt.a ${PATH_LIBS}/libgme.a ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    target_link_libraries(emu-jukebox stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/sfml)
        if(DEBUG)
            set(MY_STATIC_LIBS ${PATH_LIBS}/fmt-s-d.lib ${PATH_SFML_LIB}/sfml-network-s-d.lib ${PATH_SFML_LIB}/sfml-audio-s-d.lib ${PATH_SFML_LIB}/sfml-main-d.lib ${PATH_SFML_LIB}/sfml-graphics-s-d.lib ${PATH_SFML_LIB}/sfml-window-s-d.lib ${PATH_SFML_LIB}/sfml-system-s-d.lib)
        elseif(RELEASE)
            set(MY_STATIC_LIBS ${PATH_LIBS}/fmt-s.lib ${PATH_SFML_LIB}/sfml-network-s.lib ${PATH_SFML_LIB}/sfml-audio-s.lib ${PATH_SFML_LIB}/sfml-main.lib ${PATH_SFML_LIB}/sfml-graphics-s.lib ${PATH_SFML_LIB}/sfml-window-s.lib ${PATH_SFML_LIB}/sfml-system-s.lib)
        endif()

        target_link_libraries(emu-jukebox ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win/mingw/fmt)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/mingw/sfml/dynamic)
        set(MY_STATIC_LIBS ${PATH_LIBS}/libfmt.a ${PATH_SFML_LIB}/libsfml-network.a ${PATH_SFML_LIB}/libsfml-audio.a ${PATH_SFML_LIB}/libsfml-graphics.a ${PATH_SFML_LIB}/libsfml-window.a ${PATH_SFML_LIB}/libsfml-system.a)

        target_link_libraries(PixelmoundStudio stdc++fs ${MY_STATIC_LIBS})
    endif()
endif()

add_subdirectory(tests)