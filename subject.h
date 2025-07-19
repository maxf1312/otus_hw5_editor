#pragma once

#include "editor.h"

namespace otus_hw5
{
    template <typename SubjectImplT>
    class Subject : public ISubject
    {
    public:
        Subject(SubjectImplT &outer) : outer_impl_(&outer) {}
        virtual ~Subject() noexcept;
        virtual void subscribe(observer_ptr_t observer) override;
        virtual void unsubscribe(observer_ptr_t observer) override;
        virtual void set_changed(bool was_changed) override;
        virtual void notify_all() override;

    protected:
        Subject() : outer_impl_(nullptr) {}

        template <typename SubjectImplTR = SubjectImplT>
        auto impl_this_ptr() -> std::enable_if_t<std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR *>
        {
            return outer_impl_ ? outer_impl_ : static_cast<SubjectImplT *>(this);
        }

        template <typename SubjectImplTR = SubjectImplT>
        auto impl_this_ptr() -> std::enable_if_t<!std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR *>
        {
            return outer_impl_;
        }

        template <typename SubjectImplTR = SubjectImplT>
        auto impl_this_ptr() const -> std::enable_if_t<std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR const *>
        {
            return outer_impl_ ? outer_impl_ : static_cast<SubjectImplT const *>(this);
        }

        template <typename SubjectImplTR = SubjectImplT>
        auto impl_this_ptr() const -> std::enable_if_t<!std::is_base_of<Subject<SubjectImplT>, SubjectImplTR>::value, SubjectImplTR const *>
        {
            return outer_impl_;
        }

    private:
        using observer_cont_t = SmartPtrCollection<observer_ptr_t>;
        observer_cont_t observers_;
        Events evt_;
        SubjectImplT *outer_impl_;
    };

    template <typename SubjectImplT>
    Subject<SubjectImplT>::~Subject() noexcept
    {
        evt_ = Events::kDestroing;
        notify_all();
    }

    template <typename SubjectImplT>
    void Subject<SubjectImplT>::subscribe(observer_ptr_t observer)
    {
        observers_.add(std::move(observer));
        impl_this_ptr()->on_subscribe(observer);
    }

    template <typename SubjectImplT>
    void Subject<SubjectImplT>::unsubscribe(observer_ptr_t observer)
    {
        impl_this_ptr()->on_unsubscribe(observer);
        observers_.remove(observer);
    }

    template <typename SubjectImplT>
    void Subject<SubjectImplT>::set_changed(bool was_changed)
    {
        evt_ = was_changed ? Events::kChanged : Events::kNone;
        impl_this_ptr()->on_set_changed(was_changed);
    }

    template <typename SubjectImplT>
    void Subject<SubjectImplT>::notify_all()
    {
        // TODO сделать итератор в коллекции
        // for(const auto& observer : observers_)
        //    observer->subject_changed(weak_from_this(), evt_);
        for (size_t i = 0, N = observers_.count(); i < N; ++i)
            observers_.at(i)->subject_changed(weak_from_this(), evt_);
        impl_this_ptr()->on_notify_all();
    }
};
