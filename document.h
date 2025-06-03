#pragma once

#include <vector>
#include "editor.h"
#include "observer.h"


namespace otus_hw5
{

    class Document : public IDocument, public Subject
    {
    public:
        virtual ~Document();
        virtual void add_shape(shape_ptr_t shp);
        virtual void remove_shape(shape_ptr_t shp);
    
    protected:
        using shape_cont_t = std::vector<shape_ptr_t>;

        shape_cont_t shapes_;
    };

};