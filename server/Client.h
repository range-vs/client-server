#pragma once

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>

#include <boost/asio.hpp>

#include "../shared/TransportData.h"

#include "PoolClients.h"

using boost::asio::ip::tcp;

class Client : public std::enable_shared_from_this<Client>
{
    tcp::socket socket;
    PoolClients& connections;
    TransportBlock read_msg;
    DequeTransportBlocks write_msgs;
    boost::asio::io_service& io_service;

    unsigned long long id;

public:
    Client(tcp::socket socket, PoolClients& connections, boost::asio::io_service& io_service, unsigned long long id);

    void start();

    void doReadHeader();

    void doReadBody(TYPE_OPERATION to);

    void doWrite();

    unsigned long long getId();

};