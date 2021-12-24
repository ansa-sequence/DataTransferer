//
// Created by sakhil on 24.12.2021.
//

#ifndef DATATRANSFER_JSON_CONVERTER_HPP
#define DATATRANSFER_JSON_CONVERTER_HPP

/**
 * @note STL including
 */
#include <string>
#include <variant>
#include <utility>
#include <any>

/**
 * @note Header including
 */

#include "data.hpp"
#include "json.hpp"


namespace interface{

    struct parser
    {
        template <typename Field>
        static decltype(auto) get_field(const nlohmann::json& json_) {
            using field_type= std::decay_t<Field>;
            if constexpr(std::is_same_v<field_type, details::Date>) {
               return details::Date
                        {
                                std::to_string(json_["dt"].get<int>()),
                                std::to_string(json_["sys"]["sunrise"].get<int>()),
                                std::to_string(json_["sys"]["sunset"].get<int>()),
                        };
            } else if constexpr(std::is_same_v<field_type, details::Temperature>) {
                    return details::Temperature{
                        std::to_string(json_["main"]["feels_like"].get<int>()),
                        std::to_string(json_["main"]["temp"].get<int>()),
                        std::to_string(json_["main"]["temp_max"].get<int>()),
                        std::to_string(json_["main"]["temp_min"].get<int>()),
                    };
            } else
                static_assert("ff");
        }
    };

}

#endif //DATATRANSFER_JSON_CONVERTER_HPP
