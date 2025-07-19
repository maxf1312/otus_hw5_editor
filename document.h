#pragma once

#include <vector>
#include "editor.h"
#include "subject.h"


namespace otus_hw5
{

    class Document : public IDocument, public std::enable_shared_from_this<IDocument> 
    {
    public:
        Document();
        virtual ~Document() override;

        virtual void import_from(docstg_ptr_t const stg) override;
        virtual void export_to(docstg_ptr_t stg) override;        
        virtual void add_shape(shape_ptr_t&& shp) override;
        virtual void remove_shape(shape_ptr_t const& shp) override;
        virtual shape_ptr_coll_t& shapes() override;
        virtual void add_view(view_ptr_t v) override;
        virtual void remove_view(view_ptr_t v) override;
        virtual ISubject& as_subject() override; 

        void on_subscribe(observer_ptr_t){}
        void on_unsubscribe(observer_ptr_t){}
        void on_set_changed(bool){}
        void on_notify_all(){}
    
    protected:
        using shape_cont_t = std::vector<shape_ptr_t>;
        using subject_t = Subject<Document>;
        using subject_ptr_t = std::shared_ptr<subject_t>;

        shape_ptr_coll_t shapes_;
        subject_ptr_t subj_impl_;
    };

};