//
// Created by robin on 16.01.18.
//

#ifndef EMU_JUKEBOX_LISTBOX_H
#define EMU_JUKEBOX_LISTBOX_H

#include "Control.h"
#include "Selectable.h"
#include <map>
namespace ebox
{
    class Listbox : public Control
    {
        public:
            Listbox(const std::string &id, const std::string &label, bool multichoice, int itemSpace = 3, int heightInItems = -2);

            bool process() override;

            void addValue(const int &id, const std::string &value);
            void addValues(const std::initializer_list<std::pair<size_t, std::string>> &values);

            void setHasLabel(bool hasLabel);
            void setItemSpace(size_t itemSpace);

            size_t getItemSpace() const;
            int getCurrentItem() const;
            bool hasLabel() const;

        protected:
            void manageItem(Selectable *item);

            //const char** getLocalItems();
            bool m_multichoice = false;
            size_t m_currentItem = 0;
            int m_itemSpace = 3; //Shows 3 items as default
            int m_heightInItems = -1;
            bool m_hasLabel = true;

            std::map<size_t, std::unique_ptr<Selectable>> m_items;
    };
}

#endif //EMU_JUKEBOX_LISTBOX_H
