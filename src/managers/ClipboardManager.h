//
// Created by robin on 14.01.19.
//

#ifndef EMU_JUKEBOX_CLIPBOARDMANAGER_H
#define EMU_JUKEBOX_CLIPBOARDMANAGER_H


#include <chrono>
#include "SFML/Window.hpp"

#include <codecvt>
#include "../forms/SystemLog.h"

using namespace std;
using namespace std::chrono;

class ClipboardManager
{
    public:
        ClipboardManager();
        void update();

    protected:
        std::string ws2s(const std::wstring &s);
        std::wstring s2ws(const std::string &ws);

        //string convertToUtf8(const std::string& input);
        string m_lastOsClipboardValue = "";
        string m_lastImguiClipboardValue = "";

        time_point<high_resolution_clock> m_lastOsClipboardChange;
        time_point<high_resolution_clock> m_lastImGuiClipboardChange;
};


#endif //EMU_JUKEBOX_CLIPBOARDMANAGER_H
