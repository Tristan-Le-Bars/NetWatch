#ifndef CLASS_CLIENT
#define CLASS_CLIENT

#include <string>
#include <vector>

class Client{
    private:
        FileTools file_manager;
        int client_socket; // socket qui representera une connection entrante
        int valread;
        struct sockaddr_in server_address;
        socklen_t server_addrlen = sizeof(server_address);
        char client_ip[INET_ADDRSTRLEN];
        char buffer[1024] = {0};
        MachineResources machine_resources;

    public:
        Client();
        ~Client();
        void commandsHandler();
        void monitorResources();
};

#endif