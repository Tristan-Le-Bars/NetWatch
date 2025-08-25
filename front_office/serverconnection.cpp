#include "serverconnection.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include "mainwindow.h"


ServerConnection::ServerConnection(std::string address_text_){
    address_text = address_text_;
}

int ServerConnection::EstablishConnection(){
    if ((front_office_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Client socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
        qDebug() << "Client socket creation successfull";
    }

    server_address.sin_family = AF_INET; // Utilisation du protocole IPv4 // sin_family = famille d'adresse
    server_address.sin_port = htons(9002);

    // convertie l'addresse au format binaire
    if (inet_pton(AF_INET, address_text.c_str(), &server_address.sin_addr) <= 0) {
        qDebug() << "Invalid address/ Address not supported";
        return -1;
    }

    //etablie la connection entre le front et le serveur
    if (::connect(front_office_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        qDebug() << "Connection Failed";
        return -2;
    }
    return 0;
}

int ServerConnection::ReadFromServer(){
    char buffer[1024] = {0};
    int bytesRead;
    std::string datatype;
    std::string client_id;
    double total_ram;
    double free_ram;
    double buffer_ram;
    double total_space;
    double free_space;
    double available_space;
    double cpu_usage;


    while ((bytesRead = ::read(front_office_socket, buffer, sizeof(buffer))) > 0) {
        std::string resourcesData(buffer, bytesRead);
        qDebug() << QString::fromStdString(resourcesData);

        datatype = extractString(resourcesData, "\"datatype\": ");
        client_id = extractString(resourcesData, "\"client_id\": ");
        std::cout << "test" << std::endl;
        total_ram = extractDouble(resourcesData, "\"total_ram\": ");
        free_ram = extractDouble(resourcesData, "\"free_ram\": ");
        buffer_ram = extractDouble(resourcesData, "\"buffer_ram\": ");
        total_space = extractDouble(resourcesData, "\"total_space\": ");
        free_space = extractDouble(resourcesData, "\"free_space\": ");
        available_space = extractDouble(resourcesData, "\"available_space\": ");
        cpu_usage = extractDouble(resourcesData, "\"cpu_usage\": ");

        std::cout << "extraction done" << std::endl;

        if(total_ram_map[client_id].size() == 15){
            total_ram_map[client_id].pop_front();
            free_ram_map[client_id].pop_front();
            buffer_ram_map[client_id].pop_front();
            total_space_map[client_id].pop_front();
            free_space_map[client_id].pop_front();
            available_space_map[client_id].pop_front();
            cpu_usage_map[client_id].pop_front();
        }

        total_ram_map[client_id].push_back(total_ram);
        free_ram_map[client_id].push_back(free_ram);
        buffer_ram_map[client_id].push_back(buffer_ram);
        total_space_map[client_id].push_back(total_space);
        free_space_map[client_id].push_back(free_space);
        available_space_map[client_id].push_back(available_space);
        cpu_usage_map[client_id].push_back(cpu_usage);

        std::cout << "map size limit made" << std::endl;

        if (std::find(recieved_clients_id.begin(), recieved_clients_id.end(), client_id) == recieved_clients_id.end()) {
            recieved_clients_id.push_back(client_id);
            emit addDataLayerRequested(QString::fromStdString(client_id));
        }
        std::cout << "cpu usage before emit = " << cpu_usage << std::endl;
        for (const auto& element : free_ram_map[client_id]) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        emit dataReceived(QString::fromStdString(client_id), total_ram, buffer_ram, total_space, free_ram_map[client_id].back(), free_space_map[client_id].back(), cpu_usage_map[client_id].back());
        std::cout << "emit done ?" << std::endl;
    }
    return 0;
}

double ServerConnection::extractDouble(const std::string& json, const std::string& key) {
    std::size_t pos = json.find(key);
    if (pos == std::string::npos) {
        throw std::runtime_error("Key not found");
    }
    pos += key.length();
    pos = json.find_first_of("0123456789.-", pos);
    std::size_t end_pos = json.find_first_not_of("0123456789.-", pos);
    std::string value_str = json.substr(pos, end_pos - pos);
    double extracted_double = std::stod(value_str);
    std::cout << "extracted double = " << extracted_double << std::endl;
    return extracted_double;
}

std::string ServerConnection::extractString(const std::string& json, const std::string& key) {
    std::size_t pos = json.find(key);
    if (pos == std::string::npos) {
        throw std::runtime_error("Key not found");
    }
    pos += key.length();
    pos = json.find("\"", pos) + 1;
    std::size_t end_pos = json.find("\"", pos);
    qDebug() << "extracted string = " << QString::fromStdString(json.substr(pos, end_pos - pos));
    return json.substr(pos, end_pos - pos);
}











