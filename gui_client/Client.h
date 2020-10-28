#pragma once

#include <deque>
#include <iostream>

#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\io_service.hpp>
#include <boost\asio\connect.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\write.hpp>
#include <boost\thread.hpp>
#include <boost\signals2.hpp>

#include <windows.h>

#include <vcclr.h>

#include "../shared/TransportData.h"
#include "StringBuilderListening.h"

using boost::asio::ip::tcp;

using DequeTransportBlocks = std::deque<TransportBlock>;

class Client
{
    boost::asio::io_service& io_service;
    tcp::socket socket;
    TransportBlock read_msg;
    DequeTransportBlocks write_msgs;

    gcroot<StringBuilderListening^> log;


public:
    Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, StringBuilderListening^ logger);

    void write(const TransportBlock& msg);

    void close();

    void doConnect(tcp::resolver::iterator endpoint_iterator);

    void doReadHeader();

    void doReadBody();

    void doWrite();

};