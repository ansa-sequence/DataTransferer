//
// Created by sakhil on 23.12.2021.
//

#ifndef DATATRANSFER_DATA_HPP
#define DATATRANSFER_DATA_HPP

#include <string>
#include <cstdlib>
#include <utility>

namespace details{
    struct Temperature{
        Temperature(std::string feel, std::string curr, std::string max, std::string min) :
                    feels_like  {std::to_string(std::atof(feel.c_str()) - 273)},
                    temp_curr   {std::to_string(std::atof(curr.c_str()) - 273)},
                    temp_max    {std::to_string(std::atof(max.c_str()) - 273)},
                    temp_min    {std::to_string(std::atof(min.c_str()) - 273)}
        {}

        std::string feels_like {};
        std::string temp_curr  {};
        std::string temp_max   {};
        std::string temp_min   {};
    };
}

#endif //DATATRANSFER_DATA_HPP
