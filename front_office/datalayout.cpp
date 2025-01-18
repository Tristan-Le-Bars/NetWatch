#include "datalayout.h"
#include "QChartView"

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

    free_ram_label->setText("free ram: ");
    buffer_ram_label->setText("buffer ram: ");
    free_space_label->setText("free space: ");
    cpu_usage_label->setText("cpu usage: ");

    free_ram_hlayout->addWidget(free_ram_label);
    free_ram_hlayout->addWidget(free_ram_value);
    free_ram_hlayout->addWidget(total_ram_value);

    buffer_ram_hlayout->addWidget(buffer_ram_label);
    buffer_ram_hlayout->addWidget(buffer_ram_value);
    buffer_ram_hlayout->addWidget(total_ram_value2);

    free_space_hlayout->addWidget(free_space_label);
    free_space_hlayout->addWidget(free_space_value);
    free_space_hlayout->addWidget(total_space_value);

    cpu_usage_hlayout->addWidget(cpu_usage_label);
    cpu_usage_hlayout->addWidget(cpu_usage_value);

    data_vlayout->addWidget(ip_adress);
    data_vlayout->addLayout(free_ram_hlayout);
    data_vlayout->addLayout(buffer_ram_hlayout);
    data_vlayout->addLayout(free_space_hlayout);
    data_vlayout->addLayout(cpu_usage_hlayout);

    cpu_chart_view->setRenderHint(QPainter::Antialiasing);
    cpu_chart_view->setFixedSize(400, 100);

    ram_chart_view->setRenderHint(QPainter::Antialiasing);
    ram_chart_view->setFixedSize(400, 100);

    charts_vlayout->addWidget(cpu_chart_view);
    charts_vlayout->addWidget(ram_chart_view);
    main_hlayout->addLayout(data_vlayout);
    main_hlayout->addLayout(charts_vlayout);

    qDebug() << "test";
}

DataLayout::~DataLayout()
{

}
