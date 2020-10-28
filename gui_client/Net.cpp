#include "Net.h"
#include "ConverterString.h"

using boost::asio::ip::tcp;

void NetPoint::StartSocket(System::String^ p, System::String^ port, StringBuilderListening^ logger)
{
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({ ConverterString::toString(p).c_str(), ConverterString::toString(port).c_str() });
    Client c( io_service, endpoint_iterator, logger );
    cl = &c;
    io_service.run();
}

void NetPoint::SendMessage(System::String^ m, const TYPE_OPERATION& tp)
{
    TransportBlock tb;
    tb.copyHeader(tp);
    tb.copyData(ConverterString::toString(m).c_str());
    cl->write(tb);
}

void NetPoint::StopSocket()
{
    cl->close();
}
