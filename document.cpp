#include <vector>
#include <algorithm>
#include "editor.h"
#include "document.h"


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

void Document::add_shape(shape_ptr_t&& shp)
{
    shapes_.add(std::move(shp));
    as_subject().set_changed(true);
    as_subject().notify_all();
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

void Document::import_from(docstg_ptr_t const stg)
{
    std::ignore = stg;
}

void Document::export_to(docstg_ptr_t stg)
{
    std::ignore = stg;
}      

};