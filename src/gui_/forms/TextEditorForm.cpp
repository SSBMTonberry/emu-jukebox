//
// Created by robin on 31.12.17.
//

#include "TextEditorForm.h"

ebox::TextEditorForm::TextEditorForm(std::string id, std::string title, std::string imguiId) : ebox::Form(std::move(id), std::move(title), std::move(imguiId))
{
    initialize();
}

ebox::TextEditorForm::TextEditorForm(const sf::Vector2<int> &position, const sf::Vector2<int> &size,
                                    std::string id, std::string title, std::string imguiId)
        : Form(position, size, std::move(id), std::move(title), std::move(imguiId))
{
    initialize();
}

void ebox::TextEditorForm::initialize()
{
    m_textEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
    m_textEditor.SetPalette(TextEditor::GetDarkPalette());
}

bool ebox::TextEditorForm::draw()
{
    if(m_isVisible)
    {
        bool setDefaultSize = false;
        if (m_positionHasBeenChanged || m_useLockedPosition)
        {
            ImGui::SetNextWindowPos(ImVec2(m_position));
            ImGui::SetNextWindowSize(ImVec2(m_size));
            m_positionHasBeenChanged = false;
        }
        else
            setDefaultSize = true;


        auto cpos = m_textEditor.GetCursorPosition();
        ImGui::Begin(getImguiId().c_str(), nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);

        if (setDefaultSize)
            ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save"))
                {
                    auto textToSave = m_textEditor.GetText();
                    /// save text....
                }
                if (ImGui::MenuItem("Quit", "Alt-F4"));
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                bool ro = m_textEditor.IsReadOnly();
                if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                    m_textEditor.SetReadOnly(ro);
                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && m_textEditor.CanUndo()))
                    m_textEditor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && m_textEditor.CanRedo()))
                    m_textEditor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, m_textEditor.HasSelection()))
                    m_textEditor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && m_textEditor.HasSelection()))
                    m_textEditor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && m_textEditor.HasSelection()))
                    m_textEditor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                    m_textEditor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    m_textEditor.SetSelection(TextEditor::Coordinates(),
                                              TextEditor::Coordinates(m_textEditor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Dark palette"))
                    m_textEditor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette"))
                    m_textEditor.SetPalette(TextEditor::GetLightPalette());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1,
                    m_textEditor.GetTotalLines(),
                    m_textEditor.IsOverwrite() ? "Ovr" : "Ins",
                    m_textEditor.CanUndo() ? "*" : " ",
                    m_textEditor.GetLanguageDefinition().mName.c_str());
        m_textEditor.Render("TextEditor");
        ImGui::End();
    }

    return m_isVisible;
}

TextEditor *ebox::TextEditorForm::getEditor()
{
    return &m_textEditor;
}



