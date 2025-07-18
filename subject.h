#pragma once

#include <vector>
#include "editor.h"

namespace otus_hw5 
{
    template<typename SubjectImplT>
    class Subject : public ISubject
    {
    public:
        Subject(SubjectImplT& outer) : outer_impl_(&outer) {}
        virtual ~Subject() noexcept;
        virtual void subscribe(observer_ptr_t observer) override;
        virtual void unsubscribe(observer_ptr_t observer) override;
        virtual void set_changed(bool was_changed) override;
        virtual void notify_all() override;

    protected:
        Subject() : outer_impl_(nullptr) {}

        template<typename SubjectImplTR = SubjectImplT >
        auto   impl_this_ptr() -> std::enable_if_t<std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR*>
        {
            return outer_impl_ ? outer_impl_ : static_cast<SubjectImplT*>(this);   
        }

        template<typename SubjectImplTR = SubjectImplT >
        auto   impl_this_ptr() -> std::enable_if_t<!std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR*>
        {
            return outer_impl_;   
        }

        template<typename SubjectImplTR = SubjectImplT >
        auto   impl_this_ptr() const -> std::enable_if_t<std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR const*>
        {
            return outer_impl_ ? outer_impl_ : static_cast<SubjectImplT const*>(this);    
        }

        template<typename SubjectImplTR = SubjectImplT >
        auto   impl_this_ptr() const -> std::enable_if_t<!std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR const*>
        {
            return outer_impl_;    
        }
    private:
        using observer_cont_t = std::vector<observer_ptr_t>;

        observer_cont_t observers_;
        Events evt_;
        SubjectImplT* outer_impl_;
    };

};

#include "subject.cpp"