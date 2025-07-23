/**
 * @file document.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Документ - реализация  
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <vector>
#include <algorithm>
#include "editor.h"
#include "document.h"
#include "docserializer.h"


namespace otus_hw5
{

Document::Document() : subj_impl_{new subject_t(*this)}
{
    
}

Document::~Document()
{
}

ISubject& Document::as_subject()
{
    return *subj_impl_;
} 

shape_ptr_t& Document::add_shape(shape_ptr_t&& shp)
{
    auto& rp_shp = shapes_.add(std::move(shp));
    as_subject().set_changed(true);
    as_subject().notify_all();
    return rp_shp;
}

void Document::remove_shape(shape_ptr_t const& shp)
{
    shapes_.remove(shp);
    as_subject().set_changed(true);    
    as_subject().notify_all();
}

shape_ptr_coll_t& Document::shapes()
{
    return shapes_;    
}

void Document::add_view(view_ptr_t v)
{
    v->set_doc( this->weak_from_this() );
    as_subject().subscribe(v);
}

void Document::remove_view(view_ptr_t v)
{
    v->set_doc( doc_wptr_t{} );
    as_subject().unsubscribe(v);
}

void Document::import_from(docstg_ptr_t const& stg, docser_ptr_t const& serializer)
{
    deserialize(stg, serializer);
}

void Document::export_to(docstg_ptr_t& stg, docser_ptr_t const& serializer)
{
    serialize(stg, serializer);
}      

void Document::deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) 
{
    serializer->deserialize_obj(*static_cast<IDocument*>(this), stg);
}

void Document::serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) 
{
    serializer->serialize_obj(*static_cast<IDocument*>(this), stg);
}

}