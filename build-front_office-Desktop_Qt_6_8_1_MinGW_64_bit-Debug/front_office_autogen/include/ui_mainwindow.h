/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *test_button;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *servers_layout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(673, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 20, 80, 24));
        test_button = new QPushButton(centralwidget);
        test_button->setObjectName("test_button");
        test_button->setGeometry(QRect(130, 20, 80, 24));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 60, 631, 781));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(horizontalLayoutWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 627, 777));
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 651, 781));
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 631, 781));
        servers_layout = new QVBoxLayout(verticalLayoutWidget);
        servers_layout->setObjectName("servers_layout");
        servers_layout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        test_button->setText(QCoreApplication::translate("MainWindow", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
