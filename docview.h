#pragma once

#include <vector>
#include "editor.h"

namespace otus_hw5
{

    class DocView : public IDocView
    {
    public:
        virtual ~DocView() = default;
        virtual void subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const;
    };

};