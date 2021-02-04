#include "plant.h"
#include "game.h"

Game *Plant::game=nullptr;
Plant::Plant(QWidget* parent):QLabel (parent)
{
    qmv=nullptr;
    QObject::connect(&tmr,&QTimer::timeout,this,&Plant::act);
//    hp=0;
}

Plant:: ~Plant(){
    delete qmv;
}

void Plant::initInfoPlt(int r,int c,const QString &qstr)
{
//    move(x,y);
    row=r;
    col=c;
    qmv=new QMovie(qstr);
    qDebug()<<"frame cnt "<<qmv->frameCount();
    setMovie(qmv);
    qmv->start();
    setMouseTracking(1);
    resize(qmv->currentPixmap().size());
    show();
    //    setScaledContents(true);
}

void Plant::act()
{

}

void Plant::inHp(int x)
{
   hp+=x;
//   clr();
}

char Plant::isAlive()
{
    return hp>0;
}

void Plant::clr()
{
    if(hp<=0&&game->plants[row][col]){
        qDebug()<<"clr plt";
        game->plants[row][col]=nullptr;
        delete this;
    }
}

QString SunFlower::dir="SunFlower/";
SunFlower::SunFlower(int r,int c,QWidget *parent):Plant(parent)
{
    hp=8;
    tmr.start(7000);
    initInfoPlt(r,c,pltFilePre+dir+"SunFlower1.gif");
}

void SunFlower::act()
{
    qDebug()<<"sun flower act";

    QRect rect(pos(),size());
    Sun* sun=new Sun(rect,game->mainWin);
    game->suns.push_back(sun);
}

QString PeaShooter::dir="Peashooter/";
PeaShooter::PeaShooter(int r,int c,QWidget* parent):Plant(parent){
    qDebug()<<"peashooter construct";

    hp=8;
    tmr.start(2000);
    initInfoPlt(r,c,pltFilePre+dir+"Peashooter.gif");
}

void PeaShooter::act()
{
    if(game->zombies[row].isEmpty())
        return;
    QPoint p(x()+width()*0.7,y()+2);
//    qDebug()<<"peashooter act"<<size()<<pos();
    Pea* pea=new Pea(p,0,game->mainWin);
    game->bullets[row].push_back(pea);
}

QString SnowShooter::dir="SnowPea/";
SnowShooter::SnowShooter(int r,int c,QWidget *parent):Plant (parent)
{
    hp=8;
    tmr.start(2000);
    initInfoPlt(r,c,pltFilePre+dir+"SnowPea.gif");
}

void SnowShooter::act(){

    if(game->zombies[row].isEmpty())
        return;
    QPoint p(x()+width()*0.4,y()+2);
    qDebug()<<"snowshooter act"<<size()<<pos();
    SnowPea* snowpea=new SnowPea(p,0,game->mainWin);
    game->bullets[row].push_back(snowpea);
}


//void moveUp(){
//        x=labelPix->pos().x();
//        y=labelPix->pos().y();
//        if(y>=39)
//            y-=1;
//        else {
//            //labelPix->hide();
//            //label0->setPixmap(*qpix);
//            int cnt=pMovie1->frameCount();
//            if(pMovie1->currentFrameNumber()==cnt-1){
//                label1->hide();
//                timers[0]->stop();
//            }

//        }
//        labelPix->move(x,y);
//}


QString DoubleShooter::dir="Repeater/";
DoubleShooter::DoubleShooter(int r, int c, QWidget *parent):Plant (parent)
{
    hp=8;
    tmr.start(2000);
    initInfoPlt(r,c,pltFilePre+dir+"Repeater.gif");
}

void DoubleShooter::act(){
    if(game->zombies[row].isEmpty())
        return;
    QPoint p(x()+width()*0.7,y()+2);
    qDebug()<<"doubleshooter act"<<size()<<pos();
    Pea* pea=new Pea(p,0,game->mainWin);
    game->bullets[row].push_back(pea);

    p+=QPoint(15,0);
    pea=new Pea(p,0,game->mainWin);
    game->bullets[row].push_back(pea);
}


QString WallNut::dir="WallNut/";
WallNut::WallNut(int r, int c, QWidget *parent):Plant (parent)
{
    hp=24;
//    tmr.start(100);
    initInfoPlt(r,c,pltFilePre+dir+"WallNut.gif");
    cracked1=new QMovie(pltFilePre+dir+"Wallnut_cracked1.gif");
    cracked2=new QMovie(pltFilePre+dir+"Wallnut_cracked2.gif");

}

WallNut::~WallNut()
{
    delete cracked1;
    delete cracked2;
}

void WallNut::inHp(int x)
{
    hp+=x;
    if(hp==8){
        setMovie(cracked2);
        cracked2->start();
    }
    else if(hp==16){
        setMovie(cracked1);
        cracked1->start();
    }
//    clr();
}

QString Cherry::dir="CherryBomb/";
Cherry::Cherry(int r, int c, QWidget *parent):Plant (parent)
{
    hp=8;
//    tmr.start(100);
    initInfoPlt(r,c,pltFilePre+dir+"CherryBomb.gif");
    boom=new QMovie(pltFilePre+dir+"Boom.gif");
    QObject::connect(qmv,&QMovie::frameChanged,this,&Cherry::fire);
    QObject::connect(boom,&QMovie::frameChanged,this,&Cherry::clean);

}

Cherry::~Cherry()
{
    delete boom;
    boom=nullptr;
}

void Cherry::fire(int frameId)
{
//    qDebug()<<"cherry fire";
    if(frameId==qmv->frameCount()-1){
        qDebug()<<"cherry fire";
        QRect rect(pos(),size());
        setMovie(boom);
        boom->start();
        qmv->stop();
        resize(boom->currentPixmap().size());
        QPoint p=game->gameHelper.posAlignBottom(rect,size());
        move(p+QPoint(0,GAP2BOTTOM<<2));

        rect.setX((col-1)*CELL_W+lawnRect.x());
        rect.setY((row-1)*CELL_H+lawnRect.y());
        rect.setWidth(3*CELL_W);
        rect.setHeight(3*CELL_H);
        for(int i=0;i<ROW_NUM;i++){
            for(ObjMov* objmov:game->zombies[i]){
                QPoint tarPos0=objmov->pos()+QPoint(ZMB_BORDER,objmov->height());
                QPoint tarPos1=objmov->pos()+QPoint(objmov->width()-BORDER,objmov->height());
                if(game->gameHelper.isPosInRect(tarPos0,rect)||
                        game->gameHelper.isPosInRect(tarPos1,rect)){
                    ((Zombie*)objmov)->setFired();
                }
            }
        }

//        move(p);
    }

}

void Cherry::clean(int frameId)
{
//    qDebug()<<"cherry die";
    if(frameId==boom->frameCount()-1){
        qDebug()<<"cherry die";
        hp=0;
        boom->stop();
        clr();
    }
}
