#include "datalayout.h"
#include "QChartView"
#include "iostream"
#include <deque>

DataLayout::DataLayout(QWidget *parent)
    : QWidget(parent)

{
    std::cout << "test1" << std::endl;
    main_hlayout = new QHBoxLayout;

    client_id_layout = new QHBoxLayout;
    client_id_label = new QLabel;
    client_id_value = new QLabel;

    //data_widget = new QWidget;
    data_vlayout = new QVBoxLayout;
    charts_vlayout = new QVBoxLayout;
    cpu_chart = new QChart;
    ram_chart = new QChart;
    storage_chart = new QChart;
    cpu_chart->legend()->setVisible(false);
    ram_chart->legend()->setVisible(false);
    storage_chart->legend()->setVisible(false);
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
    std::cout << "test2" << std::endl;

    //QValueAxis *axisX = new QValueAxis();
    

    client_id_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_value->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    total_ram_value->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    free_ram_hlayout->setSpacing(10);
    buffer_ram_hlayout->setSpacing(10);
    free_space_hlayout->setSpacing(10);
    cpu_usage_hlayout->setSpacing(10);
    client_id_label->setText("ID : ");
    free_ram_label->setText("ram usage: ");
    //buffer_ram_label->setText("buffer ram: ");
    free_space_label->setText("free space: ");
    cpu_usage_label->setText("cpu usage: ");
    std::cout << "test3" << std::endl;
    
    cpu_chart_view->setRenderHint(QPainter::Antialiasing);
    cpu_chart_view->setFixedSize(600, 200);

    ram_chart_view->setRenderHint(QPainter::Antialiasing);
    ram_chart_view->setFixedSize(600, 200);

    storage_chart_view->setRenderHint(QPainter::Antialiasing);
    storage_chart_view->setFixedSize(600, 200);

    std::cout << "test4" << std::endl;
    client_id_layout->addWidget(client_id_label);
    client_id_layout->addWidget(client_id_value);
    std::cout << "test5" << std::endl;


    cpu_usage_hlayout->addWidget(cpu_usage_label);
    cpu_usage_hlayout->addWidget(cpu_usage_value);
    cpu_usage_hlayout->addWidget(cpu_chart_view);

    free_ram_hlayout->addWidget(free_ram_label);
    free_ram_hlayout->addWidget(free_ram_value);
    free_ram_hlayout->addWidget(total_ram_value);
    free_ram_hlayout->addWidget(ram_chart_view);

    free_space_hlayout->addWidget(free_space_label);
    free_space_hlayout->addWidget(free_space_value);
    free_space_hlayout->addWidget(total_space_value);
    free_space_hlayout->addWidget(storage_chart_view);

    data_vlayout->setSpacing(10);
    data_vlayout->setContentsMargins(0, 0, 0, 0);
    data_vlayout->addLayout(client_id_layout);
    data_vlayout->addLayout(cpu_usage_hlayout);
    data_vlayout->addLayout(free_ram_hlayout);
    data_vlayout->addLayout(free_space_hlayout);
    // data_vlayout->addLayout(buffer_ram_hlayout);
    main_hlayout->addLayout(data_vlayout);
    main_hlayout->addLayout(charts_vlayout);


    ram_chart->addSeries(&free_ram_series);
    cpu_chart->addSeries(&cpu_usage_series);
    storage_chart->addSeries(&free_space_series);
    
    // Création et ajout des axes
    QValueAxis *axisX_cpu = new QValueAxis();
    QValueAxis *axisY_cpu = new QValueAxis();
    axisX_cpu->setRange(0, 14);
    axisY_cpu->setRange(0, 100);
    cpu_chart->addAxis(axisX_cpu, Qt::AlignBottom);
    cpu_chart->addAxis(axisY_cpu, Qt::AlignLeft);
    axisX_cpu->setVisible(false);
    cpu_usage_series.attachAxis(axisX_cpu);

    QValueAxis *axisX_ram = new QValueAxis();
    axisY_ram = new QValueAxis();
    axisX_ram->setRange(0, 14);
    axisY_ram->setRange(0, 100);
    ram_chart->addAxis(axisX_ram, Qt::AlignBottom);
    ram_chart->addAxis(axisY_ram, Qt::AlignLeft);
    axisX_ram->setVisible(false);
    free_ram_series.attachAxis(axisX_ram);

    QValueAxis *axisX_storage = new QValueAxis();
    axisY_storage = new QValueAxis();
    axisX_storage->setRange(0, 14);
    axisY_storage->setRange(0, 100);
    storage_chart->addAxis(axisX_storage, Qt::AlignBottom);
    storage_chart->addAxis(axisY_storage, Qt::AlignLeft);
    free_space_series.attachAxis(axisX_storage);
    free_space_series.attachAxis(axisY_storage);
    axisX_storage->setVisible(false);
    std::cout << "datalayout initialized" << std::endl;
}

DataLayout::~DataLayout()
{

}

int DataLayout::SetLabels(QString client_id, double free_ram, double total_ram, double buffer_ram, double free_space, double total_space, double cpu_usage){
    QString buffer_qstring;

    client_id_value->setText(client_id);

    buffer_qstring = QString::number(total_ram - free_ram, 'f', 4);
    free_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(total_ram, 'f', 4);
    total_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(buffer_ram, 'f', 4);
    buffer_ram_value->setText(buffer_qstring);

    buffer_qstring = QString::number(free_space, 'f', 4);
    free_space_value->setText(buffer_qstring);

    buffer_qstring = QString::number(total_space, 'f', 4);
    total_space_value->setText(buffer_qstring);

    buffer_qstring = QString::number(cpu_usage, 'f', 4);
    cpu_usage_value->setText(buffer_qstring);

    return 0;
}

int DataLayout::DrawCharts(){
    // convert vectors to LineSeries
    free_ram_series.clear();
    free_space_series.clear();
    cpu_usage_series.clear();
    QString total_ram_text = total_ram_value->text();
    QString total_space_text = total_space_value->text();
    bool ok;
    double total_ram = total_ram_text.toDouble(&ok);
    double total_space = total_space_text.toDouble(&ok);
    axisY_ram->setRange(0, total_ram);
    axisY_storage->setRange(0, total_space);
    for (size_t i = 0; i < cpu_usage_deque.size(); ++i) {
        double ram_x = static_cast<double>(i);
        double ram_y = (total_ram - free_ram_deque[i]) * 0.1;

        double space_x = static_cast<double>(i);
        double space_y =  free_space_deque[i];

        double cpu_x = static_cast<double>(i);
        double cpu_y = cpu_usage_deque[i] * 0.01;
        
        free_ram_series.append(ram_x, ram_y);
        free_space_series.append(space_x, space_y);
        cpu_usage_series.append(cpu_x, cpu_y);
    }

    for (const QPointF& point : free_space_series.points()) {
            qDebug() << "Point : (" << point.x() << ", " << point.y() << ")";
        }

    cpu_chart_view->update();
    ram_chart_view->update();
    storage_chart_view->update();
    return 0;
}
