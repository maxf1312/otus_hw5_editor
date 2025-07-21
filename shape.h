#pragma once
/**
 * @file shape.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Фигуры
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
                Shape(ShapeTypes tp) : tp_(tp), x_{}, y_{}, clr_{}, line_w_{1} {}
                Shape(ShapeTypes tp, coord_t x, coord_t y) : tp_(tp), x_{x}, y_{y}, clr_{}, line_w_{1} {}
        virtual ~Shape() = default;
        virtual ShapeTypes type() const override { return tp_; }
        virtual rgb_t color() const override { return clr_; } 
        virtual IShape& color(rgb_t clr) override { return clr_ = clr, *this; }
        virtual sz_t line_width() const override { return line_w_; } 
        virtual IShape& line_width(sz_t w) override { line_w_ = w; return *this; }
        virtual point_t center() const override { return {x_, y_}; }  
        virtual IShape& center(point_t const& pt) override { return center(pt.x, pt.y); }  
        virtual IShape& center(coord_t const x, coord_t const y) override { return x_ = x, y_ = y, *this; }  
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    protected:
        ShapeTypes tp_;
        coord_t x_, y_;
        rgb_t   clr_;
        sz_t    line_w_;    
    };

    class Point : public Shape
    {
    public:        
        Point() : Shape(ShapeTypes::Point) {}
        Point(coord_t x, coord_t y) : Shape{ShapeTypes::Point, x, y} {}
        virtual ~Point() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override { return 0ULL; }
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    };
    
    class Line : public Point
    {
    public:        
        Line() : x1_{}, y1_{} { tp_ = ShapeTypes::Line; }
        Line(coord_t x, coord_t y, coord_t x1, coord_t y1) : Point(x, y), x1_{x1}, y1_{y1} { tp_ = ShapeTypes::Line; }
        virtual ~Line() = default;
        virtual void draw(display_ptr_t display) const override;
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
        point_t first() const { return {x_, y_}; }
        point_t second() const { return {x1_, y1_}; }
        Line&   first(point_t const pt) { return x_ = pt.x, y_ = pt.y, *this; }
        Line&   second(point_t const pt) { return x1_ = pt.x, y1_ = pt.y, *this;  }
    protected:
        coord_t x1_, y1_;
    };

    class Square : public Point
    {
    public:        
        Square() : w_{} { tp_ = ShapeTypes::Square; }
        Square(coord_t x, coord_t y, sz_t w) : Point(x, y), w_{w} { tp_ = ShapeTypes::Square; }
        virtual ~Square() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override { return w_*w_; } 
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    protected:
        sz_t w_;
    };

    class Rectangle : public Square
    {
    public:        
    public:        
        Rectangle() : h_{} { tp_ = ShapeTypes::Rectangle; }
        Rectangle(coord_t x, coord_t y, sz_t w, sz_t h) : Square(x, y, w), h_{h} { tp_ = ShapeTypes::Rectangle; }
        virtual ~Rectangle() = default;
        virtual void draw(display_ptr_t display) const override;
        virtual sz_t area() const override { return w_*h_; } 
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    protected:
        sz_t h_;
    };

    class Circle : public Point
    {
    public:        
        Circle() : radius_{} { tp_ = ShapeTypes::Circle; }
        Circle(coord_t x, coord_t y, sz_t radius) : Point(x, y), radius_{radius} { tp_ = ShapeTypes::Circle; }
        virtual ~Circle() = default;
        virtual void draw(display_ptr_t display) const override; 
        virtual sz_t area() const override;  
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    protected:
        sz_t radius_;
    };

    class Ellipse : public Point
    {
    public:        
        Ellipse() : a_{}, b_{}, c_{} { tp_ = ShapeTypes::Ellipse; }
        Ellipse(coord_t x, coord_t y, sz_t a, sz_t b, sz_t c) : Point(x, y), a_{a}, b_{b}, c_{c} { tp_ = ShapeTypes::Ellipse; }
        virtual ~Ellipse() = default;
        virtual void draw(display_ptr_t display) const override;
        virtual sz_t area() const override;  
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
    protected:
        sz_t a_, b_, c_;
    };




} // otus_hw5

