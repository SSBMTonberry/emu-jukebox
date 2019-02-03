//
// Created by robin on 03.02.19.
//

#ifndef EMU_JUKEBOX_FILELISTFORM_H
#define EMU_JUKEBOX_FILELISTFORM_H

#include "../gui/forms/Form.h"

namespace ebox
{
    class FilelistForm : public Form
    {
        public:
            FilelistForm(const std::string &id, const std::string &title, const std::string &imguiId);

            FilelistForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, const std::string &id, const std::string &title,
                         const std::string &imguiId = "");

            void handleEvents() override;

            static const std::string ID;

        protected:
            bool customDraw() override;

        private:
            void initialize();
    };
}

#endif //EMU_JUKEBOX_FILELISTFORM_H
