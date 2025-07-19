#pragma once

#include <vector>
#include "editor.h"
#include "subject.h"


namespace otus_hw5
{

    class Document : public IDocument
    {
    public:
        Document();
        virtual ~Document() override;

        virtual void subscribe(observer_ptr_t observer) override;
        virtual void unsubscribe(observer_ptr_t observer) override;
        virtual void set_changed(bool was_changed) override;
        virtual void notify_all() override;

        virtual void import_from(docstg_ptr_t const stg) override;
        virtual void export_to(docstg_ptr_t stg) override;        
        virtual void add_shape(shape_ptr_t shp) override;
        virtual void remove_shape(shape_ptr_t shp) override;
        virtual shape_ptr_coll_t& shapes() override;
        virtual void add_view(view_ptr_t v) override;
        virtual void remove_view(view_ptr_t v) override;
 

        void on_subscribe(observer_ptr_t ){}
        void on_unsubscribe(observer_ptr_t ){}
        void on_set_changed(bool ){}
        void on_notify_all(){}
    
    protected:
        using shape_cont_t = std::vector<shape_ptr_t>;
        using subject_t = Subject<Document>;
        using subject_ptr_t = std::unique_ptr<subject_t>;

        shape_ptr_coll_t shapes_;
        subject_ptr_t subj_impl_;
    };

};