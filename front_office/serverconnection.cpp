#include "serverconnection.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define PORT 9002

ServerConnection::ServerConnection()
{
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
    std::string datatype;
    std::string client_id;
    double total_ram;
    double free_ram;
    double buffer_ram;
    double total_space;
    double free_space;
    double available_space;
    unsigned long long cpu_usage;


    while ((bytesRead = read(front_office_socket, buffer, sizeof(buffer))) > 0) {
        std::string resourcesData(buffer, bytesRead);
        std::cout << resourcesData << std::endl;
    //     datatype = extractString(resourcesData, "\"datatype\":\"");
    //     client_id = extractString(resourcesData, "\"client_id\":\"");
    //     total_ram = extractDouble(resourcesData, "\"total_ram\": ");
    //     free_ram = extractDouble(resourcesData, "\"free_ram\": ");
    //     buffer_ram = extractDouble(resourcesData, "\"buffer_ram\": ");
    //     total_space = extractDouble(resourcesData, "\"total_space\": ");
    //     free_space = extractDouble(resourcesData, "\"free_space\": ");
    //     available_space = extractDouble(resourcesData, "\"available_space\": ");
    //     cpu_usage = extractDouble(resourcesData, "\"cpu_usage\": ");

    //     if(total_ram_map[client_id].size() == 15){
    //         total_ram_map[client_id].pop_front();
    //         free_ram_map[client_id].pop_front();
    //         buffer_ram_map[client_id].pop_front();
    //         total_space_map[client_id].pop_front();
    //         free_space_map[client_id].pop_front();
    //         available_space_map[client_id].pop_front();
    //         cpu_usage_map[client_id].pop_front();
    //     }

    //     total_ram_map[client_id].push_back(total_ram);
    //     free_ram_map[client_id].push_back(free_ram);
    //     buffer_ram_map[client_id].push_back(buffer_ram);
    //     total_space_map[client_id].push_back(total_space);
    //     free_space_map[client_id].push_back(free_space);
    //     available_space_map[client_id].push_back(available_space);
    //     cpu_usage_map[client_id].push_back(cpu_usage);

    //     if (recieved_clients_id.find(client_id) == recieved_clients_id.end()) {
    //         recieved_clients_id.insert(client_id);
    //     }
        
    }
    return 0;
}

int ServerConnection::DisplayClientsData(){
    while(1){
        for (int i = 0; i < recieved_clients_id.size();i++){
            std::string keyToFind = recieved_clients_id[i];
            if (datalayout_map.find(keyToFind) == datalayout_map.end()) {
                // QWidget *data_widget = new QWidget;
                // data_widget->setStyleSheet("background-color: #CBCACA;");
                // DataLayout *layer = new DataLayout(data_widget);
                // data_widget->setLayout(layer->main_hlayout); // Set the layout of data_widget
                // ui->servers_layout->addWidget(data_widget); // Add data_widget to the servers_layout
                // datalayout_map[recieved_clients_id[i]] = layer;
                std::cout << "call to addDataLayer" << std::endl;
            }
        }
        
        for (int i = 0; i < recieved_clients_id.size();i++){
            datalayout_map[recieved_clients_id[i]].SetLabels(free_ram_map[recieved_clients_id[i]].back(),
                                                            total_ram_map[recieved_clients_id[i]].back(),
                                                            buffer_ram_map[recieved_clients_id[i]].back(),
                                                            free_space_map[recieved_clients_id[i]].back(),
                                                            total_space_map[recieved_clients_id[i]].back(),
                                                            cpu_usage_map[recieved_clients_id[i]].back());

            //datalayout_map[recieved_clients_id[i]].DrawCharts() // ICI faire la fonction 
        }
    }
}

// Fonction pour extraire une valeur de type double entre guillemets
double ServerConnection::extractDouble(const std::string& json, const std::string& key) {
    std::size_t pos = json.find(key);
    if (pos == std::string::npos) {
        throw std::runtime_error("Key not found");
    }
    pos += key.length();
    pos = json.find_first_of("0123456789.-", pos);
    std::size_t end_pos = json.find_first_not_of("0123456789.-", pos);
    std::string value_str = json.substr(pos, end_pos - pos);
    return std::stod(value_str);
}

// Fonction pour extraire une valeur de type string entre guillemets
std::string ServerConnection::extractString(const std::string& json, const std::string& key) {
    std::size_t pos = json.find(key);
    if (pos == std::string::npos) {
        throw std::runtime_error("Key not found");
    }
    pos += key.length();
    pos = json.find("\"", pos) + 1;
    std::size_t end_pos = json.find("\"", pos);
    return json.substr(pos, end_pos - pos);
}











