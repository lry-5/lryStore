#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "config.h"
#include "objmov.h"
class Game;
//class Head:public ObjMovTmp{
//public:
//    Head(QWidget* parent=nullptr);
//    void act();
//};

class Zombie:public ObjMov
{
    Q_OBJECT
public:
    Zombie(int r,QWidget* parent=nullptr);
    ~Zombie();
    void setCold(char cold=1);
    void setCommon();
    void setFired();
    void putHead();
    void clean(int frameId);
    void setAttack(char sure);
    void hitPlt();
    void inHp(int x);

    char isEnd();
    void act();

    QTimer tmrHit;
    QMovie* attackMv;

signals:
    void gameover();
protected:
    int row,rowTar,colTar;
    int hitPower;
    char cold,end,hiting;
    QString dir;
    QMovie* dieMv;
    QLabel* headLab;
    QMovie* headMv;
    QLabel* iceLab;

//    QMovie* attack;
};

class CommonZmb:public Zombie{
//    Q_OBJECT
public:
    CommonZmb(int r,QWidget* parent=nullptr);

//    static QString dir;
};

class ConeZmb:public Zombie{

public:
    ConeZmb(int r,QWidget* parent=nullptr);

//    void inHp(int x);
};

class BucketZmb:public Zombie{
public:
    BucketZmb(int r,QWidget* parent=nullptr);
};

#endif // ZOMBIE_H
