//
// Created by robin on 31.12.17.
//

#ifndef EMU_JUKEBOX_TEXTEDITORFORM_H
#define EMU_JUKEBOX_TEXTEDITORFORM_H


#include "Form.h"
#include "../TextEditor.h"
namespace ebox
{
    class TextEditorForm : public Form
    {
        public:
            TextEditorForm(std::string id, std::string title, std::string imguiId = "");
            TextEditorForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size, std::string id, std::string title, std::string imguiId = "");
            bool draw() override;

            TextEditor *getEditor();

        private:
            void initialize();

            TextEditor m_textEditor;
    };
}

#endif //EMU_JUKEBOX_TEXTEDITORFORM_H
