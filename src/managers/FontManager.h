//
// Created by robin on 26.04.19.
//

#ifndef EMU_JUKEBOX_FONTMANAGER_H
#define EMU_JUKEBOX_FONTMANAGER_H

#include "../classes/Font.h"
#include "../../content/files_mapper.h"
#include <vector>

namespace ebox
{
    class FontManager
    {
        public:
            FontManager() = default;
            void initialize();

            bool process();

            void setChosenFontAsDefaultFont();
            void setCurrentFontByName(const std::string_view &name);
            Font *getChosenFont();

            float getFontSizeFactor();

        private:
            void createFonts();
            Font *getFont(const std::string &name);
            void createDefaultFont(const std::string &name, float fontSize);
            void createFont(const std::string &name, void * data, size_t size, float fontSize);

            const std::string PREVIEW_TEXT = "HELLO! This is a rather fantastic preview of text";
            Font *m_chosenFont = nullptr;
            const char* m_currentFont = nullptr;
            bool m_fontHasBeenChosen = false;

            //Fonts
            std::vector<Font> m_fonts;
    };
}

#endif //EMU_JUKEBOX_FONTMANAGER_H
