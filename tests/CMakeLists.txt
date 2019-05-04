cmake_minimum_required(VERSION 3.11)
project(tests_emu-jukebox)

set(TEST_SOURCE_FILES tests_main.cpp)

set(GUI_SOURCE_FILES ../src/gui/controls/Button.cpp ../src/gui/controls/Button.h ../src/gui/controls/Checkbox.cpp ../src/gui/controls/Checkbox.h
        ../src/gui/controls/CheckboxSection.cpp ../src/gui/controls/CheckboxSection.h ../src/gui/controls/Child.cpp ../src/gui/controls/Child.h
        ../src/gui/controls/ColorButton.cpp ../src/gui/controls/ColorButton.h ../src/gui/controls/ColoredText.cpp ../src/gui/controls/ColoredText.h
        ../src/gui/controls/ColorPicker.cpp ../src/gui/controls/ColorPicker.h ../src/gui/controls/Column.cpp ../src/gui/controls/Column.h
        ../src/gui/controls/Combobox.cpp ../src/gui/controls/Combobox.h ../src/gui/controls/Control.cpp ../src/gui/controls/Control.h
        ../src/gui/controls/DataColumn.cpp ../src/gui/controls/DataColumn.h ../src/gui/controls/DataColumnDefinition.cpp
        ../src/gui/controls/DataColumnDefinition.h ../src/gui/controls/DataRow.cpp ../src/gui/controls/DataRow.h ../src/gui/controls/DataTable.cpp
        ../src/gui/controls/DataTable.h ../src/gui/controls/DragFloat.cpp ../src/gui/controls/DragFloat.h ../src/gui/controls/DragInt.cpp
        ../src/gui/controls/DragInt.h ../src/gui/controls/Group.cpp ../src/gui/controls/Group.h ../src/gui/controls/Image.cpp ../src/gui/controls/Image.h
        ../src/gui/controls/ImageButton.cpp ../src/gui/controls/ImageButton.h ../src/gui/controls/InputFloat.cpp ../src/gui/controls/InputFloat.h
        ../src/gui/controls/InputInt.cpp ../src/gui/controls/InputInt.h ../src/gui/controls/Label.cpp ../src/gui/controls/Label.h
        ../src/gui/controls/Listbox.cpp ../src/gui/controls/Listbox.h ../src/gui/controls/MenuBar.cpp ../src/gui/controls/MenuBar.h
        ../src/gui/controls/MenuItem.cpp ../src/gui/controls/MenuItem.h ../src/gui/controls/MenuItemCollection.cpp
        ../src/gui/controls/MenuItemCollection.h ../src/gui/controls/Progressbar.cpp ../src/gui/controls/Progressbar.h
        ../src/gui/controls/RadioSection.cpp ../src/gui/controls/RadioSection.h ../src/gui/controls/Row.cpp ../src/gui/controls/Row.h
        ../src/gui/controls/Selectable.cpp ../src/gui/controls/Selectable.h ../src/gui/controls/SliderFloat.cpp ../src/gui/controls/SliderFloat.h
        ../src/gui/controls/SliderInt.cpp ../src/gui/controls/SliderInt.h ../src/gui/controls/Table.cpp ../src/gui/controls/Table.h
        ../src/gui/controls/Textbox.cpp ../src/gui/controls/Textbox.h ../src/gui/controls/TreeList.cpp ../src/gui/controls/TreeList.h
        ../src/gui/controls/TreeNode.cpp ../src/gui/controls/TreeNode.h ../src/gui/forms/Form.cpp ../src/gui/forms/Form.h
        ../src/gui/forms/MessagePopup.cpp ../src/gui/forms/MessagePopup.h ../src/gui/forms/Popup.cpp ../src/gui/forms/Popup.h
        ../src/gui/forms/TextEditorForm.cpp ../src/gui/forms/TextEditorForm.h ../src/gui/properties/RadioData.cpp ../src/gui/properties/RadioData.h
        ../src/gui/properties/Tooltip.cpp ../src/gui/properties/Tooltip.h ../src/gui/themes/Theme.cpp ../src/gui/themes/Theme.h
        ../src/gui/TextEditor.cpp ../src/gui/TextEditor.h ../src/gui/controls/Visualizer.cpp ../src/gui/controls/Visualizer.h)

set(SOURCE_FILES ../src/managers/ProgramManager.cpp ../src/managers/ProgramManager.h ../src/audio/Voice.cpp ../src/audio/Voice.h
        ../src/managers/FormManager.cpp ../src/managers/FormManager.h ../src/managers/EventManager.cpp ../src/managers/EventManager.h
        ../src/forms/AudioTestForm.cpp ../src/forms/AudioTestForm.h ../src/audio/EmuStream.cpp ../src/audio/EmuStream.h ../src/audio/EmuTrackInfo.cpp
        ../src/audio/EmuTrackInfo.h ../src/audio/AudioCommon.h ../src/managers/ClipboardManager.cpp ../src/managers/ClipboardManager.h ../src/audio/EmuEqualizer.cpp
        ../src/audio/EmuEqualizer.h ../src/widgets/FileDialog.cpp ../src/widgets/FileDialog.h ../src/widgets/FileTable.cpp ../src/widgets/FileTable.h
        ../src/forms/SystemLog.cpp ../src/forms/SystemLog.h ../src/forms/FilelistForm.cpp ../src/forms/FilelistForm.h ../src/forms/PlaylistForm.cpp
        ../src/forms/PlaylistForm.h ../src/classes/Timer.cpp ../src/classes/Timer.h ../src/forms/AudioPlayerForm.cpp ../src/forms/AudioPlayerForm.h
        ../src/audio/EmuFileInfo.cpp ../src/audio/EmuFileInfo.h ../src/classes/Hotkey.cpp ../src/classes/Hotkey.h ../src/managers/Hotkeys.cpp
        ../src/managers/Hotkeys.h ../src/data/JsonFile.cpp ../src/data/JsonFile.h ../src/data/IniFile.cpp ../src/data/IniFile.h ../src/popups/PreferencesPopup.cpp
        ../src/popups/PreferencesPopup.h ../src/data/PlaylistFile.cpp ../src/data/PlaylistFile.h ../src/classes/PlaylistData.cpp ../src/classes/PlaylistData.h
        ../src/audio/EmuFile.cpp ../src/audio/EmuFile.h ../src/popups/EmuFileExporterPopup.cpp ../src/popups/EmuFileExporterPopup.h
        ../src/misc/EmuThemes.hpp ../src/classes/Font.cpp ../src/classes/Font.h ../src/managers/FontManager.cpp ../src/managers/FontManager.h)

add_executable(tests_emu-jukebox ${TEST_SOURCE_FILES} ${SOURCE_FILES} ${GUI_SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} ${GME_SOURCE_FILES})

if(LINUX)
    target_link_libraries(tests_emu-jukebox stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        target_link_libraries(tests_emu-jukebox ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(tests_emu-jukebox stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    target_link_libraries(tests_emu-jukebox stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
endif()