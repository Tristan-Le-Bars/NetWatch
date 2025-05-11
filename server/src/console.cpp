#include <iostream>
#include <unistd.h>
#include <thread>

#include "../include/server.h"


void console(){
    std::cout << "TODO: implement server console";
}

int main(){
    std::cout << std::unitbuf;
    int frontendPort = std::getenv("FRONTEND_WEBSOCKET_PORT") ? std::stoi(std::getenv("FRONTEND_WEBSOCKET_PORT")) : 9002;
    int clientPort = std::getenv("CLIENT_PORT") ? std::stoi(std::getenv("CLIENT_PORT")) : 8080;
    Server server(frontendPort, clientPort);
    std::thread client_thread(&Server::connexionSocket, &server);
    std::thread monitoring_thread(&Server::monitoringSocket, &server);
    
    client_thread.join();
    monitoring_thread.join();

    return 0;
}