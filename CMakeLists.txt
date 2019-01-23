cmake_minimum_required(VERSION 3.13)
project(emu-jukebox)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEBOX_DEBUG")

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

include_directories(${PROJECT_SOURCE_DIR}/external_libs/include/ ${PROJECT_SOURCE_DIR}/external_libs/include/libgme/ ${PROJECT_SOURCE_DIR}/external_libs/source/
        ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/freetype2/ ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/AL/
        ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/ ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/mingw/
        ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/ogg/ ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/stb_image/
        ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/vorbis/) #Had to remove ${PROJECT_SOURCE_DIR}/external_libs/include/sfml_extlibs/FLAC/

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

set(SFML_SOURCE_BASE ${PROJECT_SOURCE_DIR}/external_libs/source/SFML)

set(SFML_SOURCE_FILES_COMMON ${SFML_SOURCE_BASE}/System/Clock.cpp ${SFML_SOURCE_BASE}/System/Err.cpp ${SFML_SOURCE_BASE}/System/Lock.cpp
        ${SFML_SOURCE_BASE}/System/Mutex.cpp ${SFML_SOURCE_BASE}/System/Sleep.cpp ${SFML_SOURCE_BASE}/System/String.cpp
        ${SFML_SOURCE_BASE}/System/Thread.cpp ${SFML_SOURCE_BASE}/System/ThreadLocal.cpp ${SFML_SOURCE_BASE}/System/Time.cpp
        ${SFML_SOURCE_BASE}/System/FileInputStream.cpp ${SFML_SOURCE_BASE}/System/MemoryInputStream.cpp ${SFML_SOURCE_BASE}/Window/Clipboard.cpp
        ${SFML_SOURCE_BASE}/Window/ClipboardImpl.hpp ${SFML_SOURCE_BASE}/Window/Context.cpp ${SFML_SOURCE_BASE}/Window/Cursor.cpp
        ${SFML_SOURCE_BASE}/Window/CursorImpl.hpp ${SFML_SOURCE_BASE}/Window/GlContext.cpp ${SFML_SOURCE_BASE}/Window/GlContext.hpp
        ${SFML_SOURCE_BASE}/Window/GlResource.cpp ${SFML_SOURCE_BASE}/Window/InputImpl.hpp ${SFML_SOURCE_BASE}/Window/Joystick.cpp
        ${SFML_SOURCE_BASE}/Window/JoystickImpl.hpp ${SFML_SOURCE_BASE}/Window/JoystickManager.cpp ${SFML_SOURCE_BASE}/Window/JoystickManager.hpp
        ${SFML_SOURCE_BASE}/Window/Keyboard.cpp ${SFML_SOURCE_BASE}/Window/Mouse.cpp ${SFML_SOURCE_BASE}/Window/Touch.cpp
        ${SFML_SOURCE_BASE}/Window/Sensor.cpp ${SFML_SOURCE_BASE}/Window/SensorImpl.hpp ${SFML_SOURCE_BASE}/Window/SensorManager.cpp
        ${SFML_SOURCE_BASE}/Window/SensorManager.hpp ${SFML_SOURCE_BASE}/Window/VideoMode.cpp ${SFML_SOURCE_BASE}/Window/VideoModeImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Window.cpp ${SFML_SOURCE_BASE}/Window/WindowImpl.cpp ${SFML_SOURCE_BASE}/Window/WindowImpl.hpp
        ${SFML_SOURCE_BASE}/Network/Ftp.cpp ${SFML_SOURCE_BASE}/Network/Http.cpp ${SFML_SOURCE_BASE}/Network/IpAddress.cpp
        ${SFML_SOURCE_BASE}/Network/Packet.cpp ${SFML_SOURCE_BASE}/Network/Socket.cpp ${SFML_SOURCE_BASE}/Network/SocketImpl.hpp
        ${SFML_SOURCE_BASE}/Network/SocketSelector.cpp ${SFML_SOURCE_BASE}/Network/TcpListener.cpp ${SFML_SOURCE_BASE}/Network/TcpSocket.cpp
        ${SFML_SOURCE_BASE}/Network/UdpSocket.cpp ${SFML_SOURCE_BASE}/Graphics/BlendMode.cpp ${SFML_SOURCE_BASE}/Graphics/Color.cpp
        ${SFML_SOURCE_BASE}/Graphics/Font.cpp ${SFML_SOURCE_BASE}/Graphics/Glsl.cpp ${SFML_SOURCE_BASE}/Graphics/GLCheck.cpp
        ${SFML_SOURCE_BASE}/Graphics/GLCheck.hpp ${SFML_SOURCE_BASE}/Graphics/GLExtensions.hpp ${SFML_SOURCE_BASE}/Graphics/GLExtensions.cpp
        ${SFML_SOURCE_BASE}/Graphics/Image.cpp ${SFML_SOURCE_BASE}/Graphics/ImageLoader.cpp ${SFML_SOURCE_BASE}/Graphics/ImageLoader.hpp
        ${SFML_SOURCE_BASE}/Graphics/RenderStates.cpp ${SFML_SOURCE_BASE}/Graphics/RenderTexture.cpp ${SFML_SOURCE_BASE}/Graphics/RenderTarget.cpp
        ${SFML_SOURCE_BASE}/Graphics/RenderWindow.cpp ${SFML_SOURCE_BASE}/Graphics/Shader.cpp ${SFML_SOURCE_BASE}/Graphics/Texture.cpp
        ${SFML_SOURCE_BASE}/Graphics/TextureSaver.cpp ${SFML_SOURCE_BASE}/Graphics/TextureSaver.hpp ${SFML_SOURCE_BASE}/Graphics/Transform.cpp
        ${SFML_SOURCE_BASE}/Graphics/Transformable.cpp ${SFML_SOURCE_BASE}/Graphics/View.cpp ${SFML_SOURCE_BASE}/Graphics/Vertex.cpp
        ${SFML_SOURCE_BASE}/Graphics/GLLoader.cpp ${SFML_SOURCE_BASE}/Graphics/GLLoader.hpp
        ${SFML_SOURCE_BASE}/Graphics/Shape.cpp ${SFML_SOURCE_BASE}/Graphics/CircleShape.cpp ${SFML_SOURCE_BASE}/Graphics/RectangleShape.cpp
        ${SFML_SOURCE_BASE}/Graphics/ConvexShape.cpp ${SFML_SOURCE_BASE}/Graphics/Sprite.cpp ${SFML_SOURCE_BASE}/Graphics/Text.cpp
        ${SFML_SOURCE_BASE}/Graphics/VertexArray.cpp ${SFML_SOURCE_BASE}/Graphics/VertexBuffer.cpp ${SFML_SOURCE_BASE}/Graphics/RenderTextureImpl.cpp
        ${SFML_SOURCE_BASE}/Graphics/RenderTextureImpl.hpp ${SFML_SOURCE_BASE}/Graphics/RenderTextureImplFBO.cpp
        ${SFML_SOURCE_BASE}/Graphics/RenderTextureImplFBO.hpp ${SFML_SOURCE_BASE}/Graphics/RenderTextureImplDefault.cpp
        ${SFML_SOURCE_BASE}/Graphics/RenderTextureImplDefault.hpp ${SFML_SOURCE_BASE}/Audio/ALCheck.cpp ${SFML_SOURCE_BASE}/Audio/ALCheck.hpp
        ${SFML_SOURCE_BASE}/Audio/AlResource.cpp ${SFML_SOURCE_BASE}/Audio/AudioDevice.cpp ${SFML_SOURCE_BASE}/Audio/AudioDevice.hpp
        ${SFML_SOURCE_BASE}/Audio/Listener.cpp ${SFML_SOURCE_BASE}/Audio/Music.cpp ${SFML_SOURCE_BASE}/Audio/Sound.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundBuffer.cpp ${SFML_SOURCE_BASE}/Audio/SoundBufferRecorder.cpp ${SFML_SOURCE_BASE}/Audio/InputSoundFile.cpp
        ${SFML_SOURCE_BASE}/Audio/OutputSoundFile.cpp ${SFML_SOURCE_BASE}/Audio/SoundRecorder.cpp ${SFML_SOURCE_BASE}/Audio/SoundSource.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundStream.cpp ${SFML_SOURCE_BASE}/Audio/SoundFileFactory.cpp ${SFML_SOURCE_BASE}/Audio/SoundFileReaderFlac.hpp
        ${SFML_SOURCE_BASE}/Audio/SoundFileReaderFlac.cpp ${SFML_SOURCE_BASE}/Audio/SoundFileReaderOgg.hpp ${SFML_SOURCE_BASE}/Audio/SoundFileReaderOgg.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundFileReaderWav.hpp ${SFML_SOURCE_BASE}/Audio/SoundFileReaderWav.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundFileWriterFlac.hpp ${SFML_SOURCE_BASE}/Audio/SoundFileWriterFlac.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundFileWriterOgg.hpp ${SFML_SOURCE_BASE}/Audio/SoundFileWriterOgg.cpp
        ${SFML_SOURCE_BASE}/Audio/SoundFileWriterWav.hpp ${SFML_SOURCE_BASE}/Audio/SoundFileWriterWav.cpp)

