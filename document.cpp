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
    using namespace std;
    if( find(begin(shapes_), end(shapes_), shp) != end(shapes_) )
        return;
    shapes_.emplace_back(std::move(shp));
    set_changed(true);
    notify_all();
}

void Document::remove_shape(shape_ptr_t shp)
{
    using namespace std;
    auto p = remove(begin(shapes_), end(shapes_), shp);
    if( p == end(shapes_) )
        return;
    shapes_.erase(p, end(shapes_));
    set_changed(true);    
    notify_all();
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