#pragma once
/**
 * @file document.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Документ - базовая реализация   
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <vector>
#include "editor.h"
#include "subject.h"

namespace otus_hw5
{

    class Document : public IDocument, public ISerializable, public std::enable_shared_from_this<IDocument> 
    {
    public:
        Document();
        virtual ~Document() override;

        virtual void deserialize(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void serialize(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;
        virtual void import_from(docstg_ptr_t const& stg, docser_ptr_t const& serializer) override;
        virtual void export_to(docstg_ptr_t& stg, docser_ptr_t const& serializer) override;        
        virtual shape_ptr_t& add_shape(shape_ptr_t&& shp) override;
        virtual void remove_shape(shape_ptr_t const& shp) override;
        virtual shape_ptr_coll_t& shapes() override;
        virtual void add_view(view_ptr_t v) override;
        virtual void remove_view(view_ptr_t v) override;
        virtual ISubject& as_subject() override; 
        virtual ISerializable& as_serializable() override { return *this; }

        void on_subscribe(observer_ptr_t){}
        void on_unsubscribe(observer_ptr_t){}
        void on_set_changed(bool){}
        void on_notify_all(){}
    
    protected:
        using shape_cont_t = std::vector<shape_ptr_t>;
        using subject_t = Subject<Document>;
        using subject_ptr_t = std::shared_ptr<subject_t>;

        /// @brief Список фигур
        shape_ptr_coll_t shapes_;

        /// @brief Реализация Наблюдаемого объекта
        subject_ptr_t subj_impl_;
    };

}