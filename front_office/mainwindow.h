#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datalayout.h"

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
        Ui::MainWindow *ui;

        int ConnectToServer();
        int GetClients();

        std::map<std::string, DataLayout> datalayout_map;

    public slots:
        int AddDataLayer();

};
#endif // MAINWINDOW_H
