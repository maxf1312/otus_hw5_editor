/**
 * @file display.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация дисплеев
 * @version 0.1
 * @date 2025-07-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "display.h"

#define USE_DBG_TRACE
#include "mydbgtrace.h"

namespace otus_hw5
{

    IDisplay &OStreamDisplay::point(coord_t x, coord_t y)
    {
        DBG_TRACE0(os_, "point",  " x: " << x << ", y: " << y << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::move_to(coord_t x, coord_t y)
    {
        DBG_TRACE0(os_, "move_to",  " x: " << x << ", y: " << y << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::line_to(coord_t x, coord_t y)
    {
        DBG_TRACE0(os_, "line_to",  " x: " << x << ", y: " << y << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::line(coord_t x0, coord_t y0, coord_t x1, coord_t y1)
    {
        DBG_TRACE0(os_, "line",  " x0: " << x0 << ", y0: " << y0 << ", x1: " << x1 << ", y1: " << y1 <<std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::rect(coord_t x, coord_t y, sz_t w, sz_t h)
    {
        DBG_TRACE0(os_, "rect",  " x: " << x << ", y: " << y << ", w: " << w << ", h: " << h << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::rect(coord_t xLT, coord_t yLT, coord_t xRB, coord_t yRB)
    {
        DBG_TRACE0(os_, "rect",  " xLT: " << xLT << ", yLT: " << yLT << ", xRB: " << xRB << ", yRB: " << yRB << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::circle(coord_t x, coord_t y, sz_t radius)
    {
        DBG_TRACE0(os_, "circle",  " x: " << x << ", y: " << y << ", radius: " << radius <<std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::color(const rgb_t clr)
    {
        DBG_TRACE0(os_, "color",  " clr: " << clr << std::endl ); 
        return *this;
    }
    
    IDisplay &OStreamDisplay::line_width(const sz_t w)
    {
        DBG_TRACE0(os_, "line_width",  " w: " << w << std::endl ); 
        return *this;
    }
} // otus_hw5
