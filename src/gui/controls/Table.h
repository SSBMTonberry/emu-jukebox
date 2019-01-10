//
// Created by robin on 21.02.18.
//

#ifndef EMU_JUKEBOX_TABLE_H
#define EMU_JUKEBOX_TABLE_H

#include "Control.h"
#include "Row.h"

namespace ebox
{
    class Table : public Control
    {
        public:
            Table(const std::string &id, const std::string &label);

            bool process() override;
            void add(std::unique_ptr<ebox::Row> row);
            //void addRange(std::initializer_list<std::unique_ptr<ebox::Column>> &columns);

        protected:
            std::vector<std::unique_ptr<ebox::Row>> m_rows;

    };
}

#endif //EMU_JUKEBOX_TABLE_H
