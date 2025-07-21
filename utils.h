#pragma once
/**
 * @file utils.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief утилиты
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "editor.h"

namespace otus_hw5{
    
    IEditor::ShapeTypes shape_type_from_string(const std::string& tp);
    const std::string   shape_type_to_string(const IEditor::ShapeTypes tp);
    void print_prompt(std::ostream& os);

} // otus_hw5
