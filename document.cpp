#include <vector>
#include <algorithm>
#include "editor.h"
#include "document.h"


namespace otus_hw5
{

Document::~Document()
{}

void Document::add_shape(shape_ptr_t shp)
{
    using namespace std;
    if( find(begin(shapes_), end(shapes_), shp) != end(shapes_) )
        return;
    shapes_.emplace_back(std::move(shp));    
}

void Document::remove_shape(shape_ptr_t shp)
{
    using namespace std;
    auto p = remove(begin(shapes_), end(shapes_), shp);
    if( p == end(shapes_) )
        return;
    shapes_.erase(p, end(shapes_));
}


};