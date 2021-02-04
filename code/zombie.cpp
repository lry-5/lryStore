#include "zombie.h"
#include "game.h"
//Head::Head(QWidget *parent):ObjMovTmp (parent)
//{
//    movType=ARC_R;
//    timeCnt=60;//40个时钟
//    ObjMov::initInfo(QPoint(0,0),15,zmbFilePre+Zombie::dir+"ZombieHead.gif");
//}

//void Head::act()
//{
//    deTime();
//    if(timeCnt<=0){
//        int id=game->gameHelper.findPtrId(game->heads,this);
//        qDebug()<<"clr head"<<id;
//        if(id>=0){
//            game->suns.erase(game->heads.begin()+id);
//        }
//        delete this;
//    }
//}

//QString Zombie::dir="Zombie/";
Zombie::Zombie(int r,QWidget *parent):ObjMov (parent)
{
    hitPower=1;
    hiting=end=cold=0;
    row=r;
    movType=LEFT;
    tmr.start();
    dieMv=nullptr;
    attackMv=nullptr;
    headMv=nullptr;
    iceLab=nullptr;
    tmrHit.setInterval(1000);
    setMouseTracking(1);
//    dir="Zombie/";
//    QPoint pos;
//    QRect rect(MAX_W,row*CELL_H+lawnRect.y(),CELL_W,CELL_H);
//    ObjMov::initInfo(CYCLE_ZMB,"",zmbFilePre+dir+"Zombie.gif");
//    pos=game->gameHelper.posAlignBottom(rect,size());
//    move(pos);

//    attack=new QMovie(zmbFilePre+dir+"ZombieAttack.gif");

//    setStyleSheet("border:4px solid red;");

    QObject::connect(&tmrHit,&QTimer::timeout,this,&Zombie::hitPlt);
    QObject::connect(&tmr,&QTimer::timeout,this,&ObjMov::movePos);
    QObject::connect(this,&Zombie::gameover,game,&Game::end);
//    lostHead=new QMovie(zmbFilePre+dir+"ZombieDie.gif");
//    fired=new QMovie(zmbFilePre+dir+"BoomDie.gif");
    //    ObjMov::initInfo();
//    tmr.start();
}

Zombie::~Zombie()
{
    qDebug()<<"~zmb ";

    delete dieMv;
    dieMv=nullptr;
    delete attackMv;
    attackMv=nullptr;
    delete headMv;
    headMv=nullptr;
}

void Zombie::setCold(char cold)
{
    if(this->cold==cold)
        return;
    this->cold=cold;
    if(cold){
        qDebug()<<"set cold**********";
        tmr.setInterval(CYCLE_COLD);
        pix.load(zmbFilePre+"Zombie/icetrap.gif");
        iceLab=new QLabel(this);
        iceLab->resize(pix.size());
        iceLab->setPixmap(pix);
        QRect rect(ZMB_BORDER,0,width()-ZMB_BORDER,height());
        QPoint p=game->gameHelper.posAlignBottom(rect,pix.size());
        iceLab->move(p+QPoint(0,GAP2BOTTOM<<1));
        iceLab->show();

    }
    else{
        tmr.setInterval(CYCLE_ZMB);
    }
}

void Zombie::setCommon()
{

    dir="Zombie/";
    qmv->stop();
    attackMv->stop();
    qmv->setFileName(zmbFilePre+dir+"Zombie.gif");
    attackMv->setFileName(zmbFilePre+dir+"ZombieAttack.gif");
//    if(hiting){
//        setMovie(attack);
//        attack->start();
//        qDebug()<<"set common attack ****";
//    }
//    else{
//        setMovie(qmv);
//        qmv->start();
//        qDebug()<<"set common move ****";
//    }
    qmv->start();
    attackMv->start();
}

void Zombie::setFired()
{
    if(hp<=0)
        return;
    qDebug()<<"set fired";
    hp=0;
    tmr.stop();
    tmrHit.stop();
//    dir="Zombie/";
    if(iceLab)
        iceLab->hide();
    dieMv=new QMovie(zmbFilePre+"Zombie/BoomDie.gif");
    QObject::connect(dieMv,&QMovie::frameChanged,this,&Zombie::clean);
    setMovie(dieMv);
    dieMv->start();
}

void Zombie::putHead()
{
    qDebug()<<"put head";
//    int ym;
    tmr.stop();
//    QPoint p=pos()+QPoint()
//    QRect rect(pos()+QPoint(0,80),size()+QSize(0,-80));

//    Head* head=new Head(rect,game->mainWin);
//    game->heads.push_back(head);
    if(iceLab)
        iceLab->hide();

    QSize sizeNew=size()+QSize(40,40);
    QPoint posNew=pos()+QPoint(0,-GAP2BOTTOM*2);
    resize(sizeNew);
    move(posNew);

    headMv=new QMovie(zmbFilePre+dir+"ZombieHead.gif");
    headMv->start();
    headLab=new QLabel(this);
    headLab->resize(headMv->currentPixmap().size());
    headLab->setMovie(headMv);
    headLab->move(40,0);
    headLab->show();
    qmv->stop();

    dieMv=new QMovie(zmbFilePre+dir+"ZombieDie.gif");
    qDebug()<<"connect die";
    setMovie(dieMv);
    QObject::connect(dieMv,&QMovie::frameChanged,this,&Zombie::clean);
    dieMv->start();
}

