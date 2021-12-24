#include <iostream>
#include <chrono>

/**
 * @brief Self libs
 */
#include "json.hpp"
#include "http_req.hpp"
#include "json_converter.hpp"

/*!
 * @brief Database headers
 */
//#include <cppconn/connection.h>
//#include <cppconn/driver.h>
//#include <mysql_driver.h>
//#include <cppconn/statement.h>

int main() {
//    sql::mysql::MySQL_Driver *driver;
//    sql::Connection *con;
//    sql::Statement *stmt;

    using json = nlohmann::json;

    boost::asio::io_context ioc;
    mowafi::Http_Client client("api.openweathermap.org", "/data/2.5/weather?q=London,uk&appid=1a56d882d9fa61dc0b5f7049cda3b0bc", 80, ioc);
    client.create_request();
    client.write();

    json weather_data = json::parse(client.read());
    std::cout << std::setw(4) << weather_data << '\n';

    //interface::parser parse;
    details::Date date = interface::parser::get_field<details::Date>(weather_data);
    std::cout << date << '\n';
    details::Temperature temp = interface::parser::get_field<details::Temperature>(weather_data);
    std::cout << temp << '\n';

//    driver = sql::mysql::get_mysql_driver_instance();
//    con = driver->connect("localhost", "user", "20021212");
//    stmt = con->createStatement();

//    using namespace fmt::literals;
//    stmt->execute("use Data;");
//    stmt->execute(fmt::format("insert into Weather(Date, Temp) values(\"{date}\", 37.7);", "date"_a = date_request::result()));

      ioc.run();
//    delete stmt;
//    delete con;
}
