#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include "datalayout.h"
#include "serverconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        int GetClients();

        std::map<std::string, DataLayout*> datalayout_map;
        Ui::MainWindow *ui;
        QThread *serverThread;
        //ServerConnection *conn;

    public slots:
        int AddDataLayer(const QString& client_id);
        int handleDataReceived(const QString& client_id, double free_ram, double total_ram, double buffer_ram, double total_space, double free_space, double cpu_usage);

    private slots:
        int ConnectToServer();

};
#endif // MAINWINDOW_H
