#include "datalayout.h"
#include "QChartView"

DataLayout::DataLayout() {
    QChartView *chart_view = new QChartView(chart);

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

    data_vlayout->addLayout(free_ram_hlayout);
    data_vlayout->addLayout(buffer_ram_hlayout);
    data_vlayout->addLayout(free_space_hlayout);
    data_vlayout->addLayout(cpu_usage_hlayout);

    chart_view->setRenderHint(QPainter::Antialiasing);
    chart_view->setFixedSize(400, 200);

    charts_vlayout->addWidget(chart_view);
    main_hlayout->addLayout(data_vlayout);
    main_hlayout->addLayout(charts_vlayout);
    qDebug() << "test";
}
