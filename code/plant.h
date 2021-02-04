#ifndef PLANT_H
#define PLANT_H
#include <QLabel>
//#include <QMap>
#include "config.h"
#include "objmov.h"
class Game;

class Plant:public QLabel
{
    Q_OBJECT
public: 
    Plant(QWidget* parent=nullptr);
    ~Plant();
    void initInfoPlt(int r,int c,const QString& qstr);
    virtual void act();
    virtual void inHp(int x=-1);
    char isAlive();
    void clr();
    QTimer tmr;
    static Game *game;

protected:
    int row,col;
    int hp,hitPower;
//    float coolTime;
    QMovie* qmv;

};

class SunFlower:public Plant{
public:
    SunFlower(int r,int c,QWidget* parent=nullptr);
    void act();

    static QString dir;
};

class PeaShooter:public Plant{
public:
    PeaShooter(int r,int c,QWidget* parent=nullptr);
    void act();

    static QString dir;
};

class SnowShooter:public Plant{
public:
    SnowShooter(int r,int c,QWidget* parent=nullptr);

    void act();
    static QString dir;
};

class DoubleShooter:public Plant{
public:
    DoubleShooter(int r,int c,QWidget* parent=nullptr);

    void act();
    static QString dir;
};

class WallNut:public Plant{
public:
    WallNut(int r,int c,QWidget* parent=nullptr);
    ~WallNut();
//    void act();
    void inHp(int x=-1);
    static QString dir;
private:
    QMovie *cracked1,*cracked2;
};

class Cherry:public Plant{
public:
    Cherry(int r,int c,QWidget* parent=nullptr);
    ~Cherry();
    void fire(int frameId);
    void clean(int frameId);
    static QString dir;
private:
//    QPixmap pix;
    QMovie *boom;
};

//class Potato:public Plant{
//public:
//    Potato(int x,int y,QWidget* parent=nullptr);


//    static QString dir;
//};

#endif // PLANT_H
