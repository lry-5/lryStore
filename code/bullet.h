#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include "objmov.h"
//class Bullet:public ObjMov
//{
//public:
////    QPropertyAnimation animation;
//    Bullet(const QPoint &posStart,const QPoint &posEnd, int dur,QWidget* parent=nullptr);
//protected:
//    QPixmap pix;
//};

//class Pea:public Bullet{
//public:
//    Pea(const QPoint &posStart,const QPoint &posEnd,int dur=50,QWidget* parent=nullptr);
//};

//class SnowPea:public Bullet{
//public:
//    SnowPea(const QPoint &posStart,const QPoint &posEnd,int dur=50,QWidget* parent=nullptr);
//};

class Bullet:public ObjMov{
public:
    Bullet(QWidget* parent=nullptr);
    ObjMov* searchCrash();
    void clr();
protected:
    int row;
    int hitPower;
};

class Pea:public Bullet{
public:
    Pea(const QPoint &posStart,int cycle=100,QWidget* parent=nullptr);
//    void movePos();
    void act();
};

class SnowPea:public Bullet{
public:
    SnowPea(const QPoint &posStart,int cycle=100,QWidget* parent=nullptr);
//    void movePos();
    void act();
};

#endif // BULLET_H
