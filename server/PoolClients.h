#pragma once

#include <set>
#include <deque>

#include <boost/asio.hpp>

#include "../shared/TransportData.h"

using boost::asio::ip::tcp;

class Client;
using SessionPtr = std::shared_ptr<Client>;
using DequeTransportBlocks = std::deque<TransportBlock>;


class PoolClients
{
public:
    void join(SessionPtr p);
    void leave(SessionPtr p);

private:
    std::set<SessionPtr> clients;
    DequeTransportBlocks recent_msgs;
};