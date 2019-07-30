//
// Created by robin on 13.01.18.
//

#ifndef EMU_JUKEBOX_RADIOSECTION_H
#define EMU_JUKEBOX_RADIOSECTION_H

#include "Control.h"
#include "../properties/RadioData.h"
namespace ebox
{
    class RadioSection : public Control
    {
        public:
            RadioSection(const std::string &id, const std::string &label);

            bool process() override;

            void setHorizontal(size_t itemsPerRow = 0);
            void setVertical();
            void setValue(int index);
            void addRadioData(int id, const std::string &label);

            ebox::RadioData * getValue();
            std::string getValue() const;

        protected:
            bool isSameLine(int i);
            bool m_isHorizontal = false;

            ///Set to 0 for unlimited items
            size_t m_itemsPerRow = 0;
            int m_chosenItem = 0;
            std::vector<ebox::RadioData> m_data;

    };
}

#endif //EMU_JUKEBOX_RADIOSECTION_H
