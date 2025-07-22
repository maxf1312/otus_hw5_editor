#pragma once
/**
 * @file editor.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Описание всех интерфейсов
 * @version 0.1
 * @date 2025-04-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <ios>
#include <memory>
#include <string>
#include "smartptrcoll.h"

namespace otus_hw5{
    struct IEditor;
    struct IObserver;
    struct ISubject;
    struct IDocument;
    struct IDocSerializer;
    struct ISerializable;
    struct IDocStorage;
    struct IShape;
    struct IDisplay;
    struct IDocView;
    struct IConfig;
    struct ICommand;
    struct ICommandHandler;

    /// @brief Делетер для сериализатора - т.к. сериализатор неполный тип, делетер только объявлен 
    struct IDocSerializerDeleter
    {
        void operator()( IDocSerializer* p); 
    };

    /// @brief Делетер для обработчика команд - т.к. это неполный тип, делетер только объявлен 
    struct ICommandHandlerDeleter
    {
        void operator()( ICommandHandler* p); 
    };

    using editor_ptr_t = std::unique_ptr<IEditor>;
    using doc_ptr_t = std::shared_ptr<IDocument>;
    using doc_wptr_t = std::weak_ptr<IDocument>;
    using config_ptr_t = std::unique_ptr<IConfig>;
    using docstg_ptr_t = std::shared_ptr<IDocStorage>;
    using docser_ptr_t = std::unique_ptr<IDocSerializer, IDocSerializerDeleter>;
    using shape_ptr_t = std::unique_ptr<IShape>;
    using view_ptr_t = std::shared_ptr<IDocView>;
    using display_ptr_t = std::shared_ptr<IDisplay>;
    using observer_ptr_t = std::shared_ptr<IObserver>;
    using subject_ptr_t = std::shared_ptr<ISubject>;
    using subject_wptr_t = std::weak_ptr<ISubject>;
    using command_ptr_t = std::shared_ptr<ICommand>;
    using cmdhandler_ptr_t = std::shared_ptr<ICommandHandler>;

    using doc_ptr_coll_t = SmartPtrCollection<doc_ptr_t>;
    using view_ptr_coll_t = SmartPtrCollection<view_ptr_t>;
    using shape_ptr_coll_t = SmartPtrCollection<shape_ptr_t>;

    /// @brief Абстрактный интерфейс графического редактора, 
    /// представляет собой Контроллер MVC + вместе с IConfig глобальный контекст (Приложение)
    struct IEditor
    {
        /// @brief Типы фигур
        enum class ShapeTypes : uint8_t
        {
            Unknown,
            Point,
            Line,
            Rectangle,
            Square,
            Circle,
            Ellipse
        };  
        
        /// @brief Форматы хранения документов
        enum class DocFormatTypes : uint8_t
        {
            Text,
            JSON,
            XML
        };  

        /// @brief Типы хранилищ для документов
        enum class DocStorageTypes : uint8_t
        {
            Console,
            File,
            Socket,
            S3Object,
            NoSQL
        };
        
        using DocStgMode_t = std::ios_base::openmode;
        using IOBase_t = std::ios_base;

        virtual ~IEditor() = default;
        virtual doc_ptr_t& create_new_doc(IConfig const& cfg) = 0;
        virtual doc_ptr_coll_t& docs() = 0;

        virtual void import_doc_from(doc_ptr_t& doc, docstg_ptr_t const& stg, docser_ptr_t const& serializer) = 0;
        virtual void export_doc_to(doc_ptr_t const& doc, docstg_ptr_t& stg, docser_ptr_t const& serializer) = 0;

        virtual shape_ptr_t create_shape(ShapeTypes shape_type) = 0;

        virtual view_ptr_t& create_new_view(IConfig const& cfg) = 0;
        virtual view_ptr_coll_t& views() = 0;

        virtual display_ptr_t display() const = 0;
        virtual docstg_ptr_t create_docstg(DocStorageTypes stg_type,
                                           DocStgMode_t mode = IOBase_t::in|IOBase_t::out|IOBase_t::binary,
                                           std::string const& stg_name_or_address = "") = 0;
        virtual docser_ptr_t create_docserializer(DocFormatTypes fmt_type) = 0;

        virtual bool execute_cmd(command_ptr_t const& cmd) = 0;
    };

    /// @brief Интерфейс наблюдаемого объекта в паттерне Наблюдатель
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
    
    /// @brief Интерфейс Наблюдателя в паттерне Наблюдатель
    struct IObserver : public std::enable_shared_from_this<IObserver>
    {
        virtual ~IObserver() = default;
        virtual void subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const = 0;
    };

    /// @brief Интерфейс сериализуемого объекта
    struct ISerializable 
    {
        virtual ~ISerializable() = default;
        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) = 0;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) = 0;
    };

    /// @brief Интерфейс Документа
    struct IDocument  
    {
        virtual ~IDocument() = default;
        virtual void import_from(docstg_ptr_t const& stg, docser_ptr_t const& serializer) = 0;
        virtual void export_to(docstg_ptr_t& stg, docser_ptr_t const& serializer) = 0;
        virtual shape_ptr_t& add_shape(shape_ptr_t&& shp) = 0;
        virtual void remove_shape(shape_ptr_t const& shp) = 0;
        virtual shape_ptr_coll_t& shapes() = 0;        
        virtual void add_view(view_ptr_t v) = 0;
        virtual void remove_view(view_ptr_t v) = 0;
        virtual ISubject& as_subject() = 0;
        virtual ISerializable& as_serializable() = 0; 
    };
    
    /// @brief Интерфейс объекта Фигура
    struct IShape : public ISerializable 
    {
        using coord_t = long long;
        using sz_t = unsigned long long;
        using ShapeTypes = IEditor::ShapeTypes;
        #pragma pack(push, 1)
        struct rgb_struct_t{ uint8_t r, g, b, alpha; };
        union  rgb_t{
            uint32_t rgba_n;  rgb_struct_t rgba_s;
            rgb_t(uint32_t n = 0) : rgba_n{n} {} 
            operator uint32_t() const {  return rgba_n; } 
        };
        struct point_t{
            coord_t x, y;
        };
        #pragma pack(pop)

        virtual ~IShape() = default;
        virtual ShapeTypes type() const = 0;
        virtual void draw(display_ptr_t display) const = 0; 
        virtual sz_t area() const = 0; 
        virtual rgb_t color() const = 0; 
        virtual IShape& color(rgb_t clr) = 0;
        virtual sz_t line_width() const = 0; 
        virtual IShape& line_width(sz_t w) = 0;
        virtual point_t center() const = 0;  
        virtual IShape& center(point_t const& pt) = 0;  
        virtual IShape& center(coord_t const x, coord_t const y) = 0;  
    };
    
    /// @brief Интерфейс объекта Представление документа (Документ:Представление = N:1)
    struct IDocView : public IObserver
    {
        virtual ~IDocView() = default;
        virtual void set_doc(doc_wptr_t p_doc) = 0;
    };

    /// @brief Интерфейс объекта дисплей, ответственен за отрисовку элементов
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

    /// @brief Интерфейс объекта Хранилище документов, по сути предоставляет унифицированный интерфейс к STL-потоку.
    struct IDocStorage
    {
        using DocStgMode_t = IEditor::DocStgMode_t;
        using DocStorageTypes = IEditor::DocStorageTypes;
        using IOBase_t = IEditor::IOBase_t;

        virtual ~IDocStorage() noexcept = default;
        virtual DocStorageTypes type() const = 0;
        virtual DocStgMode_t    input_mode() const = 0;
        virtual DocStgMode_t    output_mode() const = 0;
        virtual void read_doc(doc_ptr_t doc) = 0;
        virtual void write_doc(doc_ptr_t doc) = 0;
        virtual std::ostream& outputstream() = 0;
        virtual std::istream& inputstream()  = 0;
    };

    /// @brief Интерфейс команды
    struct ICommand 
    {
        virtual ~ICommand() = default;
        virtual void execute(cmdhandler_ptr_t const& handler) = 0;
    };

    /// @brief Интерфейс объекта Конфигурация. При необходимости содержит поля данных. 
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

