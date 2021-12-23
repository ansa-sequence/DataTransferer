//
// Created by sakhil on 23.12.2021.
//

#ifndef DATATRANSFER_HTTP_REQ_HPP
#define DATATRANSFER_HTTP_REQ_HPP

#include <string>
#include <utility>
#include <vector>

/*!
 * @brief Boost Beast library
 */
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>


namespace mowafi {
    namespace   beast   = boost::beast;         // from <boost/beast.hpp>
    namespace   http    = beast::http;          // from <boost/beast/http.hpp>
    namespace   net     = boost::asio;          // from <boost/asio.hpp>
    using       tcp     = net::ip::tcp;         // from <boost/asio/ip/tcp.hpp

    /**
     * Http Client class
     */
    class Http_Client final {
    public:
        /**
         * @brief Http CLient constructor with following params
         *
         * @param host_ - string
         * @param target_  - string
         * @param port_ - string
         * @param ioc_ - io_context
         */
        Http_Client(std::string host_, std::string target_, std::uint16_t port_, net::io_context& ioc_) :
                        host    {std::move(host_)},
                        target  {std::move(target_)},
                        port    {port_},
                        ioc     (ioc_),
                        stream  (ioc)
                        {
                            tcp::resolver       resolver(ioc);
                            const auto result = resolver.resolve(host.c_str(),std::to_string(port));

                            stream.connect(result);
                        }

    public:
        http::request<http::string_body> create_request() const
        {
            http::request<http::string_body> request_{http::verb::get, target, 11};
            request_.set(http::field::host, host);
            request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            return request_;
        }

//        http::response<http::dynamic_body> create_response()
//        {
//            http::response<http::dynamic_body> response{};
//            return response;
//        }

        void write(){
            http::write(stream, create_request());
        }

        void read(){
            http::response<http::dynamic_body> response{};
            http::read(stream,buffer, response);

            std::cout << boost::beast::buffers_to_string(response.body().data()) << '\n';
        }
    private:
        std::string         host{};
        std::string         target{};
        std::uint16_t       port{};
        net::io_context&    ioc;

        beast::tcp_stream   stream;
        beast::flat_buffer  buffer;
    };
}
#endif //DATATRANSFER_HTTP_REQ_HPP
