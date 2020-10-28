#include "Server.h"

void Server::doAccept()
{
	acceptor.async_accept(socket, [this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::make_shared<Client>(std::move(socket), connections, io_service, ID++)->start();
			}
			doAccept();
		});
}

Server::Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint) : acceptor(io_service, endpoint), socket(io_service), io_service(io_service)
{
	doAccept();
}

unsigned long long Server::ID(0);