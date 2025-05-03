#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QtCharts/QtCharts"
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <deque>

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
        
        void updateDataDeque(double free_ram, double free_space, double cpu_usage){
            free_ram_deque.push_back(free_ram);
            free_space_deque.push_back(free_space);
            cpu_usage_deque.push_back(cpu_usage);
    
            if (free_ram_deque.size() > 15){
                free_ram_deque.pop_front();
                free_space_deque.pop_front();
                cpu_usage_deque.pop_front();
            }
        }
    private:
        std::string client_id;

        std::deque<double> free_ram_deque;
        std::deque<double> free_space_deque;
        std::deque<double> cpu_usage_deque;


        QLabel *ip_adress;

        QVBoxLayout *data_vlayout;
        QVBoxLayout *charts_vlayout;
        
        QChart *cpu_chart;
        QChart *ram_chart;
        QChart *storage_chart;

        QLineSeries free_ram_series;
        QLineSeries free_space_series;
        QLineSeries cpu_usage_series;

        QChartView *cpu_chart_view;
        QChartView *ram_chart_view;
        QChartView *storage_chart_view;

        QHBoxLayout *free_ram_hlayout;
        QLabel *free_ram_label;
        QLabel *free_ram_value;
        QLabel *total_ram_value;
        QValueAxis *axisY_ram;
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
        QValueAxis *axisY_storage;
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
