//
// Created by luktor99 on 31.10.17.
//

#include "UDPSender.h"

namespace {
    boost::asio::io_service io_service; // io_service object is only used by UDPSender class
}

UDPSender::UDPSender(const std::string &host, const std::string &port) : socket_(io_service, udp::v4()) {
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host, port, udp::resolver::query::canonical_name);
    udp::resolver::iterator iter = resolver.resolve(query);

    socket_.connect(*iter);
}

UDPSender::~UDPSender() {
    socket_.close();
}