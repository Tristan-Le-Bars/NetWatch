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
#include "../headers/file_tools.h"
#include "../headers/client.h"
#include "../headers/machine_resources.h"


#define PORT 8080

Client::Client(){
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Client socket creation failed");  // Affiche un message d'erreur en cas d'échec de la création du socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }
    else{
        std::cout << "Client socket creation successfull" << std::endl;
    }

    server_address.sin_family = AF_INET;          // Utilisation du protocole IPv4 // sin_family = famille d'adresse
    server_address.sin_port = htons(PORT);        // Conversion du numéro de port en format réseau // sin_port = numéro de port // htons converti l'ordre des octets d'un entier vers l'ordre d'octet du réseau
    //inet_pton converti une adresse ip au format binaire
    //AF_INET -> ipv4
    // adresse ip !changer pour pouvoir la rentrer manuellement;
    // adresse vers le sockaddr_in qui stockeras l'adresse en format binaire
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
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

    monitoring_thread.detach();
    commands_thread.detach();

    close(client_socket);  // Ferme le socket du serveur
}

Client::~Client(){
    close(client_socket);  // Ferme le socket du serveur
}

void Client::monitorResources() {
    while (true) {
        machine_resources.updateResourcesInfo();
        machine_resources.getUpTime();
        machine_resources.getStorageUsage();
        machine_resources.getRAMUsage();
        machine_resources.getCPUUsage();

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 2 seconds before updating again
    }
}

void Client::commandsHandler() {
    while (true) {
        std::string command;
        std::cout << "$> ";
        std::cin >> command;
        send(client_socket, command.c_str(), strlen(command.c_str()), 0);
        
        if (command == "send_message") {
            // Envoi de la chaîne de caractères
            // send envoie des donnés à travers un socket
            // client_socket = socket du client
            // message = char* donnees envoyees
            // taille du message
            std::cout << "Type your message: ";
            std::string message;
            std::cin >> message;
            send(client_socket, message.c_str(), strlen(message.c_str()), 0);
            std::cout << "Message sent: " << message << std::endl;

            // Lecture de la réponse du serveur
            // read lit les donnés du server
            std::fill(std::begin(buffer), std::end(buffer), 0);
            valread = read(client_socket, buffer, 1024);
            std::cout << "Server response: " << std::string(buffer, valread) << std::endl;
        }
        else if (command == "upload_file") {
            std::string filename;
            std::string yes_no;
            // ecrire le path vers le fichier a envoyer
            std::cout << "Path to the file to send: ";
            std::cin >> filename;

            if (!std::filesystem::exists(filename)) {
                std::cout << "File not found." << std::endl;
                continue;
            }
            // choisire si le fichier doit être crypter ou non
            std::cout << "Do you want to encrypt the file? (y/n): ";
            std::cin >> yes_no;
            // lit et envoie les donnée du fichier
            std::vector<unsigned char> filedata = file_manager.readFile(filename);
            send(client_socket, filedata.data(), filedata.size(), 0);
            std::cout << "File sent to server." << std::endl;

            std::fill(std::begin(buffer), std::end(buffer), 0);
            valread = read(client_socket, buffer, 1024);
            std::cout << "Server response: " << std::string(buffer, valread) << std::endl;
        }
        else if (command == "list_files") {
            valread = read(client_socket, buffer, 1024);
            std::string fileList(buffer, valread);
            std::cout << fileList << std::endl;
        }
        else if (command == "download_file") {
            // Receive the list of files from the server
            std::string filename;
            std::cout << "File to download: ";
            std::cin >> filename;

             // Envoyer la commande au serveur
            // std::string cmd = "download_file";
            // send(client_socket, cmd.c_str(), cmd.size(), 0);

            // Envoyer le nom du fichier au serveur
            send(client_socket, filename.c_str(), filename.size(), 0);

            // Réception de la réponse du serveur
            int valread = read(client_socket, buffer, 1024);
            std::string response(buffer, valread);
            if (response == "FILE_FOUND") {
                std::vector<unsigned char> filedata;
                // Lire les données du fichier envoyées par le serveur
                int bytesRead = read(client_socket, buffer, sizeof(buffer));
                filedata.insert(filedata.end(), buffer, buffer + bytesRead);
                // Sauvegarder le fichier reçu
                file_manager.writeFile("downloaded_" + filename, filedata);
                std::cout << "File downloaded and saved as 'downloaded_" << filename << "'" << std::endl;
            } 
            else if (response == "FILE_NOT_FOUND") {
                std::cout << "File not found on the server." << std::endl;
            }
        }
        else {
            std::cout << "Command " << command << " unknown." << std::endl;
        }
    }
}