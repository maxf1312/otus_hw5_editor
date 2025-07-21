/**
 * @file utils.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Реализация утилит
 * @version 0.1
 * @date 2025-07-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include "utils.h"

namespace otus_hw5{

    using namespace std;
    using ShpTp_t = IEditor::ShapeTypes;
    ShpTp_t shape_type_from_string(const std::string& tp)
    {
        using conv_dict_t = unordered_map<string, ShpTp_t>;
        static conv_dict_t conv_reg = {
            {"Unknown", ShpTp_t::Unknown},
            {"Point", ShpTp_t::Point}, {"Line", ShpTp_t::Line}, {"Square", ShpTp_t::Square}, {"Rectangle", ShpTp_t::Rectangle},
            {"Circle", ShpTp_t::Circle}, {"Ellipse", ShpTp_t::Ellipse}
        };
        const auto p = conv_reg.find(tp);
        return p != conv_reg.end() ? p->second : ShpTp_t::Unknown;
    }   

    const std::string   shape_type_to_string(const ShpTp_t tp)
    {
        using conv_dict_t = unordered_map<ShpTp_t, const char*>;
        static conv_dict_t conv_reg = {
            {ShpTp_t::Unknown, "Unknown"},
            {ShpTp_t::Point, "Point"}, {ShpTp_t::Line, "Line"}, {ShpTp_t::Square, "Square"}, {ShpTp_t::Rectangle, "Rectangle"},
            {ShpTp_t::Circle, "Circle"}, {ShpTp_t::Ellipse, "Ellipse"}
        };
        const auto p = conv_reg.find(tp);
        return p != conv_reg.end() ? p->second : "Unknown";
    }

    void print_prompt(std::ostream& os)
    {
        os << "Введите команду:" << endl
           << '\t' << "N - новый документ" << endl
           << '\t' << "R - загрузить документ" << endl
           << '\t' << "S - сохранить документ" << endl
           << '\t' << "A - добавить фигуру в документ" << endl
           << '\t' << "D - удалить фигуру из документа" << endl
           << '\t' << "M - передвинуть фигуру" << endl
           << '\t' << "Q - Выход" << endl
        ;
    }

} // otus_hw5

