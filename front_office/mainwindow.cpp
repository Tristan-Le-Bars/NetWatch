#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLineEdit"
#include "QThread"
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

    //connect(ui->test_button, &QPushButton::clicked, this, &MainWindow::AddDataLayer);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::ConnectToServer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::ConnectToServer(){
    ServerConnection *conn = new ServerConnection();
    conn->EstablishConnection();
    serverThread = new QThread(this);

    // Déplacer le ServerConnection dans un thread séparé
    
    connect(serverThread, &QThread::started, conn, &ServerConnection::ReadFromServer);
    connect(conn, &ServerConnection::dataReceived, this, &MainWindow::handleDataReceived);
    connect(conn, &ServerConnection::addDataLayerRequested, this, &MainWindow::AddDataLayer);
    //connect(conn, &ServerConnection::finished, serverThread, &QThread::quit);
    connect(serverThread, &QThread::finished, serverThread, &QThread::deleteLater);
    
    conn->moveToThread(serverThread);

    serverThread->start();  // Démarre le thread
    return 0;
}

int MainWindow::GetClients(){
    // create the widgets displaying the informations from the clients
    return 0;
}


int MainWindow::AddDataLayer(const QString& client_id){
    std::cout << "call AddDataLayer" << std::endl;
    QWidget *data_widget = new QWidget;
    data_widget->setStyleSheet("background-color: #CBCACA;");
    DataLayout *layer = new DataLayout(data_widget);
    data_widget->setLayout(layer->main_hlayout); // Set the layout of data_widget
    ui->servers_layout->addWidget(data_widget); // Add data_widget to the servers_layout
    datalayout_map[client_id.toStdString()] = layer;
    std::cout << "new data layout created" << std::endl;
    return 0;
}

int MainWindow::handleDataReceived(const QString& client_id, double free_ram, double total_ram, double buffer_ram, double total_space, double free_space, double cpu_usage) {
    // Mettre à jour l'UI avec les données reçues
    std::cout << "handle data recieved" << std::endl;
    datalayout_map[client_id.toStdString()]->SetLabels( free_ram,  total_ram,  buffer_ram,  total_space,  free_space,  cpu_usage);
    std::cout << "Data received for " << client_id.toStdString() << std::endl;
    return 0;
}





























