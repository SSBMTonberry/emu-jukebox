//
// Created by robin on 17.03.18.
//

#include "DataRow.h"


ebox::DataRow::DataRow(const std::string &id, ebox::DataColumnDefinition *columnDefinition,
                      size_t imguiId) : m_id {id}, m_columnDefinition {columnDefinition}, m_imguiId {imguiId}
{
    //m_id = id;
    //m_columnDefinition = columnDefinition;
    initialize();
}

void ebox::DataRow::initialize()
{
    for(auto const &item : m_columnDefinition->getColumns())
    {
        create(item.get());
    }
}

bool ebox::DataRow::process()
{
    refreshColumns();
    bool anyItemActivated = false;
    m_isSelected = false;
    //m_isDoubleClicked = false;
    if(m_columnDefinition->getColumns().size() > 0)
    {
        ImGui::Columns(m_columnDefinition->getColumns().size(), m_id.c_str(), m_hasVerticalBorders);
        for (const auto &column : m_columnDefinition->getColumns())
        {
            if(column->hasWidth())
            {
                ImGui::SetColumnWidth(ImGui::GetColumnIndex(), column->getWidth());
            }

            if (m_hasHorizontalBorders && ImGui::GetColumnIndex() == 0)
                ImGui::Separator();

            //if (processColumn(column.get()))
            //if(column->getDataColumnType() == DataColumnType::Selectable)
            //    getAs<ebox::Selectable>(column->getName())->setSelected(false);

            if(m_values[column->getName()]->process())
            {
                anyItemActivated = true;
                m_isSelected = true;
            }

            if(m_isMarked && ImGui::IsMouseDoubleClicked(0))
            {
                m_isDoubleClicked = true;
            }

            ImGui::NextColumn();
        }
        ImGui::Columns(1); //Do this to prevent nesting, which makes things crash :(
    }
    return anyItemActivated;
}

void ebox::DataRow::setValue(const std::string &key, const std::string &value)
{
    if(m_values.count(key))
    {
        switch(m_columnDefinition->getColumn(key)->getDataColumnType())
        {
            case DataColumnType::Selectable:
                m_values[key]->setLabel(value);
                break;

            case DataColumnType::Textbox:
                getAs<ebox::Textbox>(key)->setValue(value);
                break;
        }
    }
}

/*!
 *
 * @param values List of values in the order of how the columns were added
 */
void ebox::DataRow::setValues(const std::initializer_list<std::string> &values)
{

    int i = 0;
    for(auto const &[key, val] : m_values)
    {
        int j = 0;
        for(const auto &value : values)
        {
            if (i < values.size() && i < m_values.size() && i == j)
            {
                switch(m_columnDefinition->getColumn(key)->getDataColumnType())
                {
                    case DataColumnType::Selectable:
                        m_values[key]->setLabel(value);
                        break;

                    case DataColumnType::Textbox:
                        getAs<ebox::Textbox>(key)->setValue(value);
                        break;
                }
            }
            ++j;
        }
        ++i;
    }
}

/*!
 * Like setValues, but requires a pair with id and value
 * @param values {"key", "value"}
 */
void ebox::DataRow::setValuesWithKey(const std::initializer_list<std::pair<std::string, std::string>> &values)
{
    for(auto const &[key, val] : values)
    {
        if(m_values.count(key) > 0)
        {
            switch(m_columnDefinition->getColumn(key)->getDataColumnType())
            {
                case DataColumnType::Selectable:
                    m_values[key]->setLabel(val);
                    break;

                case DataColumnType::Textbox:
                    getAs<ebox::Textbox>(key)->setValue(val);
                    break;
            }
        }
    }
}

void ebox::DataRow::setImage(const std::string &key, const void *imageData, size_t imageDataSize)
{
    if(m_values.count(key))
    {
        switch(m_columnDefinition->getColumn(key)->getDataColumnType())
        {
            case DataColumnType::Image:
                getAs<ebox::Image>(key)->create(imageData, imageDataSize);
                break;

            case DataColumnType::Selectable:
                getAs<ebox::Selectable>(key)->setImage(fmt::format("{0}_img", key), imageData, imageDataSize);
                break;
        }
    }
}

