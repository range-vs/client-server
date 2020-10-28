#include "Client.h"
#include "XmlDatabase.h"

Client::Client(tcp::socket socket, PoolClients& connections, boost::asio::io_service& io_service, unsigned long long id) :
    socket(std::move(socket)), connections(connections), io_service(io_service), id(id)
{
}

void Client::start()
{
    connections.join(shared_from_this());
    doReadHeader();

}

void Client::doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket, boost::asio::buffer(read_msg.dataHeader(), read_msg.sizeHeader()),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                auto h = read_msg.dataHeader();
                unsigned num = (h[0] << 24) | (h[1] << 16) | (h[2] << 8) | h[3];
                TYPE_OPERATION to = static_cast<TYPE_OPERATION>(num);
                doReadBody(to);
            }
            else
            {
                connections.leave(self);
            }
        });
}

void Client::doReadBody(TYPE_OPERATION _to)
{
    boost::asio::async_read(socket, boost::asio::buffer(read_msg.dataBlock(), read_msg.sizeBlock()),
        [this, _to](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                //std::cout << static_cast<unsigned>(_to) << std::endl;
                std::cout << "Get hash: " << read_msg.dataBlock();
                std::cout << "\n";

				TransportBlock tb;
				tb.copyHeader(TYPE_OPERATION::NONE);
                switch (_to)
                {
                case TYPE_OPERATION::ADD:
                    if(XmlDatabase::getInstance()->checkElement(read_msg.dataBlock()))
                        tb.copyData("Already exists");
                    else
                    {
                        XmlDatabase::getInstance()->addElement(read_msg.dataBlock());
                        tb.copyData("Added");
                    }
                    break;

                case TYPE_OPERATION::CHECK:
                    if (XmlDatabase::getInstance()->checkElement(read_msg.dataBlock()))
                        tb.copyData("Present");
                    else
                        tb.copyData("Unpresent");
                    break;

                case TYPE_OPERATION::_DELETE:
                    if (XmlDatabase::getInstance()->checkElement(read_msg.dataBlock()))
                    {
                        XmlDatabase::getInstance()->deleteElement(read_msg.dataBlock());
                        tb.copyData("Deleted");
                    }
                    else
                        tb.copyData("Not found for delete");
                    break;

                defualt:break;
                }
				io_service.post([this, tb]()
					{
						bool write_in_progress = !write_msgs.empty();
						write_msgs.push_back(tb);
						if (!write_in_progress)
						{
							doWrite();
						}
					});

                doReadHeader();
            }
            else
            {
                connections.leave(shared_from_this());
            }
        });
}

void Client::doWrite()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket, boost::asio::buffer(write_msgs.front().data(), write_msgs.front().size()),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                write_msgs.pop_front();
                if (!write_msgs.empty())
                {
                    doWrite();
                }
            }
            else
            {
                connections.leave(self);
            }
        });
}

unsigned long long Client::getId() { return id; }