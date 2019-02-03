//
// Created by robin on 21.01.19.
//

#ifndef EMU_JUKEBOX_SYSTEMLOG_H
#define EMU_JUKEBOX_SYSTEMLOG_H

#include "../gui/forms/Form.h"
#include "../gui/controls/Textbox.h"
//#include <Clipboard/Clipboard.h>
#include "../gui/controls/ColoredText.h"
#include "../../content/files_mapper.h"
#include <SFML/Graphics.hpp>
#include <chrono>

namespace ebox
{
    class SystemLog
    {
        public:
            static SystemLog *get() {
                static SystemLog log;
                return &log;
            }

            bool process();

            void add(const std::string &text, const sf::Color &color = {255, 255, 255, 255});
            void addSuccess(const std::string &text, bool useTimestamp = true);
            void addInfo(const std::string &text, bool useTimestamp = true);
            void addWarning(const std::string &text, bool useTimestamp = true);
            void addError(const std::string &text, bool useTimestamp = true);
            void addDebug(const std::string &text, bool useTimestamp = true);
            void addTestTexts();

            void setOpen(bool open);
            void setIsVisible(bool isVisible);
            void setSize(const sf::Vector2<int> &size);
            void setPosition(const sf::Vector2<int> &position);

            const sf::Vector2<int> &getSize() const;
            const sf::Vector2<int> &getPosition() const;

            void clear();

            static const std::string ID;

            const sf::Color SuccessColor{0, 182, 0, 255};
            const sf::Color InfoColor{146, 182, 255, 255};
            const sf::Color WarningColor{255, 219, 0, 255};
            const sf::Color ErrorColor{240, 0, 0, 255};
            const sf::Color DebugColor{157, 65, 204, 255};

            bool isOpen() const;
            bool isVisible() const;

        protected:
            std::string getTimestamp(bool includeDate = false);

            std::vector<ebox::ColoredText> getFilteredTexts(const std::string &filter);

            size_t m_nextId = 0;

            bool m_isVisible = true;
            bool m_isOpen = true;

            bool m_positionHasBeenChanged = false;
            sf::Vector2<int> m_position;
            sf::Vector2<int> m_size;

            ebox::Textbox m_filter{"filter_textbox", "Filter", 0};//255};
            std::vector<ebox::ColoredText> m_filteredTexts;
            std::vector<ebox::ColoredText> m_texts;
            sf::Image m_image;

        private:
            explicit SystemLog(const sf::Vector2<int> &sizeOnFirstUse = {640, 480});
    };
}

#endif //EMU_JUKEBOX_SYSTEMLOG_H