set(SFML_SOURCE_FILES_WIN ${SFML_SOURCE_BASE}/System/Win32/ClockImpl.cpp ${SFML_SOURCE_BASE}/System/Win32/ClockImpl.hpp
        ${SFML_SOURCE_BASE}/System/Win32/MutexImpl.cpp ${SFML_SOURCE_BASE}/System/Win32/MutexImpl.hpp ${SFML_SOURCE_BASE}/System/Win32/SleepImpl.cpp
        ${SFML_SOURCE_BASE}/System/Win32/SleepImpl.hpp ${SFML_SOURCE_BASE}/System/Win32/ThreadImpl.cpp ${SFML_SOURCE_BASE}/System/Win32/ThreadImpl.hpp
        ${SFML_SOURCE_BASE}/System/Win32/ThreadLocalImpl.cpp ${SFML_SOURCE_BASE}/System/Win32/ThreadLocalImpl.hpp ${SFML_SOURCE_BASE}/Main/MainWin32.cpp
        ${SFML_SOURCE_BASE}/Window/Win32/CursorImpl.hpp ${SFML_SOURCE_BASE}/Window/Win32/CursorImpl.cpp ${SFML_SOURCE_BASE}/Window/Win32/ClipboardImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Win32/ClipboardImpl.cpp ${SFML_SOURCE_BASE}/Window/Win32/WglContext.cpp ${SFML_SOURCE_BASE}/Window/Win32/WglContext.hpp
        ${SFML_SOURCE_BASE}/Window/Win32/WglExtensions.cpp ${SFML_SOURCE_BASE}/Window/Win32/WglExtensions.hpp ${SFML_SOURCE_BASE}/Window/Win32/InputImpl.cpp
        ${SFML_SOURCE_BASE}/Window/Win32/InputImpl.hpp ${SFML_SOURCE_BASE}/Window/Win32/JoystickImpl.cpp ${SFML_SOURCE_BASE}/Window/Win32/JoystickImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Win32/SensorImpl.hpp ${SFML_SOURCE_BASE}/Window/Win32/SensorImpl.cpp ${SFML_SOURCE_BASE}/Window/Win32/VideoModeImpl.cpp
        ${SFML_SOURCE_BASE}/Window/Win32/WindowImplWin32.cpp ${SFML_SOURCE_BASE}/Window/Win32/WindowImplWin32.hpp ${SFML_SOURCE_BASE}/Network/Win32/SocketImpl.cpp
        ${SFML_SOURCE_BASE}/Network/Win32/SocketImpl.hpp)

