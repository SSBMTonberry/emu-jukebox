//
// Created by robin on 14.01.18.
//

#ifndef EMU_JUKEBOX_CHECKBOXSECTION_H
#define EMU_JUKEBOX_CHECKBOXSECTION_H

#include "Control.h"
#include "Checkbox.h"
#include <map>
namespace ebox
{
    class CheckboxSection : public Control
    {
        public:
            CheckboxSection(const std::string &id, const std::string &label);
            bool process() override;

            void setHorizontal(size_t itemsPerRow = 0);
            void setVertical();

            void addCheckbox(size_t id, const std::string &label, bool isChecked);
            bool isSameLine(int i);

        protected:
            bool m_isHorizontal = false;

            ///Set to 0 for unlimited items
            size_t m_itemsPerRow = 0;
            std::map<size_t, std::unique_ptr<ebox::Checkbox>> m_data;
    };
}

#endif //EMU_JUKEBOX_CHECKBOXSECTION_H
