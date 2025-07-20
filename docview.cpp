/**
 * @file docview.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Представление документа базовое 
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "docview.h"


namespace otus_hw5
{

    void DocView::set_doc(doc_wptr_t p_doc)
    {
        doc_ = p_doc;
    }

    DocView::~DocView()
    {

    }

    void DocView::subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const
    {
        std::ignore = p_subject;
        std::ignore = event_code;
        auto sp = p_subject.lock();
        std::cout << "subject_changed " << sp.get() << " " << static_cast<uint32_t>(event_code) <<  std::endl;
        if( event_code != ISubject::Events::kChanged )
            return;

        auto sp_d = doc_.lock();
        if( !sp || !sp_d )
            return;
        
        for(size_t i = 0, N = sp_d->shapes().count(); i < N; ++i)
            sp_d->shapes().at(i)->draw(display_);
    }

};