#include "datalayout.h"
#include "QChartView"

DataLayout::DataLayout() {
    QChartView *free_ram_chart_view = new QChartView(free_ram_chart);
    QChartView *buffer_ram_chart_view = new QChartView(buffer_ram_chart);
    QChartView *free_space_chart_view = new QChartView(free_space_chart);
    QChartView *cpu_usage_chart_view = new QChartView(cpu_usage_chart);

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

    free_ram_chart_view->setRenderHint(QPainter::Antialiasing);
    buffer_ram_chart_view->setRenderHint(QPainter::Antialiasing);
    free_space_chart_view->setRenderHint(QPainter::Antialiasing);
    cpu_usage_chart_view->setRenderHint(QPainter::Antialiasing);

    charts_vlayout->addWidget(free_ram_chart_view);
    charts_vlayout->addWidget(buffer_ram_chart_view);
    charts_vlayout->addWidget(free_space_chart_view);
    charts_vlayout->addWidget(cpu_usage_chart_view);

    main_hlayout->addLayout(data_vlayout);
    main_hlayout->addLayout(charts_vlayout);
    qDebug() << "test";
}
