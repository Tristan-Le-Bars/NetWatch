#include "serverconnection.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define PORT 9002

ServerConnection::ServerConnection()
{
    if (EstablishConnection() != 0){
        std::cout << "Error while establishing connection." << std::endl;
    }
    else{
        ReadFromServer();
    }
}

int ServerConnection::EstablishConnection(){
    if ((front_office_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Client socket creation failed");  // Affiche un message d'erreur en cas d'échec de la création du socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }
    else{
        std::cout << "Client socket creation successfull" << std::endl;
    }

    server_address.sin_family = AF_INET;          // Utilisation du protocole IPv4 // sin_family = famille d'adresse
    server_address.sin_port = htons(PORT);

    // convertie l'addresse au format binaire
    if (inet_pton(AF_INET, "0.0.0.0", &server_address.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    //etablie la connection entre le front et le serveur
    if (connect(front_office_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return -2;
    }
    return 0;
}

int ServerConnection::ReadFromServer(){
    char buffer[1024] = {0};
    int bytesRead;

    while ((bytesRead = read(front_office_socket, buffer, sizeof(buffer))) > 0) {
        std::string resourcesData(buffer, bytesRead);
        std::cout << resourcesData << std::endl;
    }
}











