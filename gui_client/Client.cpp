#include "Client.h"

#include <gcroot.h>

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, StringBuilderListening^ logger) :
	io_service(io_service), socket(io_service), log(logger)
{
	doConnect(endpoint_iterator);
}

void Client::write(const TransportBlock& msg)
{
	io_service.post([this, msg]()
		{
			bool write_in_progress = !write_msgs.empty();
			write_msgs.push_back(msg);
			if (!write_in_progress)
				doWrite();
		});
}

void Client::close()
{
	io_service.post([this]() { socket.close(); });
}

void Client::doConnect(tcp::resolver::iterator endpoint_iterator)
{
	boost::asio::async_connect(socket, endpoint_iterator, [this](boost::system::error_code ec, tcp::resolver::iterator)
		{
			if (!ec)
				doReadHeader();
			log->Append(gcnew System::String("Connect to server\n"));
			std::cout << "Connect to server" << std::endl;
		});
}

void Client::doReadHeader()
{
	boost::asio::async_read(socket, boost::asio::buffer(read_msg.dataHeader(), read_msg.sizeHeader()),
		[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
				doReadBody();
			else
				socket.close();
		});
}

void Client::doReadBody()
{
	boost::asio::async_read(socket, boost::asio::buffer(read_msg.dataBlock(), read_msg.sizeBlock()),
		[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::cout << read_msg.dataBlock();
				std::cout << "\n";
				log->Append(gcnew System::String(read_msg.dataBlock()));
				log->Append(gcnew System::String("\n"));
				doReadHeader();
			}
			else
				socket.close();
		});
}

void Client::doWrite()
{
	boost::asio::async_write(socket, boost::asio::buffer(write_msgs.front().data(), write_msgs.front().size()),
		[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				write_msgs.pop_front();
				if (!write_msgs.empty())
					doWrite();
			}
			else
				socket.close();
		});
}
