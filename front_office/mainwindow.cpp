#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLineEdit"
#include "datalayout.h"
#include "serverconnection.h"
#include <thread>
#include <iostream>

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
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::ConnectToServer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::ConnectToServer(){
    ServerConnection *conn = new ServerConnection();
    if (conn->EstablishConnection() != 0){
        std::cout << "Error while establishing connection." << std::endl;
        return -1;
    }
    else{
        std::thread reader_thread(&ServerConnection::ReadFromServer, conn);
        reader_thread.detach();
    }
    return 0;
}

int MainWindow::GetClients(){
    // create the widgets displaying the informations from the clients
    return 0;
}


int MainWindow::AddDataLayer(){
    QWidget *data_widget = new QWidget;
    data_widget->setStyleSheet("background-color: #CBCACA;");

    DataLayout *layer = new DataLayout(data_widget);
    data_widget->setLayout(layer->main_hlayout); // Set the layout of data_widget

    ui->servers_layout->addWidget(data_widget); // Add data_widget to the servers_layout

    return 0;
}






























