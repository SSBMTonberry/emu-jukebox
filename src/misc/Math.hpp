//
// Created by robin on 01.08.2021.
//

#ifndef EMU_JUKEBOX_MATH_HPP
#define EMU_JUKEBOX_MATH_HPP

namespace ebox
{
    class Math
    {
        public:
            //Math
            inline static float sin(float radians) { return sinf(radians); }
            inline static float cos(float radians) { return cosf(radians); }
            inline static float sqrt(float a) { return sqrtf(a); }
            inline static float min(float a, float b) { return (a < b) ? a : b; }
            inline static float max(float a, float b) { return (a > b) ? a : b; }
            inline static float abs(float a) { return (a < 0) ? -a : a; }
            inline static float clamp(float a, float lo, float hi) { return Math::max(lo, Math::min(a, hi)); }
            inline static void sinCos(float radians, float* s, float* c) { *c = Math::cos(radians); *s = Math::sin(radians); }
            inline static float sign(float a) { return (a < 0) ? -1.0f : 1.0f; }

            /*!
             * Uses a threshold for comparing floats, as they are not precise in many cases.
             * @param a
             * @param b
             * @return
             */
            inline static bool Equal(float a, float b, float precision = 8192.f)
            {
                float threshold = 1.f / precision;
                return fabsf(a - b) < threshold;
            }
    };
}

#endif //EMU_JUKEBOX_MATH_HPP
