#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QtCharts/QtCharts"
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef DATALAYOUT_H
#define DATALAYOUT_H

class DataLayout : public QWidget {
    Q_OBJECT
    public:
        DataLayout(QWidget *parent = nullptr);
        ~DataLayout();
        int DrawCharts();

        int SetLabels(double free_ram, double total_ram, double buffer_ram, double free_space, double total_space, double cpu_usage);

        QHBoxLayout *main_hlayout;
    private:
        std::string client_id;
        QLabel *ip_adress;

        QVBoxLayout *data_vlayout;
        QVBoxLayout *charts_vlayout;
        QChart *cpu_chart;
        QChart *ram_chart;
        QChartView *cpu_chart_view;
        QChartView *ram_chart_view;

        QHBoxLayout *free_ram_hlayout;
        QLabel *free_ram_label;
        QLabel *free_ram_value;
        QLabel *total_ram_value;
        std::vector<double> free_ram_value_history;


        QHBoxLayout *buffer_ram_hlayout;
        QLabel *buffer_ram_label;
        QLabel *buffer_ram_value;
        QLabel *total_ram_value2;
        std::vector<double> buffer_ram_value_history;


        QHBoxLayout *free_space_hlayout;
        QLabel *free_space_label;
        QLabel *free_space_value;
        QLabel *total_space_value;
        std::vector<double> free_space_value_history;

        QHBoxLayout *cpu_usage_hlayout;
        QLabel *cpu_usage_label;
        QLabel *cpu_usage_value;
        std::vector<double> cpu_usage_value_history;

        int client_socket; // socket qui representera une connection entrante
        int valread;
        struct sockaddr_in server_address;
        socklen_t server_addrlen = sizeof(server_address);
        char client_ip[INET_ADDRSTRLEN];
        char buffer[1024] = {0};
};

#endif // DATALAYOUT_H
