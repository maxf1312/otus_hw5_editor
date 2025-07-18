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

#include <vector>
#include <algorithm>
#include "editor.h" 
#include "document.h" 
#include "docview.h" 

namespace otus_hw5{

    template<typename InterfacePtrT>
    class InterfacePtrCollection
    {
    public:
        size_t count() const 
        {
            return pointers_.size();
        }

        InterfacePtrT at(size_t i) const
        {
            return pointers_.at(i);
        }

        void add(const InterfacePtrT& ptr) 
        {
            const auto p = std::find(pointers_.begin(), pointers_.end(), ptr);
            if( p != pointers_.end() )
                return;
            pointers_.emplace_back(ptr);
        }

        void remove(const InterfacePtrT& ptr) 
        {
            const auto p = std::remove(pointers_.begin(), pointers_.end(), ptr);
            if( p == pointers_.end() )
                return;
            pointers_.pop_back();
        }

        void remove(size_t i) 
        {
            const auto ptr = at(i);
            remove(ptr);
        }

    private:
        using coll_t = std::vector<InterfacePtrT>;            
        coll_t pointers_;             
    };


    /// @brief Реализация редактора.
    class SimpleEditor : public IEditor
    {
    public:        
        virtual ~SimpleEditor() = default;
        virtual size_t doc_count() const override { return docs_.count(); } 
        virtual doc_ptr_t doc_at(size_t i) const override { return docs_.at(i);}
        virtual doc_ptr_t create_new_doc(IConfig const& ) override 
        {
            auto p = std::make_shared<Document>(); docs_.add(p);
            return p; 
        }
        virtual void del_doc_at(size_t i) override
        {
            docs_.remove(i);
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
        
        virtual size_t view_count() const override { return views_.count(); }
        virtual view_ptr_t view_at(size_t i) const override { return views_.at(i); }
        virtual view_ptr_t create_new_view(IConfig const&) override 
        {
            auto p = std::make_shared<DocView>(); views_.add(p);
            return p; 
        }
        virtual void del_view_at(size_t i) override
        {
            views_.remove(i);
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

        InterfacePtrCollection<doc_ptr_t> docs_;
        InterfacePtrCollection<view_ptr_t> views_;
    };

    /// @brief глобальный доступ к синглтону редактора 
    /// @return ссылку на объект редактора
    IEditor&    the_editor()
    {
        return SimpleEditor::Instance();
    }

} // otus_hw5