set(SFML_SOURCE_FILES_UNIX ${SFML_SOURCE_BASE}/System/Unix/ClockImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/ClockImpl.hpp
        ${SFML_SOURCE_BASE}/System/Unix/MutexImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/MutexImpl.hpp ${SFML_SOURCE_BASE}/System/Unix/SleepImpl.cpp
        ${SFML_SOURCE_BASE}/System/Unix/SleepImpl.hpp ${SFML_SOURCE_BASE}/System/Unix/ThreadImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/ThreadImpl.hpp
        ${SFML_SOURCE_BASE}/System/Unix/ThreadLocalImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/ThreadLocalImpl.hpp ${SFML_SOURCE_BASE}/Window/Unix/CursorImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Unix/CursorImpl.cpp ${SFML_SOURCE_BASE}/Window/Unix/ClipboardImpl.hpp ${SFML_SOURCE_BASE}/Window/Unix/ClipboardImpl.cpp
        ${SFML_SOURCE_BASE}/Window/Unix/Display.cpp ${SFML_SOURCE_BASE}/Window/Unix/Display.hpp ${SFML_SOURCE_BASE}/Window/Unix/InputImpl.cpp
        ${SFML_SOURCE_BASE}/Window/Unix/InputImpl.hpp ${SFML_SOURCE_BASE}/Window/Unix/SensorImpl.cpp ${SFML_SOURCE_BASE}/Window/Unix/SensorImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Unix/VideoModeImpl.cpp ${SFML_SOURCE_BASE}/Window/Unix/WindowImplX11.cpp
        ${SFML_SOURCE_BASE}/Window/Unix/WindowImplX11.hpp ${SFML_SOURCE_BASE}/Window/Unix/JoystickImpl.cpp ${SFML_SOURCE_BASE}/Window/Unix/JoystickImpl.hpp
        ${SFML_SOURCE_BASE}/Window/Unix/GlxContext.cpp ${SFML_SOURCE_BASE}/Window/Unix/GlxContext.hpp ${SFML_SOURCE_BASE}/Window/Unix/GlxExtensions.cpp
        ${SFML_SOURCE_BASE}/Window/Unix/GlxExtensions.hpp ${SFML_SOURCE_BASE}/Network/Unix/SocketImpl.cpp ${SFML_SOURCE_BASE}/Network/Unix/SocketImpl.hpp )

