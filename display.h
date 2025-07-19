#pragma once
/**
 * @file display.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <memory>
#include "editor.h"

namespace otus_hw5{

    class OStreamDisplay : public IDisplay 
    {
    public:
        OStreamDisplay(std::ostream& os) : os_(os) { }
        virtual ~OStreamDisplay() = default;
        virtual IDisplay& point(coord_t x, coord_t y) override;
        virtual IDisplay& move_to(coord_t x, coord_t y) override;
        virtual IDisplay& line_to(coord_t x, coord_t y) override;
        virtual IDisplay& line(coord_t x0, coord_t y0, coord_t x1, coord_t y1) override;
        virtual IDisplay& rect(coord_t x, coord_t y, sz_t w, sz_t h) override;
        virtual IDisplay& rect(coord_t xLT, coord_t yLT, coord_t xRB, coord_t yRB) override;
        virtual IDisplay& circle(coord_t x, coord_t y, sz_t radius) override;
        virtual IDisplay& color(const rgb_t clr) override;
        virtual IDisplay& line_width(const sz_t w) override;
    private:
        std::ostream& os_;
    };
} // otus_hw5

