//
// Created by robin on 12.01.19.
//

#ifndef EMU_JUKEBOX_EMUSTREAM_H
#define EMU_JUKEBOX_EMUSTREAM_H

#include "libgme/gme_types.h"
#include "libgme/Music_Emu.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <iostream>
#include <cstring>
#include "Voice.h"

namespace ebox
{
    class EmuStream : public sf::SoundStream
    {
        public:


            EmuStream();

            EmuStream(const std::string &filename, int track = 0, uint channelCount = 2, uint sampleRate = 44100);

            EmuStream(void *data, size_t size, int track = 0, uint channelCount = 2, uint sampleRate = 44100);

            ~EmuStream() override;

            void initializeFile(const std::string &filename, int track = 0, uint channelCount = 2, uint sampleRate = 44100);

            void initializeMemory(void *data, size_t size, int track = 0, uint channelCount = 2, uint sampleRate = 44100);

            void muteChannel(int channelNo, bool mute);

            void toggleMuteChannel(int channelNo);

            void toggleMuteChannelByHotkey(sf::Keyboard::Key key);

            size_t getNumberOfChannels();

            void unmuteAllChannels();

            std::vector<Voice> *getVoices();

        protected:
            bool onGetData(Chunk &data) override;

            virtual void onSeek(sf::Time timeOffset) override;

            bool initializeEmu();

            bool handleError(const char *errorText);

        private:
            enum class Mode
            {
                File = 0,
                Memory = 1
            };
            std::vector<sf::Int16> m_samples;     ///< Temporary buffer of samples
            sf::Mutex m_mutex;       ///< Mutex protecting the data

            Mode m_loadMode = Mode::File;
            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint m_sampleRate;
            /*! 1 = mono, 2 = stereo */
            uint m_channelCount;
            /*! The emulator for the sound*/
            Music_Emu *m_emu = nullptr;
            /*! The track loaded. 0 is the first track */
            int m_track = 0;
            std::string m_errorText;

            std::string m_filename; //if loaded by file
            void *m_data; //If loaded by memory
            size_t m_dataSize; //If loaded by memory

            std::vector<Voice> m_voices;
    };
}

#endif //EMU_JUKEBOX_EMUSTREAM_H
