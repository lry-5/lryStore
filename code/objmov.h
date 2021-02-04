#ifndef OBJMOV_H
#define OBJMOV_H
#include <QPropertyAnimation>
#include "config.h"

//class ObjMov:public QLabel
//{
//public:
//    QPropertyAnimation *animation;
//    ObjMov(QWidget* parent=nullptr);
//    ~ObjMov();
//    void initInfo(const QPoint &posStart,const QPoint &posEnd,int dur,const QString& qstr);
//protected:
//    QPixmap pix;
//    QMovie* qmv;
//};
class Game;

//class Arc{//抛物线
//public:
//    int x2y(int x);

//    QRect rect;
//};

class ObjMov:public QLabel
{
    Q_OBJECT
public:
    ObjMov(QWidget* parent=nullptr);
    ~ObjMov();
    void initInfo(int cycle=20,const QString& qstr="",const QString& qstr1="");
    void movePos();
    char isAlive();
    virtual void act();

    static Game* game;
    QTimer tmr;

protected:
    int hp;
    char movType;
    QPixmap pix;
    QMovie* qmv;
};

class ObjMovTmp:public ObjMov{
public:
    ObjMovTmp(QWidget* parent=nullptr);
    void deTime();

protected:
    int yMax,timeCnt;
//    int yMax,id,timeCnt;
};

class Sun:public ObjMovTmp{
public:
    Sun(const QRect& rect,QWidget* parent=nullptr);
    void clr();
    void act();

};

//class Head:public ObjMovTmp{
//public:
//    Head(const QRect& rect,QWidget* parent=nullptr);
//    void act();
//};

#endif // OBJMOV_H
