//
// Created by robin on 27.12.17.
//

#ifndef EMU_JUKEBOX_FORM_H
#define EMU_JUKEBOX_FORM_H

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../controls/Control.h"
#include <imgui/imgui.h>
//#include <map>
#include <unordered_map>

namespace ebox
{
    class Form
    {
        public:
            Form(std::string id, std::string title, std::string imguiId = "");
            Form(const sf::Vector2<int> &position, const sf::Vector2<int> &size, std::string id,
                 std::string title, std::string imguiId);
            void add(std::unique_ptr<ebox::Control> control);
            void addReference(ebox::Control *ref);
            //void update(); //not used, for now
            virtual bool draw();
            virtual void handleEvents();

            void setOpen(bool open);
            void setIsVisible(bool isVisible);
            void setSize(const sf::Vector2<int> &size);
            void setPosition(const sf::Vector2<int> &position);
            void setScaleFactor(float scaleFactor);

            //Flags
            void setFormFlags(const FormFlags &formFlags);
            void addFormFlag(const FormFlags &formFlag);
            void removeFormFlag(const FormFlags &formFlag);
            bool hasFormFlag(const FormFlags &formFlag);

            ImGuiWindowFlags_ getFlagsAsImGuiFlags();
            FormFlags getFormFlags() const;
            std::string getImguiId();
            const std::string &getId() const;
            const sf::Vector2<int> &getSize() const;
            const sf::Vector2<int> &getPosition() const;
            const sf::Vector2<size_t> &getCurrentWindowSize() const;
            const sf::Vector2<size_t> &getCurrentWindowPosition() const;
            bool hasImguiId() const;
            float getScaleFactor() const;

            template <typename T>
            T * getControl(const std::string &id);
            template <typename T>
            T * getControlReference(const std::string &id);

            bool isOpen() const;
            bool isVisible() const;

        protected:
            virtual bool customDraw();

            bool m_positionHasBeenChanged = false;
            bool m_useLockedPosition = false;
            bool m_formIsHovered = false;
            bool m_formIsActive = false;

            virtual void onOpen() {};
            virtual void onWindowResize() {};
            virtual void onMoved() {};

            bool m_open = true;
            bool m_isVisible = true;
            FormFlags m_flags = FormFlags::None;
            std::string m_id;
            std::string m_title;
            float m_scaleFactor = 1.f;

            /*!
             * 2018-10-08 - ImGuiID should never have been a number, as it behaves like a string.
             * This string is appended after a m_title and ### when calling getImguiId().
             */
            std::string m_imguiId;
            sf::Vector2<int> m_position;
            sf::Vector2<int> m_size;
            sf::Vector2<int> m_scaledSize;

            sf::Vector2<size_t> m_previousWindowSize {0, 0};
            sf::Vector2<size_t> m_previousWindowPosition {0, 0};
            sf::Vector2<size_t> m_currentWindowSize {0, 0};
            sf::Vector2<size_t> m_currentWindowPosition {0, 0};

            std::vector<std::unique_ptr<ebox::Control>> m_controls;
            std::vector<ebox::Control *> m_controlRefs; //Pointers to items owned by something else
            //std::unordered_map<std::string, std::unique_ptr<ebox::Control>> m_controls;
    };

    template<typename T>
    T * ebox::Form::getControl(const std::string &id)
    {
        ebox::Control *control = nullptr;
        for(auto & item : m_controls)
        {
            if(item->getId().compare(id) == 0)
                control = item.get();
        }

        if(control == nullptr)
            return nullptr;

        T * reference = static_cast<T*>(control);
        return reference;
    }

    template<typename T>
    T * ebox::Form::getControlReference(const std::string &id)
    {
        ebox::Control *control = nullptr;
        for(auto & item : m_controlRefs)
        {
            if(item->getId().compare(id) == 0)
                control = item;
        }

        if(control == nullptr)
            return nullptr;

        T * reference = static_cast<T*>(control);
        return reference;
    }
}

#endif //EMU_JUKEBOX_FORM_H
