#include "PoolClients.h"
#include "Client.h"

void PoolClients::join(SessionPtr p)
{
    std::cout << "Connect! Id: " << p->getId() << std::endl;
    clients.insert(p);
}

void PoolClients::leave(SessionPtr p)
{
    std::cout << "Dissconnect! Id: " << p->getId() << std::endl;
    clients.erase(p);
}
