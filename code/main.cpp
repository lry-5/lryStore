#include "mainwindow.h"
#include <QApplication>
#include <QFile>
//#include <iostream>
//#include <fstream>
//using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    w.ui->listWidget->hide();

//    Music music;
//    music.show();
//    QFile fileR("../resource/text/todo0.txt");
//    if (!fileR.open(QIODevice::ReadOnly | QIODevice::Text))
//        return -1;
//    QTextStream in(&fileR);
//    in.setCodec("utf-8");
//    QString str=in.readLine();
//    qDebug()<<str;
//    std::ofstream ofstr("../resource/text/todo0.txt",ios::out);
//    ofstr<<"hhh";
//    if(!ofstr)
//        qDebug()<<"failed";
//    ofstr.close();
    return a.exec();
}
