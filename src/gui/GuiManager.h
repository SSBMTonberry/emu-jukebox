//
// Created by robin on 18.12.17.
//

#ifndef EMU_JUKEBOX_GUIMANAGER_H
#define EMU_JUKEBOX_GUIMANAGER_H

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "Themes/Theme.h"
#include "imgui-SFML.h"

#include "fmt/format.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "../EventManager.h"

#include "Forms/Form.h"
#include "Controls/GuiFactory.h"
#include "Forms/TextEditorForm.h"

using namespace std;

namespace ebox
{
    class GuiManager
    {
            typedef std::function<void(void)> func_customdraw; //OnCancel(), for instance
        public:
            enum class GuiTheme : uint
            {
                Classic = 0,
                Dark = 1,
                Light = 2,
                /*! Open the Style Editor of ImGui */
                Custom = 3
            };

            GuiManager();

            GuiManager(sf::RenderWindow *window, ebox::EventManager *eventManager);


            void initialize(sf::RenderWindow *window, ebox::EventManager *eventManager);
            void addForm(std::unique_ptr<ebox::Form> form);
            void addFormReference(ebox::Form * form);
            void addTestForm();
            bool isShowImguiDemoWindow() const;

            void setTheme(const GuiTheme &theme);
            void setTheme(Theme &theme);
            void setSetting(const GuiSetting &setting, const float &x, const float &y);
            void setShowImguiDemoWindow(bool showImguiDemoWindow);

            ebox::Form *getForm(const std::string &id);

            template <typename T>
            T * getForm(const std::string &id);
            template <typename T>
            T * getFormReference(const std::string &id);

            void registerOnCustomDrawCallback(const func_customdraw &cb);

            void update();
            void draw(bool callWindowDisplay = false);
            void handleEvents();
            bool run(bool callWindowDisplay = false);

        protected:
            bool m_showImguiDemoWindow = false;
            ImGuiStyle *m_style = nullptr;
            ImGuiIO *m_io = nullptr;

            std::vector<std::unique_ptr<ebox::Form>> m_forms;
            std::vector<ebox::Form *> m_formRefs;
            std::vector<func_customdraw> m_callbackOnCustomDraw;
            //std::map<std::string, std::unique_ptr<ebox::Form>> m_forms;
            sf::RenderWindow *m_window;
            ebox::EventManager *m_eventManager;
            sf::Clock m_deltaClock;
    };
}

template<typename T>
T * ebox::GuiManager::getForm(const std::string &id)
{
    ebox::Form *form = nullptr;
    for(auto & item : m_forms)
    {
        if(item->getId().compare(id) == 0)
            form = item.get();
    }

    if(form == nullptr)
        return nullptr;

    T * reference = static_cast<T*>(form);
    return reference;
}

template<typename T>
T * ebox::GuiManager::getFormReference(const std::string &id)
{
    ebox::Form *form = nullptr;
    for(auto & item : m_formRefs)
    {
        if(item->getId().compare(id) == 0)
            form = item;
    }

    if(form == nullptr)
        return nullptr;

    T * reference = static_cast<T*>(form);
    return reference;
}

#endif //EMU_JUKEBOX_GUIMANAGER_H