void Zombie::clean(int frameId)
{
    if(frameId==dieMv->frameCount()-1){
        end=1;

//        clr();
//        QList<ObjMov*>& zmbLs=game->zombies[row];
//        int id=game->gameHelper.findPtrId(zmbLs,this);

//        emit fun(row,id);
//        die->stop();
    }
}

void Zombie::setAttack(char sure)
{
    if(sure){
//        if(tmr.isActive()){
//            qDebug()<<"set attack r,c"<<rowTar<<' '<<colTar;
//            tmr.stop();
//            tmrHit.start();
//            setMovie(attack);
//            attack->start();
//            qmv->stop();
//        }
        hiting=1;
        qDebug()<<"set attack r,c"<<rowTar<<' '<<colTar;
        tmr.stop();
        tmrHit.start();
        setMovie(attackMv);
        attackMv->start();
        qmv->stop();
    }
    else {
//        if(!tmr.isActive()){
//            qDebug()<<"set move";
//            tmr.start();
//            tmrHit.stop();
//            setMovie(qmv);
//            attack->stop();
//            qmv->start();
//        }
        hiting=0;
        qDebug()<<"set move";
        tmr.start();
        tmrHit.stop();
        setMovie(qmv);
        attackMv->stop();
        qmv->start();
    }
}

void Zombie::hitPlt()
{
    qDebug()<<"hit plt";
    Plant* plt=game->plants[rowTar][colTar];
    if(plt){
        plt->inHp();
        if(!plt->isAlive()){
            setAttack(0);
            plt->clr();
        }
    }
    else
        setAttack(0);
}

void Zombie::inHp(int x)
{
    if(hp<=0)
        return;
    hp+=x;
    if(hp==6){
       setCommon();
    }
    else if(hp<=0){//
       putHead();
    }
}

//void Zombie::clr()
//{
//    QList<ObjMov*>& zmbLs=game->zombies[row];
//    int id=game->gameHelper.findPtrId(zmbLs,this);
//    if(id>=0){
//        qDebug()<<"clr zmb r id"<<row<<' '<<id;
//        zmbLs.erase(zmbLs.begin()+id);
////        delete this;
//    }
//}

char Zombie::isEnd()
{
    return end;
}

void Zombie::act()
{
//    qDebug()<<"zombie act";
    if(x()<=lawnRect.x()-CELL_W-ZMB_BORDER)
        emit gameover();
    std::pair<int,int> pr=game->gameHelper.rowAndCol(1,x()+ZMB_BORDER,y()+height());
    rowTar=pr.first;
    colTar=pr.second;
    if(colTar<0||colTar>=COL_NUM
            ||rowTar<0||rowTar>=ROW_NUM)
        return;
    Plant *plt=game->plants[rowTar][colTar];

    if(!plt)
        return;
    raise();
    if(game->gameHelper.checkCrash(*plt,*this,0)){
//        qDebug()<<"plt"<<plt->pos()<<' '<<plt->size();
//        qDebug()<<"zmb"<<pos()<<' '<<size();
        qDebug()<<"zombie crash";
        setAttack(1);
    }
}




CommonZmb::CommonZmb(int r, QWidget *parent):Zombie (r,parent)
{
    qDebug()<<"common zmb";
    hp=6;
    dir="Zombie/";
    QPoint pos;
    QRect rect(MAX_W,row*CELL_H+lawnRect.y(),CELL_W,CELL_H);
    ObjMov::initInfo(CYCLE_ZMB,"",zmbFilePre+dir+"Zombie.gif");
//    resize(85,120);
    pos=game->gameHelper.posAlignBottom(rect,size());
    move(pos);

    attackMv=new QMovie(zmbFilePre+dir+"ZombieAttack.gif");
}

ConeZmb::ConeZmb(int r, QWidget *parent):Zombie (r,parent)
{
    qDebug()<<"common zmb";
    hp=12;
    dir="ConeheadZombie/";
    QPoint pos;
    QRect rect(MAX_W,row*CELL_H+lawnRect.y(),CELL_W,CELL_H);
    ObjMov::initInfo(CYCLE_ZMB,"",zmbFilePre+dir+"ConeheadZombie.gif");
//    resize(85,120);
    pos=game->gameHelper.posAlignBottom(rect,size());
    move(pos);

    attackMv=new QMovie(zmbFilePre+dir+"ConeheadZombieAttack.gif");
}

BucketZmb::BucketZmb(int r, QWidget *parent):Zombie (r,parent)
{
    qDebug()<<"bucket zmb";
    hp=18;
    dir="BucketheadZombie/";
    QPoint pos;
    QRect rect(MAX_W,row*CELL_H+lawnRect.y(),CELL_W,CELL_H);
    ObjMov::initInfo(CYCLE_ZMB,"",zmbFilePre+dir+"BucketheadZombie.gif");
//    resize(85,120);
    pos=game->gameHelper.posAlignBottom(rect,size());
    move(pos);

    attackMv=new QMovie(zmbFilePre+dir+"BucketheadZombieAttack.gif");
}

//void ConeZmb::inHp(int x)
//{
//    if(hp<=0)
//        return;
//    hp+=x;
//    if(hp==6){

//    }
//    if(hp<=0){//
//       putHead();
//    }
//}
