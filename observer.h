#pragma once

#include <vector>
#include "editor.h"

namespace otus_hw5 
{
    class Subject : public ISubject
    {
    public:
       
        virtual ~Subject() noexcept;
        virtual void subscribe(observer_ptr_t observer) override;
        virtual void unsubscribe(observer_ptr_t observer) override;
        virtual void set_changed(bool was_changed) override;
        virtual void notify_all() const override;

    private:
        using observer_cont_t = std::vector<observer_ptr_t>;

        observer_cont_t observers_;
        uint8_t what_;
    };

};