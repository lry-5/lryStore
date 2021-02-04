#ifndef GAMEHELPER_H
#define GAMEHELPER_H
//#include "game.h"
#include "config.h"
#include "plant.h"
#include "bullet.h"
class Game;
class GameHelper:public QObject
{
    Q_OBJECT
    Game* game;
public:
    GameHelper(Game* g);
    Plant* whichPlant(int row,int col);
    void putZmbs();

    void setCyclePut(int tmp);

    QPoint posAlignBottom(const QRect &destRect,const QSize &srcSize);
    QPoint posAlignCenter(const QRect &destRect,const QSize &srcSize);
    QPoint posAlignTop(const QRect &destRect,const QSize &srcSize);
    bool isPosInRect(const QPoint& pos,const QRect& rect);

    QPoint posWhiteCell(bool add);
    int findPtrId(QList<ObjMov*> &list,void *ptr);
    char checkCrash(const QLabel& label0,const QLabel& label1,char strict=1);
    std::pair<int,int> rowAndCol(bool center=1,int x=-1,int y=-1);
private:
    QTimer tmrPut;
    int zmbCnt;
    int cyclePut;
};

#endif // GAMEHELPER_H
