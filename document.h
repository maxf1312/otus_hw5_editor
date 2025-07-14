#pragma once

#include <vector>
#include "editor.h"
#include "observer.h"


namespace otus_hw5
{

    class Document : public IDocument, public Subject
    {
    public:
        virtual ~Document() override;
        virtual void add_shape(shape_ptr_t shp) override;
        virtual void remove_shape(shape_ptr_t shp) override;
    
    protected:
        using shape_cont_t = std::vector<shape_ptr_t>;

        shape_cont_t shapes_;
    };

};