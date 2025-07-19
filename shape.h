#pragma once
/**
 * @file shape.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2025-04-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "editor.h"

namespace otus_hw5{
    struct IShapeCreator
    {
        virtual ~IShapeCreator() = default;
        virtual shape_ptr_t create_shape(IEditor::ShapeTypes shape_type) const = 0; 
    };
    using shape_creator_ptr_t = std::shared_ptr<IShapeCreator>;
    shape_creator_ptr_t get_shape_creator(IConfig const& cfg); 

    /// @brief Шаблон примеси для определения статического конструктора 
    /// @tparam CreatedT 
    /// @tparam CreatedPtrT 
    template <typename CreatedT, typename CreatedPtrT = std::unique_ptr<CreatedT> >
    struct Creator
    {
        static void create(CreatedPtrT& out_p) { out_p = std::make_unique<CreatedT>(); }
    };

    class  Shape : public IShape
    {
    public:    
                Shape() : x_{}, y_{}, clr_{}, line_w_{} {}
                Shape(coord_t x, coord_t y) : x_{x}, y_{y}, clr_{}, line_w_{} {}
        virtual ~Shape() = default;
        virtual rgb_t color() const override { return clr_; } 
        virtual IShape& color(rgb_t clr) override 
        {
            clr_ = clr;
            return *this;
        }
        virtual sz_t line_width() const override { return line_w_; } 
        virtual IShape& line_width(sz_t w) override { line_w_ = w; return *this; }
    protected:
        coord_t x_, y_;
        rgb_t   clr_;
        sz_t    line_w_;    
    };

    class Point : public Shape
    {
    public:        
        Point() = default;
        Point(coord_t x, coord_t y) : Shape{x, y} {}
        virtual ~Point() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override { return 0ULL; } 
    };
    
    class Line : public Point
    {
    public:        
        Line() : x1_{}, y1_{} {}
        Line(coord_t x, coord_t y, coord_t x1, coord_t y1) : Point(x, y), x1_{x1}, y1_{y1} {}
        virtual ~Line() = default;
        virtual void draw(display_ptr_t display) const override;
    protected:
        coord_t x1_, y1_;
    };

    class Square : public Point
    {
    public:        
        Square() : w_{} {}
        Square(coord_t x, coord_t y, sz_t w) : Point(x, y), w_{w} {}
        virtual ~Square() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override { return w_*w_; } 
    protected:
        sz_t w_;
    };

    class Rectangle : public Square
    {
    public:        
    public:        
        Rectangle() : h_{} {}
        Rectangle(coord_t x, coord_t y, sz_t w, sz_t h) : Square(x, y, w), h_{h} {}
        virtual ~Rectangle() = default;
        virtual void draw(display_ptr_t display) const override;
        virtual sz_t area() const override { return w_*h_; } 
    protected:
        sz_t h_;
    };

    class Circle : public Point
    {
    public:        
        Circle() : radius_{} {}
        Circle(coord_t x, coord_t y, sz_t radius) : Point(x, y), radius_{radius} {}
        virtual ~Circle() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override;  
    protected:
        sz_t radius_;
    };

    class Ellipse : public Point
    {
    public:        
        Ellipse() : a_{}, b_{}, c_{} {}
        Ellipse(coord_t x, coord_t y, sz_t a, sz_t b, sz_t c) : Point(x, y), a_{a}, b_{b}, c_{c} {}
        virtual ~Ellipse() = default;
        virtual void draw(display_ptr_t display) const override;
        virtual sz_t area() const override;  
    protected:
        sz_t a_, b_, c_;
    };




} // otus_hw5

