#pragma once
/**
 * @file docserializer.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Сериализаторы для объектов
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <ios>
#include <memory>
#include <string>
#include "editor.h"
#include "shape.h"

namespace otus_hw5{

    /// @brief Интерфейс объекта Сериализатор объектов с интерфейсом ISerializable,
    ///  по сути представляет Посетителя в патерне Посетитель для документа и фигур.
    struct IDocSerializer  
    {
        using DocFormatTypes = IEditor::DocFormatTypes;
        virtual ~IDocSerializer() = default;
        virtual docser_ptr_t clone() const = 0;
        virtual DocFormatTypes format_type() const = 0;
        virtual void deserialize_obj(ISerializable& obj, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(ISerializable& obj, docstg_ptr_t stg_to)  = 0;

        virtual void deserialize_obj(IDocument& doc, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(IDocument& doc, docstg_ptr_t stg_to)  = 0;

        virtual void deserialize_obj(IShape& shp, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(IShape& shp, docstg_ptr_t stg_to)  = 0;

        virtual void deserialize_obj(Shape& shp, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(Shape& shp, docstg_ptr_t stg_to)  = 0;

        virtual void deserialize_obj(Point& pt, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(Point& pt, docstg_ptr_t stg_to)  = 0;

        virtual void deserialize_obj(Line& line, docstg_ptr_t stg_from)  = 0;
        virtual void serialize_obj(Line& line, docstg_ptr_t stg_to)  = 0;
    };    

    /// @brief Сериализатор - Посетитель
    class DocSerializer : public IDocSerializer
    {
    public:
        virtual ~DocSerializer() = default;
    };    

    /// @brief Сериализатор формат текст
    class DocSerializerText : public DocSerializer
    {
    public:
        virtual ~DocSerializerText() = default;
        virtual docser_ptr_t clone() const override { return docser_ptr_t{new DocSerializerText(*this)}; }
        virtual DocFormatTypes format_type() const override { return DocFormatTypes::Text; }
        virtual void deserialize_obj(ISerializable& obj, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(ISerializable& obj, docstg_ptr_t stg_to) override;

        virtual void deserialize_obj(IDocument& doc, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(IDocument& doc, docstg_ptr_t stg_to) override;

        virtual void deserialize_obj(IShape& shp, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(IShape& shp, docstg_ptr_t stg_to) override;

        virtual void deserialize_obj(Shape& shp, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(Shape& shp, docstg_ptr_t stg_to) override;

        virtual void deserialize_obj(Point& pt, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(Point& pt, docstg_ptr_t stg_to) override;

        virtual void deserialize_obj(Line& line, docstg_ptr_t stg_from) override;
        virtual void serialize_obj(Line& line, docstg_ptr_t stg_to) override;
    };    

} // otus_hw5

