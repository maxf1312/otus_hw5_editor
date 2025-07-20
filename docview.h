#pragma once
/**
 * @file docview.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Представление документа базовое 
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <vector>
#include "editor.h"

namespace otus_hw5
{

    class DocView : public IDocView
    {
    public:
                DocView(display_ptr_t display) : display_(display) {}
        virtual ~DocView() override;
        virtual void subject_changed(subject_wptr_t p_subject, ISubject::Events event_code) const override;
        virtual void set_doc(doc_wptr_t p_doc) override;
    protected:
        /// @brief Представляемый документ (слабая ссылка)
        doc_wptr_t doc_;

        /// @brief Указатель на дисплей для вывода
        display_ptr_t display_;
    };

};