#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <thread>
#include <random>
#include <iomanip>

#include "../include/file_tools.h"
#include "../include/client.h"
#include "../include/machine_resources.h"

Client::Client(std::string inputIP, std::string inputPort){
    setId();
    machine_resources = std::make_shared<MachineResources>(id);
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Client socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
        std::cout << "Client socket creation successfull" << std::endl;
    }

    server_address.sin_family = AF_INET;          // Utilisation du protocole IPv4 // sin_family = famille d'adresse
    server_address.sin_port = htons(std::atoi(std::getenv("PORT")));        // Conversion du numéro de port en format réseau // sin_port = numéro de port // htons converti l'ordre des octets d'un entier vers l'ordre d'octet du réseau
    //inet_pton converti une adresse ip au format binaire
    //AF_INET -> ipv4
    // adresse ip !changer pour pouvoir la rentrer manuellement;
    // adresse vers le sockaddr_in qui stockeras l'adresse en format binaire
    if (inet_pton(AF_INET, inputIP.c_str(), &server_address.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        // return -1;
    }

    // connect etablie la connection entre un socket client et un socket server
    // client_socket = le socket du client
    // pointer vers une struct sockaddr contenant l'adresse du server
    // taille en octer de la struct sockaddr du socket du server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        // return -1;
    }

    std::cout << "List of commands: " << std::endl;
    std::cout << " - send_message" << std::endl;
    std::cout << " - upload_file" << std::endl << std::endl;

    std::thread monitoring_thread(&Client::monitorResources, this);
    std::thread commands_thread(&Client::commandsHandler, this);

    monitoring_thread.join();
    commands_thread.join();
    // monitoring_thread.detach();
    // commands_thread.detach();

    // close(client_socket);  // Ferme le socket du serveur
}

Client::~Client(){
    close(client_socket);  // Ferme le socket du serveur
}

void Client::monitorResources() {
    std::string formated_data;
    try{
        while (true) {
            machine_resources->updateResourcesInfo();
            machine_resources->getUpTime();
            machine_resources->getRAMUsage();
            machine_resources->getStorageUsage();
            machine_resources->getCPUUsage();
            // send(client_socket, "send_resources", strlen("send_resources"), 0);
            sendMachineResources();
            
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 2 seconds before updating again
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in monitorResources: " << e.what() << std::endl;
    }

}

void Client::commandsHandler() {
    std::cout << "entering commands handler" << std::endl;
    
    while (true) {
        std::string command;
        std::cout << "$> "; //FIX HERE
        std::cin >> command;
        send(client_socket, command.c_str(), strlen(command.c_str()), 0);
        
        if (command == "send_resources"){
            sendMachineResources();
        }
        else {
            std::cout << "Command " << command << " unknown." << std::endl;
        }
    }
}

void Client::sendMachineResources(){
    std::string resourcesData = machine_resources->getFormattedData();
    
    // Send the "send_resources" command firsts
    std::string command = "send_resources";
    send(client_socket, command.c_str(), command.size(), 0);
    
    // Send the formatted resources data
    send(client_socket, resourcesData.c_str(), resourcesData.size(), 0);
}

void Client::setId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (int i = 0; i < 8; i++) ss << std::setw(1) << dis(gen);
    ss << "-";
    for (int i = 0; i < 4; i++) ss << std::setw(1) << dis(gen);
    ss << "-4"; // version 4
    for (int i = 0; i < 3; i++) ss << std::setw(1) << dis(gen);
    ss << "-";
    ss << std::setw(1) << ((dis(gen) & 0x3) | 0x8); // version variant bits
    for (int i = 0; i < 3; i++) ss << std::setw(1) << dis(gen);
    ss << "-";
    for (int i = 0; i < 12; i++) ss << std::setw(1) << dis(gen);

    id = ss.str();
}