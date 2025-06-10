#include "../include/client.h"

#include <regex>
#include<cstdlib>


bool checkIP(const std::string& ip){
    const std::regex ipRegex(
    R"(^((25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)$)"
    );
    return std::regex_match(ip, ipRegex);
}

bool checkPort(const std::string& portStr){
    try {
        int port = std::stoi(portStr);
        return port > 0 && port <= 65535;
    } catch (...) {
        return false;
    }
}

int main(){
    std::string inputIP;
    std::string inputPort;
    int port;


    while (true) {
        std::cout << "Enter server IP address : ";
        std::getline(std::cin, inputIP);

        if (checkIP(inputIP)) {
            break;
        } else {
            std::cout << "Format d'adresse IP invalide. Réessayez.\n";
        }
    }

    while (true) {
        std::cout << "Enter server port (1-65535) : ";
        std::getline(std::cin, inputPort);

        if (checkPort(inputPort)) {
            break;
        } else {
            std::cout << "Port invalide. Réessayez.\n";
        }
    }


    Client client(inputIP, inputPort);
    return 0;
}