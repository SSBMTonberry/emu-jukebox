//
// Created by robin on 17.03.18.
//

#ifndef EMU_JUKEBOX_DATATABLE_H
#define EMU_JUKEBOX_DATATABLE_H

#include "Control.h"
#include "DataColumnDefinition.h"
#include "DataRow.h"
#include <optional>
namespace ebox
{
    class DataTable : public Control
    {
        public:
            DataTable(const std::string &id, const std::string &label);

            bool process() override;

            DataRow *newRow();
            void addColumn(const std::string &columnName, const std::string &columnTitle, const DataColumnType &dataColumnType = DataColumnType::Selectable, size_t dataSize = 25);
            const std::vector<DataColumn *> getColumns();

            const std::optional<DataRow *> &getSelectedRow() const;

        protected:
            void drawHeader();
            virtual void onHeaderColumnClicked(const std::string &id);
            virtual void onRowDoubleClicked(DataRow *row);
            virtual void onRowMarked(DataRow *row);
            void markSelectedRow();

            size_t m_rowIdCounter = 0;
            DataColumnDefinition m_columnDefinition;
            //vector<unique_ptr<DataRow>> m_rows;
            std::vector<DataRow> m_rows;
            DataRow* m_lastMarkedRow = nullptr;
            std::optional<DataRow*> m_selectedRow = std::nullopt;

    };
}

#endif //EMU_JUKEBOX_DATATABLE_H
