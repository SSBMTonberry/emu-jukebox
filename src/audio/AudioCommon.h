//
// Created by robin on 13.01.19.
//

#ifndef EMU_JUKEBOX_AUDIOCOMMON_H
#define EMU_JUKEBOX_AUDIOCOMMON_H

enum class SampleRate : long
{
    /*! SHITTIEST QUALITY */
    _5512 = 5512,
    /*! SHIT QUALITY */
    _8269 = 8269,
    /*! BAD QUALITY */
    _11025 = 11025,
    /*! DECENT QUALITY */
    _16037 = 16037,
    /*! GOOD QUALITY */
    _22050 = 22050,
    /* VERY GOOD QUALITY */
    _33075 = 33075,
    /*! BEST QUALITY */
    _44100 = 44100
};

#endif //EMU_JUKEBOX_AUDIOCOMMON_H
