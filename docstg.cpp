/**
 * @file docstg.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация хранилищ
 * @version 0.1
 * @date 2025-07-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "docstg.h"

namespace otus_hw5{
    FileDocStorage::FileDocStorage(DocStgMode_t mode, std::string const& file_nm)
    {
        filestm_.open(file_nm, mode);
        if( !filestm_ )
            throw std::runtime_error("Error opening file \'" + file_nm + "\'");

        os_ = &filestm_;
        is_ = &filestm_;
    }

} // otus_hw5

