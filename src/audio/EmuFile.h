//
// Created by robin on 20.04.19.
//

#ifndef EMU_JUKEBOX_EMUFILE_H
#define EMU_JUKEBOX_EMUFILE_H

#include <Music_Emu.h>
#include "Voice.h"
#include "../forms/SystemLog.h"
#include "EmuTrackInfo.h"
#include "EmuEqualizer.h"
#include <SFML/Audio.hpp>

namespace ebox
{
    class EmuFile
    {
        public:
            EmuFile();
            EmuFile(const std::string &filename, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100);
            ~EmuFile();

            bool initialize(const std::string &filename, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100, bool printAsDebug = false);

            bool createSamplesAndFillBuffer();
            bool exportToSoundFile(const std::string &path);

            void muteChannel(int channelNo, bool mute);

            void toggleMuteChannel(int channelNo);
            void unmuteAllChannels();

            void setTempo(float tempo);
            void setTrack(int track);

            size_t getNumberOfVoices();
            std::vector<Voice> *getVoices();
            const EmuTrackInfo &getInfoFromCurrentTrack() const;
            const std::vector<EmuTrackInfo> &getTracks() const;
            EmuEqualizer *getEqualizer();

            const std::string &getFilename() const;
            int getTrack() const;
            uint32_t getChannelCount() const;
            uint32_t getEmuSampleRate() const;
            int getNumberOfTracks() const;

            bool isValid() const;

        private:
            bool initializeEmu();
            bool handleError(const char *errorText);



            std::vector<sf::Int16> m_samples;

            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint32_t m_sampleRate;
            /*! 1 = mono, 2 = stereo */
            uint32_t m_channelCount;
            /*! The emulator for the sound*/
            Music_Emu *m_emu = nullptr;
            /*! The track loaded. 0 is the first track */
            int m_track = 0;
            std::string m_errorText;

            std::string m_filename;

            bool m_isValid = true;
            int m_numberOfTracks = 0;
            std::vector<Voice> m_voices;

            EmuTrackInfo m_emptyTrack; //When no track info exists
            std::vector<EmuTrackInfo> m_tracks;
            EmuEqualizer m_equalizer;

            sf::SoundBuffer m_buffer;
    };
}

#endif //EMU_JUKEBOX_EMUFILE_H
