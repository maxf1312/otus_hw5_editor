#pragma once
/**
 * @file editor.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <memory>
#include "smartptrcoll.h"

namespace otus_hw5{
    struct IEditor;
    struct IObserver;
    struct ISubject;
    struct IDocument;
    struct IDocStorage;
    struct IShape;
    struct IDisplay;
    struct IDocView;
    struct IConfig;

    using editor_ptr_t = std::unique_ptr<IEditor>;
    using doc_ptr_t = std::shared_ptr<IDocument>;
    using doc_wptr_t = std::weak_ptr<IDocument>;
    using config_ptr_t = std::unique_ptr<IConfig>;
    using docstg_ptr_t = std::unique_ptr<IDocStorage>;
    using shape_ptr_t = std::unique_ptr<IShape>;
    using view_ptr_t = std::shared_ptr<IDocView>;
    using display_ptr_t = std::shared_ptr<IDisplay>;
    using observer_ptr_t = std::shared_ptr<IObserver>;
    using subject_ptr_t = std::shared_ptr<ISubject>;
    using subject_wptr_t = std::weak_ptr<ISubject>;

    using doc_ptr_coll_t = SmartPtrCollection<doc_ptr_t>;
    using view_ptr_coll_t = SmartPtrCollection<view_ptr_t>;
    using shape_ptr_coll_t = SmartPtrCollection<shape_ptr_t>;

    struct IEditor
    {
        enum class ShapeTypes : uint8_t
        {
            Point,
            Line,
            Rectangle,
            Square,
            Circle,
            Ellipse
        };  
        
        virtual ~IEditor() = default;
        virtual doc_ptr_t& create_new_doc(IConfig const& cfg) = 0;
        virtual doc_ptr_coll_t& docs() = 0;

        virtual doc_ptr_t import_doc_from(docstg_ptr_t const& stg) = 0;
        virtual void export_doc_to(doc_ptr_t const& doc, docstg_ptr_t& stg) = 0;
        virtual shape_ptr_t create_shape(ShapeTypes shape_type) = 0;
        virtual view_ptr_t& create_new_view(IConfig const& cfg) = 0;
        virtual view_ptr_coll_t& views() = 0;

        virtual display_ptr_t display() const = 0;
    };

    struct ISubject : public std::enable_shared_from_this<ISubject>
    {
        enum class Events: uint8_t 
        {
            kNone,
            kChanged,
            kDestroing
        };  

        virtual ~ISubject() noexcept = default;
        virtual void subscribe(observer_ptr_t observer) = 0;
        virtual void unsubscribe(observer_ptr_t observer) = 0;
        virtual void set_changed(bool was_changed) = 0;
        virtual void notify_all() = 0;
    };
    struct IObserver : public std::enable_shared_from_this<IObserver>
    {
        virtual ~IObserver() = default;
        virtual void subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const = 0;
    };

    struct IDocument 
    {
        virtual ~IDocument() = default;
        virtual void import_from(docstg_ptr_t const stg) = 0;
        virtual void export_to(docstg_ptr_t stg) = 0;
        virtual void add_shape(shape_ptr_t&& shp) = 0;
        virtual void remove_shape(shape_ptr_t const& shp) = 0;
        virtual shape_ptr_coll_t& shapes() = 0;        
        virtual void add_view(view_ptr_t v) = 0;
        virtual void remove_view(view_ptr_t v) = 0;
        virtual ISubject& as_subject() = 0;
    };
    
    struct IShape
    {
        using coord_t = long long;
        using sz_t = unsigned long long;

        #pragma pack(push, 1)
        struct rgb_struct_t{ uint8_t r, g, b, alpha; };
        union  rgb_t{
            uint32_t rgba_n;  rgb_struct_t rgba_s; 
            operator uint32_t() const {  return rgba_n; } 
        };
        #pragma pack(pop)

        virtual ~IShape() = default;
        virtual void draw(display_ptr_t display) const = 0; 
        virtual sz_t area() const = 0; 
        virtual rgb_t color() const = 0; 
        virtual IShape& color(rgb_t clr) = 0;
        virtual sz_t line_width() const = 0; 
        virtual IShape& line_width(sz_t w) = 0; 
    };
    
    struct IDocView : public IObserver
    {
        virtual ~IDocView() = default;
        virtual void set_doc(doc_wptr_t p_doc) = 0;
    };

    struct IDisplay 
    {
        using coord_t = IShape::coord_t;
        using sz_t    = IShape::sz_t;
        using rgb_t   = IShape::rgb_t;

        virtual ~IDisplay() = default;
        virtual IDisplay& point(coord_t x, coord_t y) = 0;
        virtual IDisplay& move_to(coord_t x, coord_t y) = 0;
        virtual IDisplay& line_to(coord_t x, coord_t y) = 0;
        virtual IDisplay& line(coord_t x0, coord_t y0, coord_t x1, coord_t y1) = 0;
        virtual IDisplay& rect(coord_t x, coord_t y, sz_t w, sz_t h) = 0;
        virtual IDisplay& rect(coord_t xLT, coord_t yLT, coord_t xRB, coord_t yRB) = 0;
        virtual IDisplay& circle(coord_t x, coord_t y, sz_t radius) = 0;
        virtual IDisplay& color(const rgb_t clr) = 0;
        virtual IDisplay& line_width(const sz_t w) = 0;
    };

    struct IDocStorage
    {
        virtual ~IDocStorage() = default;

        virtual void read_doc(doc_ptr_t doc) = 0;
        virtual void write_doc(doc_ptr_t doc) = 0;
    };

    struct IConfig
    {
        virtual ~IConfig() = default;
    };

    /// @brief глобальный доступ к синглтону конфигурации 
    /// @return ссылку на объект конфигурации
    IConfig&    the_config();


    /// @brief глобальный доступ к синглтону редактора 
    /// @return ссылку на объект редактора
    IEditor&    the_editor();

} // otus_hw5

