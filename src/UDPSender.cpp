//
// Created by luktor99 on 31.10.17.
//

#include <iostream>
#include "UDPSender.h"

namespace {
    boost::asio::io_service io_service; // io_service object is only used by UDPSender class
}

UDPSender::UDPSender(const std::string &host, const std::string &port) : socket_(io_service, udp::v4()) {
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host, port, udp::resolver::query::canonical_name);
    udp::resolver::iterator iter = resolver.resolve(query);

    std::cout << "Connecting to " << host << " on port " << port << "..." << std::endl;
    socket_.connect(iter->endpoint());
}

UDPSender::~UDPSender() {
    socket_.close();
}

void UDPSender::send(const boost::asio::mutable_buffer &b) {
    socket_.send(boost::asio::buffer(b));
}