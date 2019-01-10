//
// Created by robin on 12.08.17.
//

#ifndef EMU_JUKEBOX_C2ENUMS_H
#define EMU_JUKEBOX_C2ENUMS_H

#include "EnumBitflags.hpp"
#include <imgui/imgui.h>

namespace ebox
{
    enum class TextboxFlags : unsigned
    {
        None = 0,
        /// Allow 0123456789.+-
        CharsDecimal = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsDecimal                ,
        /// Allow 0123456789ABCDEFabcdef
        CharsHexadecimal = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsHexadecimal        ,
        /// Turn a..z into A..Z
        CharsUppercase = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsUppercase            ,
        /// Filter out spaces, tabs
        CharsNoBlank = ImGuiInputTextFlags_::ImGuiInputTextFlags_CharsNoBlank                ,
        /// Select entire text when first taking mouse focus
        AutoSelectAll = ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll              ,
        /// Return 'true' when Enter is pressed (as opposed to when the value was modified)
        EnterReturnsTrue = ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue        ,
        /// Call user function on pressing TAB (for completion handling)
        CallbackCompletion = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCompletion    ,
        /// Call user function on pressing Up/Down arrows (for history handling)
        CallbackHistory = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackHistory          ,
        /// Call user function every time. User code may query cursor position, modify text buffer.
        CallbackAlways = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackAlways            ,
        /// Call user function to filter character. Modify data->EventChar to replace/filter input, or return 1 to discard character.
        CallbackCharFilter = ImGuiInputTextFlags_::ImGuiInputTextFlags_CallbackCharFilter    ,
        /// Pressing TAB input a '\t' character into the text field
        AllowTabInput = ImGuiInputTextFlags_::ImGuiInputTextFlags_AllowTabInput              ,
        /// In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
        CtrlEnterForNewLine = ImGuiInputTextFlags_::ImGuiInputTextFlags_CtrlEnterForNewLine  ,
        /// Disable following the cursor horizontally
        NoHorizontalScroll = ImGuiInputTextFlags_::ImGuiInputTextFlags_NoHorizontalScroll    ,
        /// Insert mode
        AlwaysInsertMode = ImGuiInputTextFlags_::ImGuiInputTextFlags_AlwaysInsertMode        ,
        /// Read-only mode
        ReadOnly = ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly                        ,
        /// Password mode, display all characters as '*'
        Password = ImGuiInputTextFlags_::ImGuiInputTextFlags_Password                        ,
        /// Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call
        NoUndoRedo = ImGuiInputTextFlags_::ImGuiInputTextFlags_NoUndoRedo                    ,
        // Allow 0123456789.+-*/eE (Scientific notation input)
        CharsScientific = ImGuiInputTextFlags_CharsScientific                                ,
        // Allow buffer capacity resize + notify when the string wants to be resized (for string types which hold a
        // cache of their Size) (see misc/stl/imgui_stl.h for an example of using this)
        CallbackResize = ImGuiInputTextFlags_CallbackResize                                  ,
    };

    enum class FormFlags : unsigned
    {
        None = 0,
        /// Disable title-bar
        NoTitleBar = ImGuiWindowFlags_NoTitleBar                                ,
        /// Disable user resizing with the lower-right grip
        NoResize = ImGuiWindowFlags_NoResize                                    ,
        /// Disable user moving the window
        NoMove = ImGuiWindowFlags_NoMove                                        ,
        /// Disable scrollbars (window can still scroll with mouse or programatically)
        NoScrollbar = ImGuiWindowFlags_NoScrollbar                              ,
        /// Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
        NoScrollWithMouse = ImGuiWindowFlags_NoScrollWithMouse                  ,
        /// Disable user collapsing window by double-clicking on it
        NoCollapse = ImGuiWindowFlags_NoCollapse                                ,
        /// Resize every window to its content every frame
        AlwaysAutoResize = ImGuiWindowFlags_AlwaysAutoResize                    ,

        /// Show borders around windows and items (OBSOLETE! Use e.g. style.FrameBorderSize=1.0f to enable borders).
        //ImGuiWindowFlags_ShowBorders                                          ,

        /// Never load/save settings in .ini file
        NoSavedSettings = ImGuiWindowFlags_NoSavedSettings                      ,
        /// Disable catching mouse or keyboard inputs, hovering test with pass through.
        NoInputs = ImGuiWindowFlags_NoInputs                                    ,
        /// Has a menu-bar
        MenuBar = ImGuiWindowFlags_MenuBar                                      ,
        /// Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f));
        /// prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
        HorizontalScrollbar = ImGuiWindowFlags_HorizontalScrollbar              ,
        /// Disable taking focus when transitioning from hidden to visible state
        NoFocusOnAppearing = ImGuiWindowFlags_NoFocusOnAppearing                ,
        /// Disable bringing window to front when taking focus (e.g. clicking on it or programatically giving it focus)
        NoBringToFrontOnFocus = ImGuiWindowFlags_NoBringToFrontOnFocus          ,
        /// Always show vertical scrollbar (even if ContentSize.y < Size.y)
        AlwaysVerticalScrollbar = ImGuiWindowFlags_AlwaysVerticalScrollbar      ,
        /// Always show horizontal scrollbar (even if ContentSize.x < Size.x)
        AlwaysHorizontalScrollbar = ImGuiWindowFlags_AlwaysHorizontalScrollbar  ,
        /// Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows,
        /// because more convenient)
        AlwaysUseWindowPadding = ImGuiWindowFlags_AlwaysUseWindowPadding        ,

