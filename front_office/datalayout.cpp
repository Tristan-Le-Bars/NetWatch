#include "datalayout.h"
#include "QChartView"
#include "iostream"
#include <deque>

DataLayout::DataLayout(QWidget *parent)
    : QWidget(parent)

{
    main_hlayout = new QHBoxLayout;

    ip_adress = new QLabel;

    //data_widget = new QWidget;
    data_vlayout = new QVBoxLayout;
    charts_vlayout = new QVBoxLayout;
    cpu_chart = new QChart;
    ram_chart = new QChart;
    storage_chart = new QChart;
//    cpu_chart->legend()->setVisible(false);
//    ram_chart->legend()->setVisible(false);
//    storage_chart->legend()->setVisible(false);
    free_ram_hlayout = new QHBoxLayout;
    free_ram_label = new QLabel;
    free_ram_value = new QLabel;
    total_ram_value = new QLabel;

    buffer_ram_hlayout = new QHBoxLayout;
    buffer_ram_label = new QLabel;
    buffer_ram_value = new QLabel;
    total_ram_value2 = new QLabel;

    free_space_hlayout = new QHBoxLayout;
    free_space_label = new QLabel;
    free_space_value = new QLabel;
    total_space_value = new QLabel;
    cpu_usage_hlayout = new QHBoxLayout;
    cpu_usage_label = new QLabel;
    cpu_usage_value = new QLabel;
    cpu_chart_view = new QChartView(cpu_chart);
    ram_chart_view = new QChartView(ram_chart);
    storage_chart_view = new QChartView(storage_chart);

    ip_adress->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_value->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    total_ram_value->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_hlayout->setSpacing(10);
    buffer_ram_hlayout->setSpacing(10);
    free_space_hlayout->setSpacing(10);
    cpu_usage_hlayout->setSpacing(10);
    ip_adress->setText("ip adress");
    free_ram_label->setText("free ram: ");
    buffer_ram_label->setText("buffer ram: ");
    free_space_label->setText("free space: ");
    cpu_usage_label->setText("cpu usage: ");
    
    cpu_chart_view->setRenderHint(QPainter::Antialiasing);
    cpu_chart_view->setFixedSize(400, 400);

    ram_chart_view->setRenderHint(QPainter::Antialiasing);
    ram_chart_view->setFixedSize(400, 400);

    storage_chart_view->setRenderHint(QPainter::Antialiasing);
    storage_chart_view->setFixedSize(400, 400);
    cpu_usage_hlayout->addWidget(cpu_usage_label);
    cpu_usage_hlayout->addWidget(cpu_usage_value);
    cpu_usage_hlayout->addWidget(cpu_chart_view);

    free_ram_hlayout->addWidget(free_ram_label);
    free_ram_hlayout->addWidget(free_ram_value);
    free_ram_hlayout->addWidget(total_ram_value);
    free_ram_hlayout->addWidget(ram_chart_view);

    // buffer_ram_hlayout->addWidget(buffer_ram_label);
    // buffer_ram_hlayout->addWidget(buffer_ram_value);
    // buffer_ram_hlayout->addWidget(total_ram_value2);

    free_space_hlayout->addWidget(free_space_label);
    free_space_hlayout->addWidget(total_space_value);
    free_space_hlayout->addWidget(free_space_value);
    free_space_hlayout->addWidget(storage_chart_view);

    data_vlayout->setSpacing(10);
    data_vlayout->setContentsMargins(0, 0, 0, 0);
    data_vlayout->addWidget(ip_adress);
    data_vlayout->addLayout(cpu_usage_hlayout);
    data_vlayout->addLayout(free_ram_hlayout);
    data_vlayout->addLayout(free_space_hlayout);
    // data_vlayout->addLayout(buffer_ram_hlayout);
    main_hlayout->addLayout(data_vlayout);
    main_hlayout->addLayout(charts_vlayout);


    ram_chart->addSeries(&free_ram_series);
    cpu_chart->addSeries(&cpu_usage_series);
    storage_chart->addSeries(&free_space_series);

    std::cout << "datalayout initialized" << std::endl;
}

DataLayout::~DataLayout()
{

}

int DataLayout::SetLabels(double free_ram, double total_ram, double buffer_ram, double free_space, double total_space, double cpu_usage){
    QString buffer_qstring;

    buffer_qstring = QString::number(free_ram, 'f', 4);
    free_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(total_ram, 'f', 4);
    total_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(buffer_ram, 'f', 4);
    buffer_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(free_space, 'f', 4);
    free_space_value->setText(buffer_qstring);

    buffer_qstring = QString::number(total_space, 'f', 4);
    total_space_value->setText(buffer_qstring);

    std::cout << "cpu_usage in setlabels = " << cpu_usage << std::endl;
    buffer_qstring = QString::number(cpu_usage, 'f', 4);
    cpu_usage_value->setText(buffer_qstring);

    return 0;
}

int DataLayout::DrawCharts(){
    // convert vectors to LineSeries
    
    for (size_t i = 0; i < free_ram_deque.size(); ++i) {
        double ram_x = static_cast<double>(i);
        double ram_y = free_ram_deque[i];

        double space_x = static_cast<double>(i);
        double space_y = free_space_deque[i];

        double cpu_x = static_cast<double>(i);
        double cpu_y = cpu_usage_deque[i];
        
        free_ram_series.append(ram_x, ram_y);
        free_space_series.append(space_x, space_y);
        cpu_usage_series.append(cpu_x, cpu_y);
    }

    cpu_chart_view->update();
    ram_chart_view->update();
    storage_chart_view->update();

//     ram_chart->addSeries(&free_ram_series);
//     cpu_chart->addSeries(&cpu_usage_series);
//     storage_chart->addSeries(&free_space_series);
    //draw chart
    return 0;
}
