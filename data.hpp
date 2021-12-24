//
// Created by sakhil on 23.12.2021.
//

#ifndef DATATRANSFER_DATA_HPP
#define DATATRANSFER_DATA_HPP

#include <string>
#include <ostream>
#include <cstdlib>
#include <utility>
#include <string_view>

#include <boost/date_time.hpp>

namespace details {

    struct Temperature {
        /**
         *
         * @param feel
         * @param curr
         * @param max
         * @param min
         */
        Temperature(const std::string &feel, const std::string &curr, const std::string &max, const std::string &min) :
                feels_like  {std::to_string(std::atoi(feel.c_str()) - 273)},
                temp_curr   {std::to_string(std::atoi(curr.c_str()) - 273)},
                temp_max    {std::to_string(std::atoi(max.c_str()) - 273)},
                temp_min    {std::to_string(std::atoi(min.c_str()) - 273)}
                {}

        friend std::ostream &operator<<(std::ostream &os, const Temperature &temp) {
            os << "Feels like : " << temp.feels_like << '\n'
               << "Current temperature : " << temp.temp_curr << '\n'
               << "Minimal temperature : " << temp.temp_min << '\n'
               << "Maximum temperature : " << temp.temp_max << '\n';
            return os;
        }

    private:
        std::string feels_like{};
        std::string temp_curr{};
        std::string temp_max{};
        std::string temp_min{};
    };
    //------------------------------------------------------------------------------------------------------------------
    struct Date{
        /**
         * @param currentDate
         * @param sunrise
         * @param sunset
         */
        Date(std::string currentDate, std::string sunrise_, std::string sunset_) :
            current_date    {std::move(currentDate)},
            sunrise         {std::move(sunrise_)},
            sunset          {std::move(sunset_)}
            {
                current_date    = unix_to_normal(   std::atoi(current_date.c_str()) );
                sunrise         = unix_to_normal(   std::atoi(sunrise.c_str())      );
                sunset          = unix_to_normal(   std::atoi(sunset.c_str())       );
            }

            /**
             * @note This output needed for debug if we have problems
             * @param os
             * @return current date ouput
             */
           friend  std::ostream& operator<<(std::ostream& os,const Date& d)
            {
                os << "Current Date : "     << d.current_date  << '\n'
                   << "Sunrise time : "     << d.sunrise       << '\n'
                   << "Sunset time  : "     << d.sunset        << '\n';
                return os;
            }

            /**
             *
             */
             std::string unix_to_normal(int timeR)
             {
                 const std::time_t unix_time = timeR;

                 const auto pt = boost::posix_time::from_time_t(unix_time);

                 return boost::posix_time::to_simple_string(pt);
             }

    private:
        std::string current_date   {};
        std::string sunrise        {};
        std::string sunset         {};
    };
    //------------------------------------------------------------------------------------------------------------------
}

#endif //DATATRANSFER_DATA_HPP