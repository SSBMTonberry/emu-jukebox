//
// Created by robin on 23.02.18.
//

#ifndef EMU_JUKEBOX_ROW_H
#define EMU_JUKEBOX_ROW_H

#include "Control.h"
#include "Column.h"

namespace ebox
{
    class Row : public Control
    {
        public:
            Row(const std::string &id, const std::string &label);
            bool process() override;

            void add(std::unique_ptr<ebox::Column> column);
            //void addRange(std::initializer_list<std::unique_ptr<ebox::Column>> &columns);

            void setHasVerticalBorders(bool hasVerticalBorders);
            void setHasHorizontalBorders(bool hasHorizontalBorders);

            bool hasHorizontalBorders() const;
            bool hasVerticalBorders() const;


        protected:
            std::vector<std::unique_ptr<ebox::Column>> m_columns;
            bool m_hasVerticalBorders = true;
            bool m_hasHorizontalBorders = true;
            //int m_columnsPerRow = 1;
    };


}

#endif //EMU_JUKEBOX_ROW_H
