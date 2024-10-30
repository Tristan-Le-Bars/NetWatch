#ifndef CLASS_CLIENT
#define CLASS_CLIENT

#include <string>
#include <vector>
#include <mutex>
#include <memory>
#include "machine_resources.h"
#include "file_tools.h"
#include <netinet/in.h>
#include <arpa/inet.h>

class Client{
    private:
        std::string id;
        FileTools file_manager;
        int client_socket; // socket qui representera une connection entrante
        int valread;
        struct sockaddr_in server_address;
        socklen_t server_addrlen = sizeof(server_address);
        char client_ip[INET_ADDRSTRLEN];
        char buffer[1024] = {0};
        // MachineResources machine_resources;
        std::shared_ptr<MachineResources> machine_resources;
        std::mutex socketMutex;
        
    public:
        Client();
        ~Client();

        void setId();

        std::string getId();

        void commandsHandler();
        void monitorResources();
        void sendMachineResources();
};

#endif