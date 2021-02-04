#include "bullet.h"
#include "zombie.h"
#include "game.h"
//Bullet::Bullet(const QPoint &posStart, const QPoint &posEnd, int dur, QWidget *parent):
//    ObjMov (posStart,posEnd,dur,parent)
//{

////    animation.setStartValue(posStart);
////    animation.setEndValue(QPoint(parent->width(),posStart.y()));
////    animation.setDuration(dur);
////    animation.start();
//}

//Pea::Pea(const QPoint &posStart, int dur, QWidget *parent):
//    Bullet (posStart,dur,parent)
//{
////   pix=QPixmap(pltFilePre+"PB01.gif");
//   pix.load(pltFilePre+"PB01.gif");
//   resize(pix.size());
//   setPixmap(pix);
//}

Bullet::Bullet(QWidget *parent):ObjMov (parent)
{
    hp=1;
//    hitPower=1;
//    row=(game->gameHelper.rowAndCol(1,x(),y())).first;
//    id=game->gameHelper.findPtrId(game->bullets[row],this);
}

ObjMov* Bullet::searchCrash()
{
//    std::pair<int,int> pr=game->gameHelper.rowAndCol(1,x()+width(),y()+height());
//    if(game->plants[pr.first][pr.second])
//        raise();
    raise();
    QList<ObjMov*> &zmbLs=game->zombies[row];
    for(ObjMov* objmov:zmbLs){
//        ObjMov* objmov=zmbLs[i];
        if(!objmov)
            continue;
        if(game->gameHelper.checkCrash(*this,*objmov,0)){
            hp=0;
            qDebug()<<"blt hit zmb";
            ((Zombie*)objmov)->inHp(-hitPower);
            return objmov;
        }
    }
//    for(int i=0;i<zmbLs.size();i++){
//        //        ObjMov* objmov=zmbLs[i];
//        if(!zmbLs[i]->isAlive())
//            continue;
//        if(game->gameHelper.checkCrash(*this,*zmbLs[i],0)){
//            hp=0;
//            qDebug()<<"blt hit zmb";
//            ((Zombie*)zmbLs[i])->inHp(-hitPower);
//            return i;
//        }
//    }
    return nullptr;
}

void Bullet::clr()
{
    QList<ObjMov*>& bltLs=game->bullets[row];
    int id=game->gameHelper.findPtrId(bltLs,this);
    if(x()>=MAX_W||hp<=0){
        if(id>=0){
            bltLs.erase(bltLs.begin()+id);
            qDebug()<<"erase pea row id:"<<row<<' '<<id;
        }
        delete this;
    }
}

Pea::Pea(const QPoint &posStart,int cycle, QWidget *parent):
    Bullet(parent)
{
    initInfo(cycle,pltFilePre+"PB01.gif");
    move(posStart);
    row=(game->gameHelper.rowAndCol(1,x(),y())).first;
//    qDebug()<<"pea row:"<<row;
//    id=game->gameHelper.findPtrId(game->bullets[row],this);
    movType=RIGHT;
    hitPower=1;
}

void Pea::act()
{
//    qDebug()<<"pea act";
//    row=(game->gameHelper.rowAndCol(1,x(),y())).first;
//    QList<ObjMov*>& bltLs=game->bullets[row];
//    id=game->gameHelper.findPtrId(blts,this);
//    std::pair<int,int> pr=game->gameHelper.rowAndCol(1,x()+ZMB_BORDER,y()+height());

    searchCrash();
    clr();
}

//void Pea::movePos()
//{

//}

SnowPea::SnowPea(const QPoint &posStart,int cycle, QWidget *parent):
    Bullet(parent)
{
    initInfo(cycle,pltFilePre+"PB-10.gif");
    move(posStart);
    row=(game->gameHelper.rowAndCol(1,x(),y())).first;
    movType=RIGHT;
    hitPower=1;
}

void SnowPea::act()
{
//    qDebug()<<"snow pea act";
    ObjMov* objmov=searchCrash();
    if(objmov){
        ((Zombie*)objmov)->setCold(1);
    }
    clr();
}


