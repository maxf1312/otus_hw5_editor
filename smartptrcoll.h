#pragma once
/**
 * @file smartptrcoll.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <vector>
#include <algorithm>

namespace otus_hw5{

    /// @brief Шаблон для коллекции умных указателей. Для удобства реализации коллекций внутри объектов 
    /// @tparam SmartPtrT - тип указателя 
    template<typename SmartPtrT>
    class SmartPtrCollection
    {
    public:
        size_t count() const 
        {
            return pointers_.size();
        }

        SmartPtrT& at(size_t i) const
        {
            return pointers_.at(i);
        }

        SmartPtrT& add(SmartPtrT&& ptr) 
        {
            const auto p = std::find(pointers_.begin(), pointers_.end(), ptr);
            if( p != pointers_.end() )
                return *p;
            return pointers_.emplace_back(std::move(ptr));
        }

        void remove(const SmartPtrT& ptr) 
        {
            const auto p = std::remove(pointers_.begin(), pointers_.end(), ptr);
            if( p == pointers_.end() )
                return;
            pointers_.pop_back();
        }

        void remove(size_t i) 
        {
            const auto& ptr = at(i);
            remove(ptr);
        }

        void remove_all() 
        {
            for(size_t i = pointers_.size(); i-- > 0 ;)
                remove(i);
        }

    private:
        using coll_t = std::vector<SmartPtrT>;            
        mutable coll_t pointers_;             
    };
} // otus_hw5

