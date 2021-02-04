/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QPushButton *verify;
    QPushButton *reset;
    QListWidget *listWidget_2;
    QLabel *chooserBgd;
    QPushButton *quit;
    QPushButton *pause;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(913, 593);
        MainWindow->setMinimumSize(QSize(912, 593));
        MainWindow->setMaximumSize(QSize(913, 593));
        MainWindow->setMouseTracking(true);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{background-image:url(../resource/Interface/background0.jpg);background-position:top left;background-repeat:no-repeat;}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMouseTracking(true);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(13, 50, 103, 481));
        listWidget->setMouseTracking(false);
        listWidget->setStyleSheet(QString::fromUtf8("background-color:transparent"));
        verify = new QPushButton(centralWidget);
        verify->setObjectName(QString::fromUtf8("verify"));
        verify->setGeometry(QRect(302, 530, 80, 28));
        reset = new QPushButton(centralWidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(402, 530, 80, 28));
        listWidget_2 = new QListWidget(centralWidget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(187, 88, 440, 381));
        listWidget_2->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        listWidget_2->setViewMode(QListView::IconMode);
        chooserBgd = new QLabel(centralWidget);
        chooserBgd->setObjectName(QString::fromUtf8("chooserBgd"));
        chooserBgd->setGeometry(QRect(160, 30, 465, 554));
        quit = new QPushButton(centralWidget);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setGeometry(QRect(690, 10, 80, 28));
        pause = new QPushButton(centralWidget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setGeometry(QRect(780, 10, 80, 28));
        MainWindow->setCentralWidget(centralWidget);
        listWidget->raise();
        chooserBgd->raise();
        listWidget_2->raise();
        verify->raise();
        reset->raise();
        quit->raise();
        pause->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        verify->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        reset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
        chooserBgd->setText(QString());
        quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        pause->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
