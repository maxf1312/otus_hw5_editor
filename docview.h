#pragma once

#include <vector>
#include "editor.h"

namespace otus_hw5
{

    class DocView : public IDocView
    {
    public:
                DocView(display_ptr_t display) : display_(display) {}
        virtual ~DocView() override;
        virtual void subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const override;
        virtual void set_doc(doc_wptr_t p_doc) override;
    protected:
        doc_wptr_t doc_;
        display_ptr_t display_;
    };

};