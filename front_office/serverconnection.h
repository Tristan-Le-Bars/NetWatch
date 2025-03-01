#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include<netinet/in.h>
#include<arpa/inet.h>

class ServerConnection
{
private:
    int front_office_socket;
    struct sockaddr_in server_address;
    socklen_t server_addrlen = sizeof(server_address);
    char client_ip[INET_ADDRSTRLEN];

    int EstablishConnection();
public:
    int ReadFromServer();
    ServerConnection();
};

#endif // SERVERCONNECTION_H