        // Removed per-window ImGuiWindowFlags_ResizeFromAnySide Beta flag in favor io.ConfigResizeWindowsFromEdges=true to
        // enable the feature globally.
        // ResizeFromAnySide = ImGuiWindowFlags_ResizeFromAnySide

        // No gamepad/keyboard navigation within the window
        NoNavInputs = ImGuiWindowFlags_NoNavInputs,

        // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
        NoNavFocus = ImGuiWindowFlags_NoNavFocus,

        NoNav = NoNavInputs | NoNavFocus,
        // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context,
        // tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup,
        // etc.) without flicker.
        UnsavedDocument = ImGuiWindowFlags_UnsavedDocument,

        // Disable docking of this window
        NoDocking = ImGuiWindowFlags_NoDocking
    };

    enum class GuiSetting : unsigned
    {
        Alpha = ImGuiStyleVar_Alpha,                          // float     Alpha
        WindowPadding = ImGuiStyleVar_WindowPadding,          // ImVec2    WindowPadding
        WindowRounding = ImGuiStyleVar_WindowRounding,        // float     WindowRounding
        WindowBorderSize = ImGuiStyleVar_WindowBorderSize,    // float     WindowBorderSize
        WindowMinSize = ImGuiStyleVar_WindowMinSize,          // ImVec2    WindowMinSize
        WindowTitleAlign = ImGuiStyleVar_WindowTitleAlign,    // ImVec2    WindowTitleAlign
        ChildRounding = ImGuiStyleVar_ChildRounding,          // float     ChildRounding
        ChildBorderSize = ImGuiStyleVar_ChildBorderSize,      // float     ChildBorderSize
        PopupRounding = ImGuiStyleVar_PopupRounding,          // float     PopupRounding
        PopupBorderSize = ImGuiStyleVar_PopupBorderSize,      // float     PopupBorderSize
        FramePadding = ImGuiStyleVar_FramePadding,            // ImVec2    FramePadding
        FrameRounding = ImGuiStyleVar_FrameRounding,          // float     FrameRounding
        FrameBorderSize = ImGuiStyleVar_FrameBorderSize,      // float     FrameBorderSize
        ItemSpacing = ImGuiStyleVar_ItemSpacing,              // ImVec2    ItemSpacing
        ItemInnerSpacing = ImGuiStyleVar_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
        IndentSpacing = ImGuiStyleVar_IndentSpacing,          // float     IndentSpacing
        ScrollbarSize = ImGuiStyleVar_ScrollbarSize,          // float     ScrollbarSize
        ScrollbarRounding = ImGuiStyleVar_ScrollbarRounding,  // float     ScrollbarRounding
        GrabMinSize = ImGuiStyleVar_GrabMinSize,              // float     GrabMinSize
        GrabRounding = ImGuiStyleVar_GrabRounding,            // float     GrabRounding
        TabRounding = ImGuiStyleVar_TabRounding,              // float     TabRounding
        ButtonTextAlign = ImGuiStyleVar_ButtonTextAlign,      // ImVec2    ButtonTextAlign

        TouchExtraPadding = 100
        /*///Requires two values
        WindowPadding = 0,
        ///Requires one value
        PopupRounding = 1,
        ///Requires two values
        FramePadding = 2,
        ///Requires two values
        ItemSpacing = 3,
        ///Requires two values
        ItemInnerSpacing = 4,
        ///Requires two values
        TouchExtraPadding = 5,
        ///Requires one value
        IndentSpacing = 6,
        ///Requires one value
        ScrollbarSize = 7,
        ///Requires one value
        GrabMinSize = 8,
        ///Requires one value
        WindowBorderSize = 9,
        ///Requires one value
        ChildBorderSize = 10,
        ///Requires one value
        PopupBorderSize = 11,
        ///Requires one value
        FrameBorderSize = 12,
        ///Requires one value
        WindowRounding = 13,
        ///Requires one value
        ChildRounding = 14,
        ///Requires one value
        FrameRounding = 15,
        ///Requires one value
        ScrollbarRounding = 16,
        ///Requires one value
        GrabRounding = 17,
        ///Requires two values
        WindowTitleAlign = 18,
        ///Requires two values
        ButtonTextAlign = 19,
        TabRounding = 20*/
    };

    ENABLE_BITMASK_OPERATORS(TextboxFlags)
    ENABLE_BITMASK_OPERATORS(FormFlags)
}

#endif //EMU_JUKEBOX_C2ENUMS_H
