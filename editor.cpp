/**
 * @file editor.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация простого редактора
 * @version 0.1
 * @date 2025-07-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <cassert> 
#include "editor.h" 
#include "document.h" 
#include "docview.h" 
#include "display.h"
#include "shape.h"
#include "docstg.h"
#include "docserializer.h"


namespace otus_hw5{

    void IDocSerializerDeleter::operator()(IDocSerializer* p)
    {
        delete p;
    } 
    

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

        virtual void import_doc_from(doc_ptr_t& doc, docstg_ptr_t const& stg, docser_ptr_t const& serializer) override 
        {
            doc->as_serializable().deserialize(stg, serializer);
        }
        
        virtual void export_doc_to(doc_ptr_t const& doc, docstg_ptr_t& stg, docser_ptr_t const& serializer) override
        {
            doc->as_serializable().serialize(stg, serializer);
        }

        virtual shape_ptr_t create_shape(ShapeTypes shape_type) override
        {
            return shape_creator_->create_shape(shape_type) ;
        }
        
        virtual view_ptr_t& create_new_view(IConfig const&) override 
        {
            auto p = std::make_shared<DocView>(display());
            return views_.add(p);
        }
        virtual view_ptr_coll_t& views() override
        {
            return views_;
        }

        virtual display_ptr_t display() const override
        {
            if( !display_ )
                display_ = std::make_shared<OStreamDisplay>(std::cout);
            return display_;
        }

        virtual docstg_ptr_t create_docstg(DocStorageTypes stg_type, DocStgMode_t mode, std::string const& stg_name_or_address) override
        {
            docstg_ptr_t p_stg; 
            switch (stg_type)
            {
            default:
                assert( (void("Not supported doc storage type"), false) );
                break;

            case IEditor::DocStorageTypes::Console:
                p_stg = std::make_shared<StreamDocStorage>();                
                break;
            
            case IEditor::DocStorageTypes::File:
                p_stg = std::make_shared<FileDocStorage>(mode, stg_name_or_address);                
                break;
            }
            return p_stg;
        }

        virtual docser_ptr_t create_docserializer(DocFormatTypes fmt_type) override 
        {
            std::ignore = fmt_type;
            docser_ptr_t p_ser;
            switch(fmt_type)
            {
            default:
                assert( (void("Not supported doc format"), false) );

                break;
            case IEditor::DocFormatTypes::Text: 
                p_ser.reset( new DocSerializerText() );
                break;
            }
            return p_ser;
        }

        virtual bool execute_cmd(command_ptr_t const& cmd) override
        {
            std::ignore = cmd;
            return true;
        }


        static IEditor& Instance()
        {
            //static SimpleEditor  editor(the_config());
            static SimpleEditor* editor = new SimpleEditor(the_config());
            return *editor;
        }

    private:
        SimpleEditor(IConfig const& cfg) : shape_creator_(get_shape_creator(cfg))
        {

        }

        SmartPtrCollection<doc_ptr_t> docs_;
        SmartPtrCollection<view_ptr_t> views_;
        mutable display_ptr_t   display_;
        shape_creator_ptr_t shape_creator_;
    };

    /// @brief глобальный доступ к синглтону редактора 
    /// @return ссылку на объект редактора
    IEditor&    the_editor()
    {
        return SimpleEditor::Instance();
    }

} // otus_hw5

