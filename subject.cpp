#include <algorithm>

#include "subject.h"

namespace otus_hw5
{

template<typename SubjectImplT>
Subject<SubjectImplT>::~Subject() noexcept
{
    evt_ = Events::kDestroing;
    notify_all();    
}

template<typename SubjectImplT>
void Subject<SubjectImplT>::subscribe(observer_ptr_t observer)
{
    const auto p = std::find(observers_.begin(), observers_.end(), observer);
    if( p != observers_.end() )
        return;
    observers_.emplace_back(observer);
    impl_this_ptr()->on_subscribe(observer);
}

template<typename SubjectImplT>
void Subject<SubjectImplT>::unsubscribe(observer_ptr_t observer)
{
    impl_this_ptr()->on_unsubscribe(observer);
    const auto p = std::remove(observers_.begin(), observers_.end(), observer);
    if( p == observers_.end() )
        return;
    observers_.pop_back();
}

template<typename SubjectImplT>
void Subject<SubjectImplT>::set_changed(bool was_changed)
{
    evt_ = was_changed ? Events::kChanged : Events::kNone;
    impl_this_ptr()->on_set_changed(was_changed);
}

template<typename SubjectImplT>
void Subject<SubjectImplT>::notify_all() 
{
    for(const auto& observer : observers_)
        observer->subject_changed(weak_from_this(), evt_);
    impl_this_ptr()->on_notify_all();
}
};