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

namespace otus_hw5{
    struct IObserver;
    struct ISubject;
    struct IDocument;
    struct IDocStorage;
    struct IShape;
    struct IDisplay;
    struct IDocView;

    using doc_ptr_t = std::shared_ptr<IDocument>;
    using docstg_ptr_t = std::unique_ptr<IDocStorage>;
    using shape_ptr_t = std::unique_ptr<IShape>;
    using view_ptr_t = std::shared_ptr<IDocView>;
    using observer_ptr_t = std::shared_ptr<IObserver>;
    using subject_ptr_t = std::weak_ptr<ISubject>;

    struct IEditor
    {
        
        virtual ~IEditor() = default;
        virtual doc_ptr_t doc() = 0;
        virtual void create_new_doc() = 0;
        virtual void import_doc_from(docstg_ptr_t const& stg) = 0;
        virtual void export_doc_to(docstg_ptr_t& stg) = 0;
        virtual shape_ptr_t create_shape() = 0;

    };

    struct ISubject
    {
        enum class StateFlags : uint8_t
        {
            kChanged = 1,
            kDestroing = 2
        };  
        
        virtual ~ISubject() noexcept = default;
        virtual void subscribe(observer_ptr_t observer) = 0;
        virtual void unsubscribe(observer_ptr_t observer) = 0;
        virtual void set_changed(bool was_changed) = 0;
        virtual void notify_all() const = 0;
    };
    struct IObserver : public std::enable_shared_from_this<IObserver>
    {
        virtual ~IObserver() = default;
        virtual void subject_changed(uint8_t what_flags) const = 0;
    };

    struct IDocument 
    {
        virtual ~IDocument() = default;
        virtual void add_shape(shape_ptr_t shp) = 0;
        virtual void remove_shape(shape_ptr_t shp) = 0;
    };
    
    struct IShape
    {
        virtual ~IShape() = default;
    };
    
    struct IDocView
    {
        virtual ~IDocView() = default;
    };
} // otus_hw5