# ImageLoader.cpp must be compiled with the -fno-strict-aliasing
# when gcc is used; otherwise saving PNGs may crash in stb_image_write
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties(${SFML_SOURCE_BASE}/Graphics/ImageLoader.cpp PROPERTIES COMPILE_FLAGS -fno-strict-aliasing)
endif()

set(SFML_SOURCE_FILES_OSX ${SFML_SOURCE_BASE}/System/Unix/ClockImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/ClockImpl.hpp ${SFML_SOURCE_BASE}/System/Unix/MutexImpl.cpp
        ${SFML_SOURCE_BASE}/System/Unix/MutexImpl.hpp ${SFML_SOURCE_BASE}/System/Unix/SleepImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/SleepImpl.hpp
        ${SFML_SOURCE_BASE}/System/Unix/ThreadImpl.cpp ${SFML_SOURCE_BASE}/System/Unix/ThreadImpl.hpp ${SFML_SOURCE_BASE}/System/Unix/ThreadLocalImpl.cpp
        ${SFML_SOURCE_BASE}/System/Unix/ThreadLocalImpl.hpp
        ${SFML_SOURCE_BASE}/Window/OSX/cpp_objc_conversion.h ${SFML_SOURCE_BASE}/Window/OSX/cpp_objc_conversion.mm
        ${SFML_SOURCE_BASE}/Window/OSX/cg_sf_conversion.hpp ${SFML_SOURCE_BASE}/Window/OSX/cg_sf_conversion.mm ${SFML_SOURCE_BASE}/Window/OSX/CursorImpl.hpp
        ${SFML_SOURCE_BASE}/Window/OSX/CursorImpl.mm ${SFML_SOURCE_BASE}/Window/OSX/ClipboardImpl.hpp ${SFML_SOURCE_BASE}/Window/OSX/ClipboardImpl.mm
        ${SFML_SOURCE_BASE}/Window/OSX/InputImpl.mm ${SFML_SOURCE_BASE}/Window/OSX/InputImpl.hpp ${SFML_SOURCE_BASE}/Window/OSX/HIDInputManager.hpp
        ${SFML_SOURCE_BASE}/Window/OSX/HIDInputManager.mm ${SFML_SOURCE_BASE}/Window/OSX/HIDJoystickManager.hpp
        ${SFML_SOURCE_BASE}/Window/OSX/HIDJoystickManager.cpp ${SFML_SOURCE_BASE}/Window/OSX/JoystickImpl.cpp
        ${SFML_SOURCE_BASE}/Window/OSX/JoystickImpl.hpp ${SFML_SOURCE_BASE}/Window/OSX/NSImage+raw.h ${SFML_SOURCE_BASE}/Window/OSX/NSImage+raw.mm
        ${SFML_SOURCE_BASE}/Window/OSX/Scaling.h ${SFML_SOURCE_BASE}/Window/OSX/SensorImpl.cpp ${SFML_SOURCE_BASE}/Window/OSX/SensorImpl.hpp
        ${SFML_SOURCE_BASE}/Window/OSX/SFApplication.h ${SFML_SOURCE_BASE}/Window/OSX/SFApplication.m
        ${SFML_SOURCE_BASE}/Window/OSX/SFApplicationDelegate.h ${SFML_SOURCE_BASE}/Window/OSX/SFApplicationDelegate.m
        ${SFML_SOURCE_BASE}/Window/OSX/SFContext.hpp ${SFML_SOURCE_BASE}/Window/OSX/SFContext.mm
        ${SFML_SOURCE_BASE}/Window/OSX/SFKeyboardModifiersHelper.h ${SFML_SOURCE_BASE}/Window/OSX/SFKeyboardModifiersHelper.mm
        ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView.h ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView.mm
        ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView+keyboard.mm ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView+keyboard_priv.h
        ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView+mouse.mm ${SFML_SOURCE_BASE}/Window/OSX/SFOpenGLView+mouse_priv.h
        ${SFML_SOURCE_BASE}/Window/OSX/SFSilentResponder.h ${SFML_SOURCE_BASE}/Window/OSX/SFSilentResponder.m ${SFML_SOURCE_BASE}/Window/OSX/SFWindow.h
        ${SFML_SOURCE_BASE}/Window/OSX/SFWindow.m ${SFML_SOURCE_BASE}/Window/OSX/SFWindowController.h ${SFML_SOURCE_BASE}/Window/OSX/SFWindowController.mm
        ${SFML_SOURCE_BASE}/Window/OSX/SFViewController.h ${SFML_SOURCE_BASE}/Window/OSX/SFViewController.mm
        ${SFML_SOURCE_BASE}/Window/OSX/VideoModeImpl.cpp ${SFML_SOURCE_BASE}/Window/OSX/WindowImplCocoa.hpp ${SFML_SOURCE_BASE}/Window/OSX/WindowImplCocoa.mm
        ${SFML_SOURCE_BASE}/Window/OSX/WindowImplDelegateProtocol.h ${SFML_SOURCE_BASE}/Window/OSX/AutoreleasePoolWrapper.h
        ${SFML_SOURCE_BASE}/Window/OSX/AutoreleasePoolWrapper.mm)

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
                          src/audio/EmuEqualizer.h src/forms/FileDialog.cpp src/forms/FileDialog.h src/forms/FileTable.cpp src/forms/FileTable.h src/forms/SystemLog.cpp src/forms/SystemLog.h)



