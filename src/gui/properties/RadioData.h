//
// Created by robin on 13.01.18.
//

#ifndef EMU_JUKEBOX_RADIODATA_H
#define EMU_JUKEBOX_RADIODATA_H

#include <iostream>

namespace ebox
{
    class RadioData
    {
        public:
            RadioData(const int &id, const std::string &label);

            int getId() const;
            const std::string &getLabel() const;

            void setId(int id);
            void setLabel(const std::string &label);

        protected:
            int m_id;
            std::string m_label;

    };
}

#endif //EMU_JUKEBOX_RADIODATA_H
