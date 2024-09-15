#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

#define PORT 8080

std::vector<unsigned char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string& filename, const std::vector<unsigned char>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

int client_socket(){
    int client_socket; // socket qui representera une connection entrante
    int valread;
    struct sockaddr_in server_address;
    socklen_t server_addrlen = sizeof(server_address);
    char client_ip[INET_ADDRSTRLEN];
    char buffer[1024] = {0};

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
        return -1;
    }

    // connect etablie la connection entre un socket client et un socket server
    // client_socket = le socket du client
    // pointer vers une struct sockaddr contenant l'adresse du server
    // taille en octer de la struct sockaddr du socket du server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }

    std::cout << "List of commands: " << std::endl;
    std::cout << " - send_message" << std::endl;
    std::cout << " - upload_file" << std::endl << std::endl;

    while (1){
        std::string command;
        std::cout << "$> ";
        std::cin >> command;
        send(client_socket, command.c_str(), strlen(command.c_str()), 0);
        if(command == "send_message"){
            // Envoi de la chaîne de caractères
            // send envoie des donnés à travers un socket
            // client_socket = socket du client
            // message = char* donnees envoyees
            // taille du message
            std::cout << "type your message: ";
            std::string message;
            std::cin >> message;
            send(client_socket, message.c_str(), strlen(message.c_str()), 0); // !ICI le server ne reçois que le premier mot
            std::cout << "Message sent: " << message << std::endl;

            // Lecture de la réponse du serveur
            // read lit les donnés du server
            std::fill(std::begin(buffer), std::end(buffer), 0);
            valread = read(client_socket, buffer, 1024);
            std::cout << "Server response: " << std::string(buffer, valread) << std::endl;
        }
        else if(command == "upload_file"){
            std::string filename;
            std::string yes_no;
            // ecrire le path vers le fichier a envoyer
            std::cout << "path to the file to send: ";
            std::cin >> filename;
            if (!std::filesystem::exists(filename)) {
                std::cout << "file not found." << std::endl;
                }
            // choisire si le fichier doit être crypter ou non
            std::cout << "do you want to encrypt the file ? (y/n): ";
            std::cin >> yes_no;
            // lit et envoie les donnée du fichier
            std::vector<unsigned char> filedata = readFile(filename);
            send(client_socket, filedata.data(), filedata.size(), 0);
            std::cout << "File sent to server" << std::endl;
            std::fill(std::begin(buffer), std::end(buffer), 0);
            valread = read(client_socket, buffer, 1024);
            std::cout << "Server response: " << std::string(buffer, valread) << std::endl;
        }
        else if (command == "list_files") {
            // Receive the list of files from the server
            int valread = read(client_socket, buffer, 1024);
            std::string fileList(buffer, valread);
            std::cout << fileList << std::endl;
        }
        else if (command == "download_file") {
            std::string filename;
            std::cout << "file to download: ";
            std::cin >> filename;

            // Envoyer la commande au serveur
            // std::string cmd = "download_file";
            // send(client_socket, cmd.c_str(), cmd.size(), 0);

            // Envoyer le nom du fichier au serveur
            send(client_socket, filename.c_str(), filename.size(), 0);

            // Réception de la réponse du serveur
            int valread = read(client_socket, buffer, 1024);
            std::string response(buffer, valread);
            std::cout << response << std::endl;
            if (response == "FILE_FOUND") {
                std::vector<unsigned char> filedata;
                int bytesRead;

                // Lire les données du fichier envoyées par le serveur
                bytesRead = read(client_socket, buffer, sizeof(buffer));
                filedata.insert(filedata.end(), buffer, buffer + bytesRead);

                // Sauvegarder le fichier reçu
                writeFile("downloaded_" + filename, filedata);
                std::cout << "File downloaded and saved as 'downloaded_" << filename << "'" << std::endl;
            }
            else if (response == "FILE_NOT_FOUND") {
                std::cout << "File not found on the server." << std::endl;
            }
        }
        else{
            std::cout << "command " + command + " unknown." << std::endl;
        }
    }
    close(client_socket);  // Ferme le socket du serveur
    return 0;
};

int main(){
    client_socket();
}