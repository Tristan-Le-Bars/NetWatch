#ifndef CLASS_SERVER
#define CLASS_SERVER

#include <string>
#include <vector>

class Server{
    private:
    public:
        int connexionSocket();
        int clientHandler(int client_socket, struct sockaddr_in client_address);
        void server_console();
};

#endif