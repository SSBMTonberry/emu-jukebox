//
// Created by robin on 30.01.18.
//

#ifndef EMU_JUKEBOX_COLUMN_H
#define EMU_JUKEBOX_COLUMN_H

#include "Control.h"
#include <optional>

namespace ebox
{
    class Column : public Control
    {
        public:
            Column(const std::string &id, const std::string &label, const std::optional<float> &width = std::nullopt);

            bool process() override;

            void add(std::unique_ptr<ebox::Control> control);

            const float getWidth() const;
            const bool hasWidth();
            void setWidth(const std::optional<float> &width);
            void setWidthByPercent(size_t widthByPercentOfAvailableSpace);

        protected:
            std::vector<std::unique_ptr<ebox::Control>> m_items;
            std::optional<float> m_width = std::nullopt;
    };
}

#endif //EMU_JUKEBOX_COLUMN_H
