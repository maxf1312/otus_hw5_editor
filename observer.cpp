#include <algorithm>

#include "observer.h"

namespace otus_hw5
{

Subject::~Subject() noexcept
{
}

void Subject::subscribe(observer_ptr_t observer)
{
    const auto p = std::find(observers_.begin(), observers_.end(), observer);
    if( p != observers_.end() )
        return;
    observers_.emplace_back(observer);
}

void Subject::unsubscribe(observer_ptr_t observer)
{
    const auto p = std::remove(observers_.begin(), observers_.end(), observer);
    if( p == observers_.end() )
        return;
    observers_.pop_back();
}

void Subject::set_changed(bool was_changed)
{
    if( was_changed )
        what_ |= static_cast<decltype(what_)>(StateFlags::kChanged);
    else
        what_ &= ~static_cast<decltype(what_)>(StateFlags::kChanged);
}

void Subject::notify_all() const
{
    for(const auto& observer : observers_)
        observer->subject_changed(what_);
}


};