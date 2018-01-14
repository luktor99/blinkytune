//
// Created by luktor99 on 31.10.17.
//

#ifndef BLINKYTUNE_UDPSENDER_H
#define BLINKYTUNE_UDPSENDER_H

#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

/**
 * Represents a UDP connection.
 */
class UDPSender {
public:
    /**
     * The constructor.
     * @param host The hostname / IP address of the target device.
     * @param port The port the connection will be established to.
     */
    UDPSender(const std::string &host, const std::string &port);

    /**
     * The destructor.
     */
    ~UDPSender();

    /**
     * Send a buffer to the UDP device.
     * @param b Data buffer.
     */
    void send(const boost::asio::mutable_buffer &b);

private:
    udp::socket socket_; /*!< The UDP socket object. */
};


#endif //BLINKYTUNE_UDPSENDER_H
