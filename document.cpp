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

void Document::subscribe(observer_ptr_t observer)
{
    subj_impl_->subscribe(observer);
}

void Document::unsubscribe(observer_ptr_t observer)
{
    subj_impl_->unsubscribe(observer);
}

void Document::set_changed(bool was_changed)
{
    subj_impl_->set_changed(was_changed);
}

void Document::notify_all()
{
    subj_impl_->notify_all();
}

void Document::add_shape(shape_ptr_t shp)
{
    shapes_.add(std::move(shp));
    set_changed(true);
    notify_all();
}

void Document::remove_shape(shape_ptr_t shp)
{
    shapes_.remove(shp);
    set_changed(true);    
    notify_all();
}

shape_ptr_coll_t& Document::shapes()
{
    return shapes_;    
}

void Document::add_view(view_ptr_t v)
{
    subscribe(v);
}

void Document::remove_view(view_ptr_t v)
{
    unsubscribe(v);
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