// socket = interface de commmunication entre 2 machine sur un réseau
// un socket comprend: une adresse ip, un port,un protocole

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080

int socket_setup() {
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
    address.sin_port = htons(PORT);        // Conversion du numéro de port en format réseau // sin_port = numéro de port // htons converti l'ordre des octets d'un entier vers l'ordre d'octet du réseau

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

    std::cout << "Server is listening on port " << PORT << std::endl;  // Message indiquant que le serveur est en écoute

    // 5. Acceptation des connexions entrantes
    // accept est utiliser pour autorisé la connection entrante d'un client.
    // connexion_socket = nouveau socket spécifique qui represente la connexion entrante.
    // server_fd = socket en écoute
    // (struct sockaddr*)&address = pointeur vers la structure qui sera remplis avec l'adresse et le port du client.
    // (socklen_t*)&addrlen) =  Pointeur vers un entier qui spécifie la taille de la structure sockaddr pointée par address
    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_addrlen = sizeof(client_address);
        if ((connexion_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        //inet_ntop sert a convertir une adresse ip en une chaine de character compréhensible pour un humain.
        // AF_INTET -> ipv4
        // &address.sin_addr = pointer vers l'adresse ip du socket en binaire.
        // server_ip = chaine de character dans laquelle mettre l'adresse ip en chaine de character.
        // INET_ADDRSTRLEN = taille d'une adresse ipv4
        inet_ntop(AF_INET, &address.sin_addr, server_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::cout << "Connection established between server (" << server_ip << ") and client (" << client_ip << ")." << std::endl;

        while (1){
            // Lecture des données du client
            // read lit les donnés du client via le socket client
            // les donnés sont stocket dans la variable "buffer";
            // 1024 = nombre maximal d'octet à lire
            valread = read(connexion_socket, buffer, 1024);
            std::cout << "Data received: " << buffer << std::endl;
            
            // Réponse au client (par exemple, accusé de réception)
            char *response = "Message received by the server";
            send(connexion_socket, response, strlen(response), 0);
            printf("Hello message sent\n");
            
            memset(buffer, 0, sizeof(buffer));
        }
    }
    // Fermeture du socket de la connexion client
    close(connexion_socket);

    close(server_fd);  // Ferme le socket du serveur
    return 0;          // Terminaison normale du programme
}

int main(){
    socket_setup();
}