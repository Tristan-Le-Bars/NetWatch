#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define PORT 9002

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect();
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

