#pragma once
/**
 * @file docstg.h
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Хранилища для документов
 * @version 0.1
 * @date 2025-07-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <fstream>
#include "editor.h"

namespace otus_hw5{
    /// @brief Объект Хранилище документов для STL-потоков, хранит ссылки на потоки.
    class  StreamDocStorage : public IDocStorage
    {
    public:
        StreamDocStorage() : os_(&std::cout), is_(&std::cin) { }
        StreamDocStorage(std::ostream& os, std::istream& is) : os_(&os), is_(&is) { }
        virtual ~StreamDocStorage() noexcept = default;
        virtual IEditor::DocStorageTypes type() const override
        {
            return DocStorageTypes::Console; 
        }

        virtual DocStgMode_t    input_mode() const override
        {
            return IOBase_t::in;
        }

        virtual DocStgMode_t    output_mode() const override
        {
            return IOBase_t::out|IOBase_t::app;
        }

        virtual void read_doc(doc_ptr_t) override
        {
        }

        virtual void write_doc(doc_ptr_t) override
        {
        }

        virtual std::ostream& outputstream() override
        {
            return *os_;
        }

        virtual std::istream& inputstream()  override
        {
            return *is_;
        }
    protected:
        std::ostream* os_;
        std::istream* is_;        
    };

    /// @brief Объект Хранилище документов для STL-файла.
    class  FileDocStorage : public StreamDocStorage
    {
    public:
        FileDocStorage() : mode_(IOBase_t::in|IOBase_t::out|IOBase_t::binary) { }
        FileDocStorage(DocStgMode_t mode, std::string const& file_nm);
        virtual ~FileDocStorage() noexcept = default;
        virtual DocStorageTypes type() const override
        {
            return DocStorageTypes::File; 
        }

        virtual DocStgMode_t    input_mode() const override
        {
            return mode_;
        }

        virtual DocStgMode_t    output_mode() const override
        {
            return mode_;
        }
    protected:
        std::fstream filestm_;
        DocStgMode_t mode_;
    };

} // otus_hw5

