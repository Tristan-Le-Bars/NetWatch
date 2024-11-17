#ifndef CLASS_SERVER
#define CLASS_SERVER

#include <string>
#include <vector>
#include <mutex>

class Server{
    private:
        std::vector<std::string> resources_json;
        std::vector<int> admin_sockets;
        std::mutex client_mutex; 
    public:
        int connexionSocket();
        int clientHandler(int client_socket, struct sockaddr_in client_address);
        int monitoringSocket();
};

#endif