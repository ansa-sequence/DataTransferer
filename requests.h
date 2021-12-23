//
// Created by sakhil on 22.12.2021.
//

#ifndef DATATRANSFER_REQUESTS_H
#define DATATRANSFER_REQUESTS_H

#include <string>
#include <chrono>

#include <fmt/format.h>
#include <iomanip>

struct Requests{
    static std::string date(){
        const auto now = std::chrono::system_clock::now();
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time), "%Y-%m-%d %X");
        return ss.str();
    }
    std::string req_;
};

#endif //DATATRANSFER_REQUESTS_H
