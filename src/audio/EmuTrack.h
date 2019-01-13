//
// Created by robin on 13.01.19.
//

#ifndef EMU_JUKEBOX_EMUTRACK_H
#define EMU_JUKEBOX_EMUTRACK_H

#include "AudioCommon.h"
#include "SFML/Audio.hpp"
#include "fmt/format.h"
#include "libgme/Music_Emu.h"

namespace ebox
{
    class EmuTrack
    {
        public:
            EmuTrack();
            EmuTrack(Music_Emu *emu, int trackNumber, long sampleRate);

            bool load(Music_Emu *emu, int trackNumber, long sampleRate);

            void setTrackNumber(int trackNumber);
            void setSystem(const std::string &system);
            void setGame(const std::string &game);
            void setAuthor(const std::string &author);
            void setCopyright(const std::string &copyright);
            void setComment(const std::string &comment);
            void setDumper(const std::string &dumper);
            void setSong(const std::string &song);
            void setLength(int length);
            void setPlayLength(int playLength);
            void setIntroLength(int introLength);
            void setLoopLength(int loopLength);

            int getTrackNumber() const;
            const std::string &getSystem() const;
            const std::string &getGame() const;
            const std::string &getAuthor() const;
            const std::string &getCopyright() const;
            const std::string &getComment() const;
            const std::string &getDumper() const;
            const std::string &getSong() const;
            int getLength() const;
            int getPlayLength() const;
            int getIntroLength() const;
            int getLoopLength() const;



        private:
            Music_Emu *m_emu;
            long m_sampleRate = 44100;
            bool handleError(const char * errorText);

            int m_trackNumber = 0;
            std::string m_system;
            std::string m_game;
            std::string m_author;
            std::string m_copyright;
            std::string m_comment;
            std::string m_dumper;
            std::string m_song;
            int m_length;
            int m_introLength;
            int m_loopLength;
            int m_playLength;

            std::string m_errorText;

            std::vector<sf::Int16> m_samples;
            sf::SoundBuffer m_soundBuffer;
            sf::Sound m_sound;
    };
}

#endif //EMU_JUKEBOX_EMUTRACK_H