/*!
 * A quicker way to load image into a row, by using an existing one.
 * @param key
 * @param img
 */
void ebox::DataRow::setImageRef(const std::string &key, ebox::Image *img)
{
    if(m_values.count(key) && img != nullptr)
    {
        switch(m_columnDefinition->getColumn(key)->getDataColumnType())
        {
            case DataColumnType::Image:
                getAs<ebox::Image>(key)->create(img->getSprite());
                break;

            case DataColumnType::Selectable:
                getAs<ebox::Selectable>(key)->setImageRef(img);
                break;
        }
    }
}


/*!
 * Refreshes the columns, and adds missing columns if they are new to the column definition
 */
void ebox::DataRow::refreshColumns()
{
    for(auto const &item : m_columnDefinition->getColumns())
    {
        if(m_values.count(item->getName()) == 0)
            create(item.get());
    }
}

bool ebox::DataRow::hasVerticalBorders() const
{
    return m_hasVerticalBorders;
}

void ebox::DataRow::setHasVerticalBorders(bool hasVerticalBorders)
{
    m_hasVerticalBorders = hasVerticalBorders;
}

bool ebox::DataRow::hasHorizontalBorders() const
{
    return m_hasHorizontalBorders;
}

void ebox::DataRow::setHasHorizontalBorders(bool hasHorizontalBorders)
{
    m_hasHorizontalBorders = hasHorizontalBorders;
}

/*bool ebox::DataRow::processColumn(const ebox::DataColumn *col)
{
    switch(col->getDataColumnType())
    {
        case DataColumnType::Selectable:
            if(ImGui::Selectable(m_values[col->getName()].c_str(), false))
            {
                return true;
            }
            break;

        case DataColumnType::Textbox:
            break;
    }

    return false;
}*/

void ebox::DataRow::create(const ebox::DataColumn *col)
{
    switch(col->getDataColumnType())
    {
        case DataColumnType::Selectable:
        {
            auto selectable = std::make_shared<ebox::Selectable>(col->getName(), "");
            selectable->setIsToggleable(false);
            m_values[col->getName()] = std::move(selectable);
            //m_values.insert(std::unordered_map<std::string, std::unique_ptr<ebox::Control>>::value_type(col->getName(), std::move(selectable)));
        }
        break;

        case DataColumnType::Image:
            //m_values.insert(std::unordered_map<std::string, std::unique_ptr<ebox::Control>>::value_type(col->getName(), make_unique<ebox::Image>(col->getName())));
            m_values[col->getName()] = std::make_shared<ebox::Image>(col->getName());
            break;

        case DataColumnType::Textbox:
        {
            auto textbox = std::make_shared<ebox::Textbox>(col->getName(), "", col->getDataSize(), m_imguiId);
            textbox->setHasLabel(false);
            //m_values.insert(std::unordered_map<std::string, std::unique_ptr<ebox::Control>>::value_type(col->getName(), std::move(textbox)));
            m_values[col->getName()] = std::move(textbox);
        }
        break;
    }
}

const std::string &ebox::DataRow::getValue(const std::string &item) const
{
    return m_values.find(item)->second->getLabel(); //Using find to get value and promise not to modify the map
}

bool ebox::DataRow::isSelected() const
{
    return m_isSelected;
}

void ebox::DataRow::mark()
{
    if(!m_isMarked)
    {
        m_isMarked = true;
        for (const auto &column : m_columnDefinition->getColumns())
        {
            if (column->getDataColumnType() == DataColumnType::Selectable)
                getAs<ebox::Selectable>(column->getName())->setSelected(m_isMarked);
        }
    }
}

void ebox::DataRow::unmark()
{
    if(m_isMarked)
    {
        m_isMarked = false;
        for (const auto &column : m_columnDefinition->getColumns())
        {
            if (column->getDataColumnType() == DataColumnType::Selectable)
                getAs<ebox::Selectable>(column->getName())->setSelected(m_isMarked);
        }
    }
}

bool ebox::DataRow::isDoubleClicked() const
{
    return m_isDoubleClicked;
}

void ebox::DataRow::resetIsDoubleClicked()
{
    m_isDoubleClicked = false;
}