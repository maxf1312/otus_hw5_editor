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
    struct IDocument;
    struct IDocStorage;
    struct IShape;
    
    struct IEditor
    {
        using doc_ptr_t = std::shared_ptr<IDocument>;
        using docstg_ptr_t = std::unique_ptr<IDocStorage>;
        using shape_ptr_t = std::unique_ptr<IShape>;
        
        virtual ~IEditor() = default;
        virtual doc_ptr_t doc() = 0;
        virtual void create_new_doc() = 0;
        virtual void import_doc_from(docstg_ptr_t const& stg) = 0;
        virtual void export_doc_to(docstg_ptr_t& stg) = 0;
        virtual shape_ptr_t create_shape() = 0;
        virtual void add_shape(shape_ptr_t& shp) = 0;
        virtual void remove_shape(shape_ptr_t& shp) = 0;
    };

    struct IDisplay;
    struct IDocument;
    struct IShape;
    struct IDocView;

    struct IDocument{};
    struct IShape{};
    struct IDocView{};
} // otus_hw5

