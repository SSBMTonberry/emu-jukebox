//
// Created by robin on 12.01.18.
//

#ifndef EMU_JUKEBOX_COMBOBOX_H
#define EMU_JUKEBOX_COMBOBOX_H

#include "Control.h"
#include <vector>
namespace ebox
{
    class Combobox : public Control
    {
        public:
            Combobox(const std::string &id, const std::string &label);

            virtual bool process();

            void addValue(const std::string &value);
            void addValueRange(const std::initializer_list<std::string> &values);
            void removeValue(const std::string &value);
            void clear();

            void selectNext();
            void selectPrevious();

            void setColor(const sf::Color &text, const sf::Color &background);
            void setHasLabel(bool hasLabel, bool disablePushItemWidth = false);
            void setValue(int index);

            bool valueHasBeenChosen() const;
            bool hasLabel() const;
            const std::string &getValue() const;
            int getIndex();
            int getIndex(const std::string &id);


        protected:
            void assignColors() override;

            const char* m_currentItem = nullptr;
            std::vector<std::string> m_list;
            std::string m_value;
            bool m_hasLabel = true;
            bool m_valueHasBeenChosen = false;

            sf::Color m_textColor;
            sf::Color m_backgroundColor;
            bool m_disablePushItemWidth = false;

    };
}

#endif //EMU_JUKEBOX_COMBOBOX_H
