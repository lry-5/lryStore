#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QListWidget>
#include <QWidget>
#include <QPair>
#include <functional>
#include "config.h"

//class PlantCard;
//class MyTimer:public QTimer{
//    Q_OBJECT

//public:
//    MyTimer(PlantCard* card,QWidget*parent=nullptr);
//    void myslot();

//    PlantCard* pltcard;
//};

class Game;
class PlantCard:public QObject,public QListWidgetItem
{//hard in connect signal and slots
    Q_OBJECT
public:
    PlantCard(QListWidget* parent=nullptr,int pltId=0);
    ~PlantCard();
    int getPltId();
    QString getCardInfo(int pltId);
    void addRatio();
    void updateImg();
    void setChecked(char c=0);
    char isChecked();

//    static void setState(char x);
//    static void setSunNum(int x);

    static Game* game;
private:
    static char state;//
    static int curSunNum;
    static const int coolDur[NUM_PLANT];
    char checked;
    int plantId;
//    int coolCycle;
    double ratio;
//    MyTimer mytmr;
    QPixmap activePix;
    QPixmap inactivePix;
    QPixmap coolPix;
    QPainter painter;
    QTimer timer;

};

#endif // PLANTCARD_H
