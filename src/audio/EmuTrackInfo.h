//
// Created by robin on 13.01.19.
//

#ifndef EMU_JUKEBOX_EMUTRACK_H
#define EMU_JUKEBOX_EMUTRACK_H

#include "AudioCommon.h"
#include "SFML/Audio.hpp"
#include "pmgui.h"
//#include "fmt/format.h"
#include <Music_Emu.h>

namespace ebox
{
    class EmuTrackInfo
    {
        public:
            EmuTrackInfo();
            EmuTrackInfo(Music_Emu *emu, int trackNumber, const std::string &filename);

            bool load(Music_Emu *emu, int trackNumber, const std::string &filename);

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

            [[nodiscard]] float getTempo() const;
            [[nodiscard]] int getTrackNumber() const;
            //int getNumberOfTracks() const;
            [[nodiscard]] const std::string &getSystem() const;
            [[nodiscard]] const std::string &getGame() const;
            [[nodiscard]] const std::string &getAuthor() const;
            [[nodiscard]] const std::string &getCopyright() const;
            [[nodiscard]] const std::string &getComment() const;
            [[nodiscard]] const std::string &getDumper() const;
            [[nodiscard]] const std::string &getSong() const;
            [[nodiscard]] const std::string &getFilename() const;

            [[nodiscard]] int getLength() const;
            [[nodiscard]] int getPlayLength() const;
            [[nodiscard]] int getIntroLength() const;
            [[nodiscard]] int getLoopLength() const;
            [[nodiscard]] const std::string &getErrorText() const;

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
            std::string m_filename;
            float m_tempo = 1.f;
            int m_length = -1;
            int m_introLength = -1;
            int m_loopLength = -1;
            int m_playLength = -1;


    };
}

#endif //EMU_JUKEBOX_EMUTRACK_H
