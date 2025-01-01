#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QChart"
#include <vector>

#ifndef DATALAYOUT_H
#define DATALAYOUT_H

class DataLayout {
    public:
        DataLayout();
        ~DataLayout();

        QHBoxLayout *main_hlayout = new QHBoxLayout;
    private:

        QVBoxLayout *data_vlayout = new QVBoxLayout;
        QVBoxLayout *charts_vlayout = new QVBoxLayout;

        QHBoxLayout *free_ram_hlayout = new QHBoxLayout;
        QLabel *free_ram_label = new QLabel;
        QLineEdit *free_ram_value = new QLineEdit;
        QLineEdit *total_ram_value = new QLineEdit;
        std::vector<std::string> free_ram_value_history;
        QChart *free_ram_chart = new QChart;


        QHBoxLayout *buffer_ram_hlayout = new QHBoxLayout;
        QLabel *buffer_ram_label = new QLabel;
        QLineEdit *buffer_ram_value = new QLineEdit;
        QLineEdit *total_ram_value2 = new QLineEdit;
        std::vector<std::string> buffer_ram_value_history;
        QChart *buffer_ram_chart = new QChart;



        QHBoxLayout *free_space_hlayout = new QHBoxLayout;
        QLabel *free_space_label = new QLabel;
        QLineEdit *free_space_value = new QLineEdit;
        QLineEdit *total_space_value = new QLineEdit;
        std::vector<std::string> free_space_value_history;
        QChart *free_space_chart = new QChart;


        // QHBoxLayout *available_space_hlayout = new QHBoxLayout;
        // QLabel *available_space_label = new QLabel;
        // QLineEdit *available_space_value = new QLineEdit;

        QHBoxLayout *cpu_usage_hlayout = new QHBoxLayout;
        QLabel *cpu_usage_label = new QLabel;
        QLineEdit *cpu_usage_value = new QLineEdit;
        std::vector<std::string> cpu_usage_value_history;
        QChart *cpu_usage_chart = new QChart;
};

#endif // DATALAYOUT_H
