/**
 * @file editor.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2025-07-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "editor.h" 
#include "document.h" 
#include "docview.h" 
#include "smartptrcoll.h"

namespace otus_hw5{

    /// @brief Реализация редактора.
    class SimpleEditor : public IEditor
    {
    public:        
        virtual ~SimpleEditor() = default;
        virtual doc_ptr_t& create_new_doc(IConfig const& ) override 
        {
            auto p = std::make_shared<Document>(); 
            return docs_.add(p); 
        }

        virtual doc_ptr_coll_t& docs() override
        {
            return docs_;
        }

        virtual doc_ptr_t import_doc_from(docstg_ptr_t const& stg) override 
        {
            std::ignore = stg;
            return doc_ptr_t{};
        }
        
        virtual void export_doc_to(doc_ptr_t const& doc, docstg_ptr_t& stg) override
        {
            std::ignore = stg;
            std::ignore = doc;
        }

        virtual shape_ptr_t create_shape(ShapeTypes shape_type) override
        {
            std::ignore = shape_type;
            return shape_ptr_t{};
        }
        
        virtual view_ptr_t& create_new_view(IConfig const&) override 
        {
            auto p = std::make_shared<DocView>();
            return views_.add(p);
        }
        virtual view_ptr_coll_t& views() override
        {
            return views_;
        }

        virtual display_ptr_t display() const override
        {
            return display_ptr_t{};
        }

        static IEditor& Instance()
        {
            static SimpleEditor editor(the_config());
            return editor;
        }


    private:
        SimpleEditor(IConfig const& )
        {

        }

        SmartPtrCollection<doc_ptr_t> docs_;
        SmartPtrCollection<view_ptr_t> views_;
    };

    /// @brief глобальный доступ к синглтону редактора 
    /// @return ссылку на объект редактора
    IEditor&    the_editor()
    {
        return SimpleEditor::Instance();
    }

} // otus_hw5

