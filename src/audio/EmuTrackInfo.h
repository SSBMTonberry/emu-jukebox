//
// Created by robin on 13.01.19.
//

#ifndef EMU_JUKEBOX_EMUTRACK_H
#define EMU_JUKEBOX_EMUTRACK_H

#include "AudioCommon.h"
#include "SFML/Audio.hpp"
#include "fmt/format.h"
#include <Music_Emu.h>

namespace ebox
{
    class EmuTrackInfo
    {
        public:
            EmuTrackInfo();
            EmuTrackInfo(Music_Emu *emu, int trackNumber);

            bool load(Music_Emu *emu, int trackNumber);

            void setTempo(float tempo);
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

            float getTempo() const;
            int getTrackNumber() const;
            //int getNumberOfTracks() const;
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

            const std::string &getErrorText() const;

        private:
            Music_Emu *m_emu;
            bool handleError(const char * errorText);

            int m_trackNumber = 0;
            std::string m_system;
            std::string m_game;
            std::string m_author;
            std::string m_copyright;
            std::string m_comment;
            std::string m_dumper;
            std::string m_song;
            std::string m_errorText;
            float m_tempo = 1.f;
            int m_length = -1;
            int m_introLength = -1;
            int m_loopLength = -1;
            int m_playLength = -1;


    };
}

#endif //EMU_JUKEBOX_EMUTRACK_H
