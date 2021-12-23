#include <iostream>
#include <chrono>

/**
 * @brief Self libs
 */
#include "json.hpp"
#include "http_req.hpp"

/*!
 * @brief Database headers
 */
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>

#include <fmt/format.h>

struct date_request{
    static std::string result(){
        std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};

        std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

        using namespace fmt::literals;
        std::string current_date = fmt::format("{year}-{month}-{day}",
                                               "year"_a = std::to_string(static_cast<int>(ymd.year())),
                                               "month"_a = std::to_string(static_cast<unsigned>(ymd.month())),
                                               "day"_a = std::to_string(static_cast<unsigned>(ymd.day()))
        );

        return current_date;
    }
};

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    using json = nlohmann::json;

    boost::asio::io_context ioc;
    mowafi::Http_Client client("api.openweathermap.org", "/data/2.5/weather?q=London,uk&appid=1a56d882d9fa61dc0b5f7049cda3b0bc", 80, ioc);
    client.create_request();
    client.write();

    json weather_data = json::parse(client.read());
    std::cout << std::setw(4) << weather_data << '\n';

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("localhost", "user", "20021212");
    stmt = con->createStatement();

//    using namespace fmt::literals;
//    stmt->execute("use Data;");
//    stmt->execute(fmt::format("insert into Weather(Date, Temp) values(\"{date}\", 37.7);", "date"_a = date_request::result()));

    delete stmt;
    delete con;
}
