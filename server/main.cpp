#include "Server.h"
#include "XmlDatabase.h"

#include <sstream>

//BOOL WINAPI HandlerRoutine(DWORD eventCode)
//{
//    switch (eventCode)
//    {
//    case CTRL_CLOSE_EVENT:
//        std::cout << "close console" << std::endl;
//        return FALSE;
//        break;
//    }
//
//    return TRUE;
//}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try
    {
        //SetConsoleCtrlHandler(HandlerRoutine, TRUE);
        boost::asio::io_service io_service;

        std::stringstream convert_num;
        convert_num << XmlDatabase::getInstance()->getPort();
        int port(0);
        convert_num >> port;

        tcp::endpoint endpoint(tcp::v4(), port);
        Server cs(io_service, endpoint);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    XmlDatabase::getInstance()->closeDatabase();

    return 0;
}
