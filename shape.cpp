/**
 * @file shape.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация фигур
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <unordered_map>
#include "shape.h"
#include "docserializer.h"
#include "utils.h"


namespace otus_hw5{

    class SimpleShapeCreator : public IShapeCreator
    {
    public:
        virtual ~SimpleShapeCreator() = default;
        virtual shape_ptr_t create_shape(IEditor::ShapeTypes shape_type) const override;
    };

    shape_creator_ptr_t get_shape_creator(IConfig const&)
    {
        return std::make_shared<SimpleShapeCreator>();
    } 

    void Shape::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }

    void Shape::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }

    void Point::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Point::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void Point::draw(display_ptr_t display) const
    {
        display->color(clr_).point(x_, y_);
    } 
    
    void Line::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Line::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void Line::draw(display_ptr_t display) const
    {
        display->color(clr_).line_width(line_w_).move_to(x_, y_).line_to(x1_, y1_);
    }

    void Square::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Square::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void Square::draw(display_ptr_t display) const
    {
        display->color(clr_).line_width(line_w_).move_to(x_, y_).line_to(x_ + w_, y_).line_to(x_ + w_, y_ + w_).line_to(x_, y_ + w_).line_to(x_, y_);
    }

    void Rectangle::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Rectangle::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void  Rectangle::draw(display_ptr_t display) const
    {
        display->color(clr_).line_width(line_w_).move_to(x_, y_).line_to(x_ + w_, y_).line_to(x_ + w_, y_ + h_).line_to(x_, y_ + h_).line_to(x_, y_);
    }

    void Circle::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Circle::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void Circle::draw(display_ptr_t display) const 
    {
        display->color(clr_).line_width(line_w_).circle(x_, y_, radius_);
    } 

    IShape::sz_t Circle::area() const
    {
        return 0;
    }

    void Ellipse::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
    {
        serializer->deserialize_obj(*this, stg);
    }
    
    void Ellipse::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer)
    {
        serializer->serialize_obj(*this, stg);
    }  

    void Ellipse::draw(display_ptr_t display) const 
    {
        display->color(clr_).line_width(line_w_).circle(x_, y_, a_);
    }

    IShape::sz_t Ellipse::area() const
    {
        return 0;
    }  


    shape_ptr_t SimpleShapeCreator::create_shape(IEditor::ShapeTypes shape_type) const
    {
        typedef void (*create_shape_fun_ptr_t)(shape_ptr_t&);
        using shape_creator_registry_t = std::unordered_map<IEditor::ShapeTypes, create_shape_fun_ptr_t>;
        static shape_creator_registry_t creators = {
            {IEditor::ShapeTypes::Point, (create_shape_fun_ptr_t)(&Creator<Point>::create)},
            {IEditor::ShapeTypes::Line, (create_shape_fun_ptr_t)(&Creator<Line>::create)},
            {IEditor::ShapeTypes::Rectangle, (create_shape_fun_ptr_t)(&Creator<Rectangle>::create)},
            {IEditor::ShapeTypes::Square, (create_shape_fun_ptr_t)(&Creator<Square>::create)},
            {IEditor::ShapeTypes::Circle, (create_shape_fun_ptr_t)(&Creator<Circle>::create)},
            {IEditor::ShapeTypes::Ellipse, (create_shape_fun_ptr_t)(&Creator<Ellipse>::create)},
        };
        
        shape_ptr_t p_ret;
        const auto p = creators.find(shape_type);
        if( p == creators.end() )
            throw std::invalid_argument("Cannot create shape of type " + shape_type_to_string(shape_type));

        p->second(p_ret);
        return p_ret;    
    }

} // otus_hw5

