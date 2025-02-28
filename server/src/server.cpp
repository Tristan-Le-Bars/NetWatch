// socket = interface de commmunication entre 2 machine sur un réseau
// un socket comprend: une adresse ip, un port,un protocole

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <thread>
#include <mutex>
#include "../include/server.h"
#include "../include/file_tools.h"

#define FRONTEND_WEBSOCKET_PORT 9002
#define CLIENT_PORT 8080

int Server::connexionSocket() {
    FileTools file_manager;
    int server_fd;        // File descriptor pour le socket du serveur
    int connexion_socket; // socket qui representera une connection entrante
    int valread;
    struct sockaddr_in address;  // Structure pour stocker l'adresse du serveur // sockaddr_in represent l'adresse d'un socket
    int opt = 1;          // Option utilisée pour configurer les options de socket
    int addrlen = sizeof(address);  // Taille de la structure d'adresse
    char server_ip[INET_ADDRSTRLEN]; // chaine de character contenant l'adresse ipv4 du server
    char client_ip[INET_ADDRSTRLEN]; // chaine de character contenant l'adresse ipv4 du client
    char buffer[1024] = {0};


    // 1. Création du file descriptor pour le socket
    // le mot clé socket créé un point de terminaison pour la communication réseau. AF_INET = utilisation du protocol ipv4. SOCK_STRAM = socket de type stream. 0 = choix automatique du protocol.
    // server_fd devient concretement un socket à ce moment là.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket creation failed");  // Affiche un message d'erreur en cas d'échec de la création du socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }
    else{
        std::cout << "socket creation successfull" << std::endl;
    }

    // 2. Configuration des options de socket
    // Permet de réutiliser l'adresse et le port pour éviter les erreurs "address already in use"
    // le mot clé setsockopt permet de définir des option sur un socket.
    // server_fd = file descriptor sur lequel les options doivent être configurer.
    // SOL_SOCKET = niveau ou l'option est défini. ici au niveau du socket.
    // SO_REUSEADDR | SO_REUSEPORT = permert de réutiliser une adresse et un port.
    // &opt = valeur à définir pour l'option ???
    // sizeof(opt) = taille en octet de la valeur de l'option
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");     // Affiche un message d'erreur en cas d'échec de la configuration des options
        close(server_fd);         // Ferme le socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }
    else {
        std::cout << "socket option setting successfull" << std::endl;
    }

    // 3. Bind du socket à une adresse et un port
    address.sin_family = AF_INET;          // Utilisation du protocole IPv4 // sin_family = famille d'adresse
    address.sin_addr.s_addr = INADDR_ANY;  // Accepte les connexions de n'importe quelle adresse réseau // sin_addr.s_addr = adresse IP
    address.sin_port = htons(CLIENT_PORT);        // Conversion du numéro de port en format réseau // sin_port = numéro de port // htons converti l'ordre des octets d'un entier vers l'ordre d'octet du réseau

    // Lie le socket à l'adresse et au port spécifiés
    // bind associe un socket à une adresse IP et à un port local
    // server_fd = file descriptor à associer
    // (struct sockaddr*)&address = pointeur vers la structure contenant l'adresse et le port à associer.
    // sizeof(address) = taille en octet de la structure contenant l'adresse et le port.
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");    // Affiche un message d'erreur en cas d'échec du bind
        close(server_fd);         // Ferme le socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }
    else{
        std::cout << "socket/addresse binding successfull" << std::endl;
    }

    // 4. Mise en écoute du socket
    // listen prépare le socket à accepter les connexions entrantes
    // server_fd = file descriptor du socket à mettre en écoute
    // 3 = taille maximal de la queu de connection
    if (listen(server_fd, 3) < 0) {
        perror("listen");         // Affiche un message d'erreur en cas d'échec de la mise en écoute
        close(server_fd);         // Ferme le socket
        exit(EXIT_FAILURE);       // Quitte le programme avec un code d'échec
    }

    std::cout << "Server is listening on port " << CLIENT_PORT << std::endl;  // Message indiquant que le serveur est en écoute

    // 5. Acceptation des connexions entrantes
    // accept est utiliser pour autorisé la connection entrante d'un client.
    // connexion_socket = nouveau socket spécifique qui represente la connexion entrante.
    // server_fd = socket en écoute
    // (struct sockaddr*)&address = pointeur vers la structure qui sera remplis avec l'adresse et le port du client.
    // (socklen_t*)&addrlen) =  Pointeur vers un entier qui spécifie la taille de la structure sockaddr pointée par address
    int bytesRead = 0;
    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_addrlen = sizeof(client_address);
        int connexion_socket;
        if ((connexion_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        // Créez un thread pour chaque connexion client
        std::thread client_thread(&Server::clientHandler, this, connexion_socket, std::ref(client_address));
        client_thread.detach();  // Détachez le thread pour qu'il puisse fonctionner indépendamment
    }
    // Fermeture du socket de la connexion client
    close(connexion_socket);

    close(server_fd);  // Ferme le socket du serveur
    return 0;          // Terminaison normale du programme
}

int Server::monitoringSocket(){
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(FRONTEND_WEBSOCKET_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // while (true) {
    int new_socket;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        // continue;
    }
    // Get the received data and send them to the front end
    // std::lock_guard<std::mutex> lock(client_mutex);
    admin_sockets.push_back(new_socket);
    std::cout << "Front-end client connected." << std::endl;
    // }
}

int Server::clientHandler(int client_socket, struct sockaddr_in client_address){
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Connection established with client (" << client_ip << ")." << std::endl;

    FileTools file_manager;
    char buffer[1024] = {0};
    int bytesRead;

    while ((bytesRead = read(client_socket, buffer, sizeof(buffer))) > 0) {
            std::string command(buffer, bytesRead);
            if (command == "send_resources") {
                // Read the incoming machine resources data
                bytesRead = read(client_socket, buffer, 1024);  // Read the data into the buffer
                std::string resourcesData(buffer, bytesRead);

                // Display the received data or process it as needed
                std::cout << "Received machine resources data from client:" << std::endl;
                std::cout << resourcesData << std::endl;
                
                // Optionally, send a response back to the client
                std::string response = "Machine resources data received";
                send(client_socket, response.c_str(), response.size(), 0);

                // ICI format le json pour tout envoyer d'un coup ?

                // Send data to the admin front-end
                // std::lock_guard<std::mutex> lock(client_mutex);  // Protège l'accès à frontend_clients
                std::cout << 'list of frontend sockets:' << std::endl;
                for (int frontend_socket : admin_sockets){
                    std::cout << "  - "<< frontend_socket << std::endl;
                }
                for (int frontend_socket : admin_sockets) {
                    std::cout << "try to send data to the front-end " << frontend_socket << std::endl;
                    
                    std::cout << "data sent :" << std::endl << resourcesData.c_str() << std::endl;
                    int send_result = send(frontend_socket, resourcesData.c_str(), resourcesData.size(), 0);
                    std::cout << "send result = " << send_result << std::endl;
                    if (send_result < 0) {
                        std::cout << "Erreur d'envoi des données au client front-end" << std::endl;
                    }
                }
            }
        }
    std::cout << "Client disconnected: " << client_ip << std::endl;
    close(client_socket);
    return 0;
}