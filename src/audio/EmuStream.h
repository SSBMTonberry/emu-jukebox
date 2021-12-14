//
// Created by robin on 12.01.19.
//

#ifndef EMU_JUKEBOX_EMUSTREAM_H
#define EMU_JUKEBOX_EMUSTREAM_H

//#include <gme_types.h>
#include <Music_Emu.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <functional>
#include "Voice.h"
#include "EmuTrackInfo.h"
#include "EmuEqualizer.h"
#include "../forms/SystemLog.h"

namespace ebox
{
    class EmuStream : public sf::SoundStream
    {
        typedef std::function<void(const sf::Int16*, size_t)> func_sampleObserver;
        public:
            enum class Mode
            {
                File = 0,
                Memory = 1
            };

            EmuStream();
            EmuStream(const fs::path &path, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100);
            EmuStream(void *data, size_t size, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100);
            EmuStream(const EmuStream &other);
            EmuStream(EmuStream &&other); //Move contructor
            ~EmuStream() override;

            EmuStream& operator=(const EmuStream &other);

            void initializeFile(const fs::path &path, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100, bool printAsDebug = false);
            void initializeMemory(void *data, size_t size, int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100, bool printAsDebug = false);

            void muteChannel(int channelNo, bool mute);

            void toggleMuteChannel(int channelNo);
            void toggleMuteChannelByHotkey(sf::Keyboard::Key key);
            void unmuteAllChannels();

            void setTempo(float tempo);
            void setTrack(int track);
            void setId(const std::string &id);
            void setNumberOfPlays(int numberOfPlays);
            void incrementNumberOfPlays();


            void nextTrack();
            void previousTrack();

            int getTimePlayed() const;
            int *getTimePlayedPtr();

            size_t getNumberOfVoices();
            std::vector<Voice> *getVoices();
            const EmuTrackInfo &getInfoFromCurrentTrack() const;
            const std::vector<EmuTrackInfo> &getTracks() const;
            EmuEqualizer *getEqualizer();

            Mode getLoadMode() const;
            const std::string &getFilename() const;

            const fs::path &getPath() const;

            int getTrack() const;
            uint32_t getChannelCount() const;
            uint32_t getEmuSampleRate() const;
            void *getData() const;
            size_t getDataSize() const;
            int getNumberOfTracks() const;
            const std::string &getId() const;
            int getNumberOfPlays() const;

            void registerSampleObserver(func_sampleObserver callback);

            bool isValid() const;

        protected:
            bool onGetData(Chunk &data) override;
            virtual void onSeek(sf::Time timeOffset) override;
            bool initializeEmu();
            bool handleError(const char *errorText);

        private:
            void copy(const EmuStream &other);
            void move(EmuStream &&other);

            std::vector<func_sampleObserver> m_sampleObservers;
            std::vector<sf::Int16> m_samples;     ///< Temporary buffer of samples
            sf::Mutex m_mutex;       ///< Mutex protecting the data

            Mode m_loadMode = Mode::File;
            uint32_t m_sampleSize; //Ref. #70
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

            std::string m_id;
            std::string m_filename; //if loaded by file - Just the filename
            fs::path    m_path; //if loaded by file
            void *m_data; //If loaded by memory
            size_t m_dataSize; //If loaded by memory

            int m_timePlayed = 0;
            bool m_isValid = true;
            bool m_isShuttingDown = false; //Set to true when calling destructor

            int m_numberOfTracks = 0;
            std::vector<Voice> m_voices;

            int m_numberOfPlays = 0;

            EmuTrackInfo m_emptyTrack; //When no track info exists
            std::vector<EmuTrackInfo> m_tracks;
            EmuEqualizer m_equalizer;
    };
}

#endif //EMU_JUKEBOX_EMUSTREAM_H
