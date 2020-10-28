#pragma once

#include <boost/asio.hpp>

#include "Client.h"

using boost::asio::ip::tcp;

class Server
{
    tcp::acceptor acceptor;
    tcp::socket socket;
    PoolClients connections;
    boost::asio::io_service& io_service;

    static unsigned long long ID;

    void doAccept();
public:
    Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
};
