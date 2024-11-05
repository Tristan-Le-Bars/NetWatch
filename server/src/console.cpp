#include <iostream>
#include <unistd.h>
#include <thread>

#include "../include/server.h"


void console(){
    std::cout << "TODO: implement server console";
}

int main(){
    Server server;
    std::thread client_thread(&Server::connexionSocket, &server);
    std::thread monitoring_thread(&Server::monitoringSocket, &server);
    
    client_thread.join();
    monitoring_thread.join();

    return 0;
}