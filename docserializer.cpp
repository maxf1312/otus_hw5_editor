/**
 * @file docserializer.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация сериализаторов 
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <limits>
#include "docserializer.h"
#include "utils.h"

#define USE_DBG_TRACE
#include "mydbgtrace.h"

namespace otus_hw5{
    using namespace std;

    /// @brief Сериализатор документов, по сути представляет Посетителя в патерне Посетитель для документа и фигур.
    void DocSerializerText::DocSerializerText::deserialize_obj(ISerializable&, docstg_ptr_t)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 

    }

    void DocSerializerText::DocSerializerText::serialize_obj(ISerializable&, docstg_ptr_t) 
    {
        DBG_TRACE("serialize_obj",  std::endl ); 

    }

    void DocSerializerText::DocSerializerText::deserialize_obj(IDocument& doc, docstg_ptr_t stg_from)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 
        string doc_signature{}, shp_tp_str{};
        size_t shape_count{}; 
        stg_from->inputstream() >> doc_signature >> shape_count;
        if( doc_signature != "ImgDoc" )
            throw std::logic_error("Bad document format");
        
        doc.shapes().remove_all();
        const auto ser_for_shapes = clone();
        auto& editor = the_editor();  
        for( ; shape_count-- > 0 && stg_from->inputstream(); )
        {
            stg_from->inputstream() >> shp_tp_str;
            IShape::ShapeTypes tp = shape_type_from_string(shp_tp_str);
            shape_ptr_t shp = editor.create_shape(tp);
            shp->deserialize(stg_from, ser_for_shapes);
            doc.add_shape(std::move(shp));
            stg_from->inputstream().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }        
    }
    
    void DocSerializerText::DocSerializerText::serialize_obj(IDocument& doc, docstg_ptr_t stg_to)
    {
        DBG_TRACE("serialize_obj",  std::endl );
        stg_to->outputstream() << "ImgDoc " << doc.shapes().count() << std::endl;
        const auto ser_for_shapes = clone();
        for(size_t i = 0, N = doc.shapes().count(); i < N; ++i)
        {
            doc.shapes().at(i)->serialize(stg_to, ser_for_shapes);
        } 
    }

    void DocSerializerText::deserialize_obj(IShape& shp, docstg_ptr_t stg)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 
        uint32_t clr{};
        IShape::sz_t line_w;
        IShape::point_t pt;
        stg->inputstream() >> clr >> line_w >> pt.x >> pt.y;
        shp.color(clr).line_width(line_w).center(pt);
    }
    
    void DocSerializerText::serialize_obj(IShape& shp, docstg_ptr_t stg)
    {
        DBG_TRACE("serialize_obj",  std::endl ); 
        stg->outputstream() << shape_type_to_string(shp.type()) << ' ' << shp.color() << ' ' << shp.line_width() 
                            << ' ' << shp.center().x << ' ' << shp.center().y << ' ';
    }

    void DocSerializerText::deserialize_obj(Shape& shp, docstg_ptr_t stg_from)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 
        deserialize_obj(static_cast<IShape&>(shp), stg_from);
    }
    
    void DocSerializerText::serialize_obj(Shape& shp, docstg_ptr_t stg_to)
    {
        DBG_TRACE("serialize_obj",  std::endl ); 
        serialize_obj(static_cast<IShape&>(shp), stg_to);
    }

    void DocSerializerText::deserialize_obj(Point& pt, docstg_ptr_t stg_from)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 
        deserialize_obj(static_cast<Shape&>(pt), stg_from);
    }
    
    void DocSerializerText::serialize_obj(Point& pt, docstg_ptr_t stg_to)
    {
        DBG_TRACE("serialize_obj",  std::endl );
        serialize_obj(static_cast<Shape&>(pt), stg_to);
        stg_to->outputstream() << std::endl;
    }

    void DocSerializerText::deserialize_obj(Line& line, docstg_ptr_t stg_from)
    {
        DBG_TRACE("deserialize_obj",  std::endl ); 
        deserialize_obj(static_cast<Point&>(line), stg_from);
        IShape::point_t pt;
        stg_from->inputstream() >> pt.x >> pt.y;
        line.second(pt);
    }

    void DocSerializerText::serialize_obj(Line& line, docstg_ptr_t stg_to)
    {
        DBG_TRACE("serialize_obj",  std::endl ); 
        serialize_obj(static_cast<Shape&>(line), stg_to);
        stg_to->outputstream() << line.second().x << ' ' << line.second().y << ' ';
        stg_to->outputstream() << std::endl;
    }


} // otus_hw5

