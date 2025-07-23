/**
 * @file config.cpp
 * @author MaximF (maxf1312@yandex.ru)
 * @brief Класс конфигурации приложения
 * @version 0.1
 * @date 2025-07-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "editor.h" 

namespace otus_hw5{

    /// @brief Конфигурация приложения
    class Config : public IConfig
    {
    public:
        static Config& Instance()
        {
            static Config cfg;
            return cfg;
        }
    private:
        Config(){}        
    };

    /// @brief глобальный доступ к синглтону конфигурации 
    /// @return ссылку на объект конфигурации
    IConfig&    the_config()
    {
        return Config::Instance();
    }

} // otus_hw5

