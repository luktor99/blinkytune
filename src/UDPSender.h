//
// Created by luktor99 on 31.10.17.
//

#ifndef BLINKYTUNE_UDPSENDER_H
#define BLINKYTUNE_UDPSENDER_H

#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UDPSender {
public:
    UDPSender(const std::string &host, const std::string &port);

    ~UDPSender();

    void send(const char *msg) {
        socket_.send(boost::asio::buffer(msg, 180));
    }

    void send(const boost::asio::mutable_buffer &b) {
        socket_.send(boost::asio::buffer(b));
    }

private:
    udp::socket socket_;
};


#endif //BLINKYTUNE_UDPSENDER_H
