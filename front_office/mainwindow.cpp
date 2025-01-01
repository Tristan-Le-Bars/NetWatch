#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLineEdit"
#include "datalayout.h"
#define PORT 9002

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);
    ui->mainLayout->addWidget(ui->scrollArea);
    ui->scrollAreaWidgetContents->setLayout(ui->servers_layout);

    connect(ui->test_button, &QPushButton::clicked, this, &MainWindow::AddDataLayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::ConnectToServer(){
    return 0;
}

int MainWindow::GetClients(){
    // create the widgets displaying the informations from the clients
    return 0;
}


int MainWindow::AddDataLayer(){
    DataLayout *layer = new DataLayout;
    ui->servers_layout->addLayout(layer->main_hlayout);
    return 0;
}






























