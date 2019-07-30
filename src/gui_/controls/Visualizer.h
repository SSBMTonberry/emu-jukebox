//
// Created by alexander on 11.03.19.
//

#ifndef EMU_JUKEBOX_VISUALIZER_H
#define EMU_JUKEBOX_VISUALIZER_H

#include <vector>
#include <SFML/Config.hpp>
#include "kissfft/kissfft.hh"
#include "../../audio/EmuStream.h"
//#include "Control.h"
#include "pmgui.h"

namespace ebox {
    class Visualizer : public pmgui::Control {
    public:
        Visualizer(const std::string &id, const std::string &label);
        void attachToStream(std::unique_ptr<ebox::EmuStream> &stream);
        bool process() override;

    protected:
        typedef float fft_type;
        typedef std::complex<fft_type> cpx_type;
        kissfft<fft_type> m_fft;
        const sf::Int16 *m_samples;
        std::size_t m_samplesSize;
    };
} 

#endif //EMU_JUKEBOX_VISUALIZER_H