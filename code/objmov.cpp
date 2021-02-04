#include "objmov.h"
#include "game.h"

Game* ObjMov::game=nullptr;
ObjMov::ObjMov(QWidget *parent):
    QLabel (parent)
//    animation(this,"pos")
{
    qmv=nullptr;
//    QObject::connect(&tmr,&QTimer::timeout,this,&ObjMov::movePos);
}

ObjMov::~ObjMov()
{
//    qDebug()<<"~objmov";
//    if(qmv)
//        delete qmv;
    delete qmv;
    qmv=nullptr;
//    delete animation;
}

void ObjMov::initInfo(int cycle,const QString& qstr,const QString& qstr1)
{

//    move(posStart);
    tmr.setInterval(cycle);
//    tmr.start(cycle);
    if(!qstr.isEmpty()){
        pix.load(qstr);
        qDebug()<<"pix size"<<pix.size();
        resize(pix.size());
        setPixmap(pix);
    }
    if(!qstr1.isEmpty()){
        qmv=new QMovie(qstr1);
        qmv->start();
//        qmv->jumpToFrame(20);
        resize(qmv->currentPixmap().size());
        qDebug()<<"qstr1 cnt "<<qmv->frameCount()<<"size"<<qmv->currentPixmap().size();
        setMovie(qmv);
    }
    show();
}

void ObjMov::act()
{

}

void ObjMov::movePos()
{
    int x=this->x(),y=this->y();
    if(game->state!=PLANT&&game->state!=SHOVEL)
        return;
    if(hp>0)
        switch(movType)
        {
            case LEFT:
//            qDebug()<<"move pos left";
                x-=GAP_MOV;
                break;
            case RIGHT:
                x+=GAP_MOV;
                break;
            case UP:
                y-=GAP_MOV;
                break;
            case DOWN:
                y+=GAP_MOV;
                break;
//            case ARC_R:
//                x+=GAP_MOV;
//                y=arc.x2y(x);
////                qDebug()<<"move arc r,x,y"<<x<<' '<<y;
//                break;
        }
    move(x,y);
    act();  
}

char ObjMov::isAlive()
{
    return hp>0;
}

//ObjMov::ObjMov(QWidget *parent):
//    QLabel (parent)
//  //    animation(this,"pos")
//{
//    //    animation.setStartValue(posStart);
//    ////    animation.setEndValue(QPoint(parent->width(),posStart.y()));
//    //    animation.setEndValue(posEnd);
//    //    animation.setDuration(dur);
//    //    animation.start();
//    animation=nullptr;
//    qmv=nullptr;
//}

//ObjMov::~ObjMov()
//{
//    delete qmv;
//    delete animation;
//}

//void ObjMov::initInfo(const QPoint &posStart, const QPoint &posEnd, int dur,const QString& qstr)
//{
//    //    animation.setStartValue(posStart);
//    ////    animation.setEndValue(QPoint(parent->width(),posStart.y()));
//    //    animation.setEndValue(posEnd);
//    //    animation.setDuration(dur);
//    //    animation.start();
//    animation=new QPropertyAnimation(this,"pos");
//    animation->setStartValue(posStart);
//    //    animation.setEndValue(QPoint(parent->width(),posStart.y()));
//    animation->setEndValue(posEnd);
//    animation->setDuration(dur);
//    animation->start();

//    pix.load(qstr);
//    resize(pix.size());
//    setPixmap(pix);
//    show();
//}

//int Arc::x2y(int x)
//{
//    double tmp=rect.width()*rect.width();
//    tmp=rect.height()/tmp;
//    int xx=x-rect.x();
//    return tmp*xx*xx+rect.y();
//}

ObjMovTmp::ObjMovTmp(QWidget *parent):ObjMov (parent)
{
    hp=1;
    tmr.start();
    QObject::connect(&tmr,&QTimer::timeout,this,&ObjMov::movePos);
}

//void ObjMovTmp::initInfo(const QPoint &pos, int ym)
//{
////    yMax=ym;
////    hp=1;
//////    id=idTmp;
////    move(pos);
////    qDebug()<<"id tmp";
//}

void ObjMovTmp::deTime()
{
//    qDebug()<<"detime y"<<y();
    if(y()>=yMax){
        hp=0;
        timeCnt--;
    }
}

Sun::Sun(const QRect& rect,QWidget *parent):ObjMovTmp (parent)
{
//    tmr.start(50);
    movType=DOWN;
    timeCnt=140;//70个时钟
    ObjMov::initInfo(25,"",interfaceFilePre+"Sun.gif");

//    QRect rect(pos(),size());
    QPoint pos=game->gameHelper.posAlignTop(rect,size());
    pos+=QPoint(0,-BORDER);

//    int ym=y()+height()-height()/2;
//    initInfo(pos,ym);

//    hp=1;
    move(pos);    
    yMax=y()+rect.height()-height()*0.3;

//    qmv=new QMovie(interfaceFilePre+"Sun.gif");
//    qDebug()<<"sun frame cnt "<<qmv->frameCount();
//    setMovie(qmv);
//    qmv->start();
}

//void Sun::initInfo(const QPoint &pos, int ym,int idTmp)
//{
//    yMax=ym;
//    id=idTmp;
//    move(pos);
////    show();
////    ObjMov::initInfo(pos,50,"",interfaceFilePre+"Sun.gif");
////    move(pos);
//}

void Sun::clr()
{
    int id=game->gameHelper.findPtrId(game->suns,this);
    qDebug()<<"clr sun"<<id;
    if(id>=0){
        game->suns.erase(game->suns.begin()+id);
    }
    delete this;
}

void Sun::act()
{
    deTime();
    if(timeCnt<=0){
        clr();
    }
}

//Head::Head(const QRect& rect, QWidget *parent):ObjMovTmp (parent)
//{
//    movType=ARC_R;
//    timeCnt=100;//100个时钟
////    ObjMov::initInfo(100,zmbFilePre+"Zombie/ZombieHead.gif");
//    QString qstr=zmbFilePre+"Zombie/ZombieHead.gif";
//    tmr.setInterval(100);
////    tmr.start(cycle);
//    if(!qstr.isEmpty()){
//        pix.load(qstr);
//        qDebug()<<"pix size"<<pix.size();
////        pix=pix.copy()
//        resize(pix.size());
//        setPixmap(pix);
//    }
////    QRect rect(pos(),size());//关键僵尸大小
//    QPoint pos=game->gameHelper.posAlignTop(rect,size());
//    yMax=rect.y()+rect.height()-BORDER;
//    move(pos);
//    qDebug()<<"y max"<<yMax;
////    head->initInfo(posTmp,ym);

//    arc.rect.setRect(pos.x(),pos.y(),rect.width()*0.7,rect.height());
//    qDebug()<<"arc rect"<<arc.rect;
//}

//void Head::act()
//{
//    qDebug()<<"head act";
//    deTime();
//    if(timeCnt<=0){
//        int id=game->gameHelper.findPtrId(game->heads,this);
//        qDebug()<<"clr head"<<id;
//        if(id>=0){
//            game->heads.erase(game->heads.begin()+id);
//            delete this;
//        }
//    }
//}
