#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include<netinet/in.h>
#include<arpa/inet.h>
#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <set>

#include "datalayout.h"

class ServerConnection
{
private:
    int front_office_socket;
    struct sockaddr_in server_address;
    socklen_t server_addrlen = sizeof(server_address);
    char client_ip[INET_ADDRSTRLEN];
    double extractDouble(const std::string& json, const std::string& key);
    std::string extractString(const std::string& json, const std::string& key);

    std::map<std::string, std::deque<double>> total_ram_map;
    std::map<std::string, std::deque<double>> free_ram_map;
    std::map<std::string, std::deque<double>> buffer_ram_map;
    std::map<std::string, std::deque<double>> total_space_map;
    std::map<std::string, std::deque<double>> free_space_map;
    std::map<std::string, std::deque<double>> available_space_map;
    std::map<std::string, std::deque<double>> cpu_usage_map;
public:
    std::vector<std::string> recieved_clients_id;
    std::map<std::string, DataLayout> datalayout_map;
    int EstablishConnection();
    int ReadFromServer();
    int DisplayClientsData();
    ServerConnection();
};

#endif // SERVERCONNECTION_H
