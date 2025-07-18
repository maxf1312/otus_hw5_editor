#include <iostream>
#include <vector>
#include <algorithm>
#include "docview.h"


namespace otus_hw5
{

    void DocView::subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const
    {
        std::ignore = p_subject;
        std::ignore = event_code;
        std::cout << "subject_changed " << p_subject.lock().get() << " " << static_cast<uint32_t>(event_code) <<  std::endl;
    }

};