#ifndef GAME_H
#define GAME_H

//#include <QWidget>
#include <QThread>
#include <QPushButton>
#include "config.h"
#include "plant.h"
#include "bullet.h"
#include "zombie.h"
#include "plantcard.h"
#include "gamehelper.h"

//class ThreadBlt:public QThread{
//public:
//    ThreadBlt(int interval=5,QWidget* parent=nullptr);
//    void run();

////    static QList<ObjMov*> *bullets;
//    QList<ObjMov*> bullets[ROW_NUM];
//    int cycle;
//};

class Game:public QObject
{
    Q_OBJECT

public:
    Game(QWidget*parent=nullptr);
    ~Game();
//    void loadPix();
//    void fun(int row,int id);
    void initInfo();
    char findSun();
    char clicked(char sure);
//    void plantsAct();
//    void zombiesAct();
    void bulletsAct();
    void setStart(bool sure);
    void end();

    void clrList(QList<ObjMov*> &objList,int id=-1);
    void clrObjects();

    char plantHandle(bool add);
//    void zombieHandle(bool add);
//    void bulletHandle(bool add);

    void putSysSun();
    void updateCursorPix();

    friend GameHelper;

    GameHelper gameHelper;
    Plant* plants[ROW_NUM][COL_NUM];
    QList<ObjMov*> zombies[ROW_NUM];
    QList<ObjMov*> bullets[ROW_NUM];
    QList<ObjMov*> suns;//heads;

//    ThreadBlt* thrBlt;

    QWidget* mainWin;
    QPoint cursorPos;
    int curPltId;
    int sunNum;
    char state;

private:
//    GameHelper gameHelper;
    QPixmap cursorPixs[NUM_PLANT];

//    Plant* plants[ROW_NUM][COL_NUM];
////    QList<Zombie> zombies[ROW_NUM];
//    QList<ObjMov*> bullets[ROW_NUM];

    QTimer tmrSys,tmrZmb,tmrBlt;
    QPoint shovelBegin;
    QLabel *cursorPlt;
    QLabel *shovel;
    QLabel *shovelBack;
    QLabel *sunBack;
    QLabel *sunNumTxt;
    QLabel *whiteCell;
    QLabel *endLab;
//    QPushButton *button;
    bool showCursorImg;
//    int sunNum;
//    int curPltId;
};

#endif // GAME_H
