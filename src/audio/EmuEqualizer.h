//
// Created by robin on 16.01.19.
//

#ifndef EMU_JUKEBOX_EMUEQUALIZER_H
#define EMU_JUKEBOX_EMUEQUALIZER_H

//#include <gme_types.h>
#include <Music_Emu.h>
#include <Nsf_Emu.h>
#include "pmgui.h"
//#include "imgui/imgui.h"

namespace ebox
{
    class EmuEqualizer
    {
        public:
            EmuEqualizer();
            EmuEqualizer(Music_Emu *emu);

            void initialize(Music_Emu *emu);

            void draw();
        protected:
            Music_Emu *m_emu = nullptr;
            gme_equalizer_t m_equalizer;
    };
}

#endif //EMU_JUKEBOX_EMUEQUALIZER_H
