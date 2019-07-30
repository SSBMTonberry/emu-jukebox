//
// Created by robin on 17.03.18.
//

#ifndef EMU_JUKEBOX_DATACOLUMNDEFINITION_H
#define EMU_JUKEBOX_DATACOLUMNDEFINITION_H

#include "DataColumn.h"

namespace ebox
{
    class DataColumnDefinition
    {
        public:
            DataColumnDefinition() = default;

            void addColumn(const std::string &columnName, const std::string &columnTitle, size_t dataSize = 25, const DataColumnType &columnType = DataColumnType::Selectable);

            DataColumn * getColumn(const std::string &columnName);
            const std::vector<std::unique_ptr<DataColumn>> &getColumns() const;

        protected:
            std::vector<std::unique_ptr<ebox::DataColumn>> m_columns;
    };
}

#endif //EMU_JUKEBOX_DATACOLUMNDEFINITION_H
