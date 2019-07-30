//
// Created by robin on 24.01.18.
//

#ifndef EMU_JUKEBOX_MENUITEM_H
#define EMU_JUKEBOX_MENUITEM_H

#include "Control.h"
#include "Image.h"
#include <functional>
namespace ebox
{
    class MenuItem : public Control
    {
        typedef std::function<void(MenuItem* )> func_menuitem; //OnCancel(), for instance
        typedef std::function<bool(MenuItem* )> func_onrightclick; //OnCancel(), for instance

        public:
            MenuItem(const std::string &id, const std::string &label, std::unique_ptr<ebox::Image> image = nullptr);
            MenuItem(const std::string &id, const std::string &label, ebox::Image* image);

            bool process() override;

            void setIsSelected(bool isSelected);
            void setIsPressed(bool isPressed);
            void setShortcut(const std::string &shortcut);
            void setImage(std::unique_ptr<Image> image);
            void setImageRef(ebox::Image *image);

            void registerOnChosenCallback(const func_menuitem &cb);
            void registerOnRightClickCallback(const func_onrightclick &cb);
            void registerOnDoubleClickCallback(const func_menuitem &cb);

            bool handlePressEvent();

            bool isPressed() const;
            bool isSelected() const;
            const std::string &getShortcut() const;

        protected:

            std::unique_ptr<ebox::Image> m_image = nullptr;
            ebox::Image *m_imageRef = nullptr;
            bool m_useImageRef = false;

            std::string m_shortcut = "";

            std::vector<func_menuitem> m_callbackOnChosen;
            std::vector<func_menuitem> m_callbackOnDoubleClick;
            std::vector<func_onrightclick> m_callbackOnRightClick; //true: open ContextItem, false: never open.

            bool m_isPressed = false;
            bool m_isSelected = false;
            bool m_isEnabled = true;
    };
}

#endif //EMU_JUKEBOX_MENUITEM_H