if(LINUX)
    add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES} ${SFML_SOURCE_FILES_UNIX} ${SFML_SOURCE_FILES_COMMON})
    set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux)
    set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/sfml)
    #set(MY_STATIC_LIBS ${PATH_LIBS}/libclip.a ${PATH_LIBS}/libfmt.a ${PATH_LIBS}/libgme.a ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    #set(MY_STATIC_LIBS ${PATH_LIBS}/libclip.a ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    #target_link_libraries(emu-jukebox stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
    target_link_libraries(emu-jukebox stdc++fs png ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/sfml)
        if(DEBUG)
            set(MY_STATIC_LIBS ${PATH_LIBS}/fmt-s-d.lib ${PATH_SFML_LIB}/sfml-network-s-d.lib ${PATH_SFML_LIB}/sfml-audio-s-d.lib ${PATH_SFML_LIB}/sfml-main-d.lib ${PATH_SFML_LIB}/sfml-graphics-s-d.lib ${PATH_SFML_LIB}/sfml-window-s-d.lib ${PATH_SFML_LIB}/sfml-system-s-d.lib)
        elseif(RELEASE)
            set(MY_STATIC_LIBS ${PATH_LIBS}/fmt-s.lib ${PATH_SFML_LIB}/sfml-network-s.lib ${PATH_SFML_LIB}/sfml-audio-s.lib ${PATH_SFML_LIB}/sfml-main.lib ${PATH_SFML_LIB}/sfml-graphics-s.lib ${PATH_SFML_LIB}/sfml-window-s.lib ${PATH_SFML_LIB}/sfml-system-s.lib)
        endif()
        add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES} ${SFML_SOURCE_FILES_WIN} ${SFML_SOURCE_FILES_COMMON})
        #target_link_libraries(emu-jukebox ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
        target_link_libraries(emu-jukebox ${SFML_DEPENDENCIES})
    else()
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win/mingw/fmt)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/mingw/sfml/dynamic)
        set(MY_STATIC_LIBS ${PATH_LIBS}/libfmt.a ${PATH_SFML_LIB}/libsfml-network.a ${PATH_SFML_LIB}/libsfml-audio.a ${PATH_SFML_LIB}/libsfml-graphics.a ${PATH_SFML_LIB}/libsfml-window.a ${PATH_SFML_LIB}/libsfml-system.a)

        add_executable(emu-jukebox ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES} ${SFML_SOURCE_FILES_UNIX} ${SFML_SOURCE_FILES_COMMON})
        target_link_libraries(emu-jukebox stdc++fs ${MY_STATIC_LIBS})
    endif()
endif()

add_subdirectory(tests)