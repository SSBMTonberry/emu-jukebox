//
// Created by alexander on 11.03.19.
//

#include <vector>
#include <algorithm>
#include "Visualizer.h"

ebox::Visualizer::Visualizer(const std::string &id, const std::string &label)
    : Control(id, label), m_samples(0), m_samplesSize(0) , m_fft(32, false)
{
    //
}

void ebox::Visualizer::attachToStream(std::unique_ptr<ebox::EmuStream> &stream) {
    stream->registerSampleObserver([this](const sf::Int16* samples, size_t size) {
        m_samples = samples;
        m_samplesSize = size;
    });
}

bool ebox::Visualizer::process() {
    if (Control::process() && m_samples != NULL) {
        std::vector<float> samples;

        /// Convert Int16 samples to float samples
        auto convertAndAddInt16ToFloat = [&samples](const sf::Int16 n) {samples.push_back((float) n / std::numeric_limits<sf::Int16>::max()); };
        std::for_each(m_samples, m_samples + m_samplesSize/2, convertAndAddInt16ToFloat);

        /// Plot samples as waveform
        auto size = ImGui::GetWindowSize();
        ImGui::PlotLines("", &samples[0], m_samplesSize / 2, 0, NULL, -1.0f, 1.0f, ImVec2(size.x, 40)); //TODO: shame on me

        /// Prepare input as complex number
        std::vector<cpx_type> in;
        std::for_each(samples.begin(), samples.end(), [&in](float f) { in.push_back(std::complex<float>(f)); });
        samples.clear();

        /// Perform FFT
        std::vector<cpx_type> out(m_samplesSize / 2);
        m_fft.assign(m_samplesSize / 2, false);
        m_fft.transform(&in[0], &out[0]);

        /// Convert output from complex to float
        auto convertAndAddCPXToFloat = [&samples](cpx_type &n) { samples.push_back(abs(n.real())); };
        std::for_each(out.begin(), out.end(), convertAndAddCPXToFloat);

        /// Find max value
        float maxval = *std::max_element(samples.begin(), samples.end(), [](float a, float b) { return (std::abs(a) < std::abs(b)); });
        /// Normalize
        int prescaler = 100; //cut off all except the first 100 bins (most action in this spectrum for 8 bit)
        int octaves = 2;
        int index = 0; //need index to do log scale
        for (auto &val : samples) {
            if (index > m_samplesSize / prescaler) break;
            float scalefac = exp(octaves * (float) index / (m_samplesSize / prescaler));
            /// Normalize and scale logarithimcally - because that is how we work
            val = (val / maxval) * scalefac;
            index++;
        }
        /// Draw frequency spectrum
        //ImGui::PlotHistogram("", &samples[0], m_samplesSize / prescaler, 0, NULL, 0, 1, ImVec2(size.x, 40)); //RBP - 12.03.2019 - Changed to PlotLines
        ImGui::PlotLines("", &samples[0], m_samplesSize / prescaler, 0, NULL, 0.f, 1.0f, ImVec2(size.x, 40)); //RBP - 12.03.2019 - Was Histogram originally.
        return true;
    }
    return false;
}