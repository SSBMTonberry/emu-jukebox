//
// Created by robin on 17.01.18.
//

#ifndef EMU_JUKEBOX_SELECTABLE_H
#define EMU_JUKEBOX_SELECTABLE_H

#include "Control.h"
#include "Image.h"
#include "MenuItem.h"
#include <optional>
#include <functional>

namespace ebox
{
    class Selectable : public Control
    {

        public:
            typedef std::function<void(Selectable* )> func_selectable; //OnCancel(), for instance
            typedef std::function<bool(Selectable* )> func_onrightclick; //OnCancel(), for instance
            typedef std::function<void(Selectable*, MenuItem*)> func_onchosencontextitem; //OnCancel(), for instance

            Selectable(const std::string &id, const std::string &label, std::optional<ebox::Image> image = std::nullopt);
            Selectable(const std::string &id, const std::string &label, ebox::Image *image);
            Selectable(const std::string &id, const std::string &label, const sf::Vector2<int> &size, std::optional<ebox::Image> image = std::nullopt);

            void setImage(const void *imageData, size_t imageDataSize, bool hasZoomTooltip = false);
            void setImage(const std::string &id, const void *imageData, size_t imageDataSize, bool hasZoomTooltip = false);
            void setImageRef(ebox::Image *image);
            void setSelected(bool isSelected);
            void setIsToggleable(bool isToggleable);
            void setSize(const sf::Vector2<int> &size);

            void createRightClickContextItemsAdvanced(const std::initializer_list<std::pair<std::string, std::string>> &items);
            void createRightClickContextItems(const std::initializer_list<std::string> &items);

            void registerOnChosenCallback(const func_selectable &cb);
            void registerOnRightClickCallback(const func_onrightclick &cb);
            void registerOnDoubleClickCallback(const func_selectable &cb);
            void registerOnChosenContextItemCallback(const func_onchosencontextitem &cb);

            bool process() override;

            bool isSelected() const;
            bool isToggleable() const;

            const sf::Vector2<int> &getSize() const;

            Image* getImage() ;
            Image *getImageRef() const;

        protected:
            bool processMouseEvents();

            std::vector<func_selectable> m_callbackOnChosen;
            std::vector<func_selectable> m_callbackOnDoubleClick;
            std::vector<func_onrightclick> m_callbackOnRightClick; //true: open ContextItem, false: never open.
            std::vector<func_onchosencontextitem> m_callbackOnChosenContextItem;
            std::vector<ebox::MenuItem> m_rightClickContextItems;

            std::optional<ebox::Image> m_image = std::nullopt;
            ebox::Image *m_imageRef = nullptr;
            bool m_useImageRef = false;
            sf::Vector2<int> m_size = {-1, -1};
            bool m_isSelected = false;
            bool m_isToggleable = true;
            bool m_hasSize = false;

            bool m_rightClickContextActivated = false;

    };
}

#endif //EMU_JUKEBOX_SELECTABLE_H
