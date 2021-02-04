#include "game.h"
#include "mainwindow.h"
//QPixmap* Game::cursorPixs[2]={
//    new QPixmap(pltFilePre+SunFlower::dir+"0.gif"),
//    new QPixmap(pltFilePre+PeaShooter::dir+"0.gif")
//};
//QList<ObjMov*>* ThreadBlt::bullets;
//ThreadBlt::ThreadBlt(int interval,QWidget* parent):QThread (parent)
//{
//    cycle=interval;
//}

//void ThreadBlt::run()
//{
////    int id=QThread::currentThread();
//    qDebug()<<"cycle "<<cycle;
//    while(1){
//        for(int i=0;i<ROW_NUM;i++){
//            for(ObjMov* objmov:bullets[i]){
//                objmov->movePos();
//                qDebug()<<"run blt";
//            }
//        }
//        msleep(5);
//    }

//}

Game::Game(QWidget* parent):QObject(parent),gameHelper(this)
{
    mainWin=parent;
    curPltId=-1;
    showCursorImg=0;
    sunNum=0;
//    PlantCard::setSunNum(sunNum);
//    ThreadBlt::bullets=bullets;
    PlantCard::game=ObjMov::game=Plant::game=this;
//    action=PLANT;

//    tmrPlt.start(100);
//    button=new QPushButton(mainWin);
//    button->resize(50,50);
//    button->move(30,10);
//    button->setText("B");
//    button->raise();
//    button->installEventFilter(mainWin);

//    QObject::connect(button,&QPushButton::clicked,this,&Game::plantsAct);

    QString dirs[NUM_PLANT]={
        SunFlower::dir,PeaShooter::dir,SnowShooter::dir,
        DoubleShooter::dir,WallNut::dir,Cherry::dir
    };
    //SnowShooter::dir
    for(int i=0;i<ROW_NUM;i++)
        for(int j=0;j<COL_NUM;j++)
            plants[i][j]=nullptr;
    for(int i=0;i<6;i++)
        cursorPixs[i].load(pltFilePre+dirs[i]+"0.gif");

//    thrBlt=new ThreadBlt(5,mainWin);
//    thrBlt->start();

//    thrBlt[0]=new ThreadBlt(10,mainWin);
//    thrBlt[1]=new ThreadBlt(20,mainWin);
//    thrBlt[0]->start();
//    thrBlt[1]->start();
//    bullets[0].push_back(new Pea(QPoint(100,82),10,mainWin));
//    new Pea(QPoint(100,50),10,mainWin);

//    cursorPlt=new QLabel(mainWin);
//    shovel=new QLabel(mainWin);
//    shovelBack=new QLabel(mainWin);
//    QPixmap pix(interfaceFilePre+"ShovelBack.png");
//    shovelBack->resize(pix.size());
//    shovelBack->setPixmap(pix);
////    shovelBack->setGeometry(180,4,pix.width(),pix.height());
//    shovelBack->move(180,4);
////    qDebug()<<shovelBack->rect();
//    pix.load(interfaceFilePre+"Shovel.png");
//    shovel->resize(pix.size());
//    shovel->setPixmap(pix);
//    QRect rect(shovelBack->pos(),shovelBack->size());
//    shovel->move(posAlignCenter(rect,shovel->size()));
//    shovel->raise();

//    Zombie* zmb=new CommonZmb(2,mainWin);
////    Zombie* zmb=new ConeZmb(2,mainWin);
//    zombies[2].push_back(zmb);

//    QRect rect(QPoint(100,100),QSize(100,100));
//    Head* head=new Head(rect,mainWin);
//    heads.push_back(head);

    endLab=new QLabel(mainWin);

    qDebug()<<"put zmb cnt"<<zombies[0].size();
    tmrSys.start(10000);
    tmrBlt.start(5);

    QObject::connect(&tmrSys,&QTimer::timeout,this,&Game::putSysSun);
    QObject::connect(&tmrBlt,&QTimer::timeout,this,&Game::bulletsAct);

}

Game::~Game()
{
//    for(int i=0;i<ROW_NUM;i++)
//        for(int j=0;j<COL_NUM;j++){
//            delete plants[i][j];
//            plants[i][j]=nullptr;
//        }
    clrObjects();
    delete cursorPlt;
    delete shovel;
}

//void Game::fun(int row, int id)
//{
//    qDebug()<<"fun **************"<<id;
//    delete zombies[row][id];
//    zombies[row].erase(zombies[row].begin()+id);
//}

//void Game::fun(int id)
//{
//    qDebug()<<"fun "<<id;
//}

void Game::initInfo()
{
    cursorPlt=new QLabel(mainWin);
    shovel=new QLabel(mainWin);
    shovelBack=new QLabel(mainWin);
    sunBack=new QLabel(mainWin);
    sunNumTxt=new QLabel(sunBack);
    whiteCell=new QLabel(mainWin);

    QPixmap pix(interfaceFilePre+"ShovelBack.png");
    shovelBack->resize(pix.size());
    shovelBack->setPixmap(pix);
    shovelBack->move(180,6);
//    qDebug()<<shovelBack->rect();

    pix.load(interfaceFilePre+"Shovel.png");
    shovel->resize(pix.size());
    shovel->setPixmap(pix);
    QRect rect(shovelBack->pos(),shovelBack->size());
    shovelBegin=gameHelper.posAlignCenter(rect,shovel->size());
    shovel->move(shovelBegin);
    shovel->raise();

    pix.load(interfaceFilePre+"SunBack.png");
    sunBack->resize(pix.size());
    sunBack->setPixmap(pix);
    sunBack->move(50,4);

    sunNum=100;
    QFont font( "Microsoft YaHei", 12);
    sunNumTxt->resize(78,pix.height());
    sunNumTxt->move(37,0);
    sunNumTxt->setAlignment(Qt::AlignCenter);
    sunNumTxt->setFont(font);
    sunNumTxt->setNum(sunNum);

//    pix.scaled(CELL_W,CELL_H);
//    QPainter p(&pix);
//    pix.fill(Qt::transparent);
//    p.setOpacity(0.4);
//    p.fillRect(pix.rect(),QColor(255, 255, 255));
//    whiteCell->setPixmap(pix);
    whiteCell->resize(CELL_W,CELL_H);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255,100));
    whiteCell->setAutoFillBackground(true);  //一定要这句，否则不行
    whiteCell->setPalette(palette);

//    QPoint p0(10,50),p1(500,50);
//    new Pea(p0,p1,1000,mainWin);
//    whiteCell->setNum()

    cursorPlt->setMouseTracking(1);
    shovel->setMouseTracking(1);
    shovelBack->setMouseTracking(1);
    whiteCell->setMouseTracking(1);
    shovelBack->show();
    shovel->show();
    sunBack->show();
    sunNumTxt->show();
}

char Game::findSun()
{
    for(ObjMov* objmov:suns){
        if(gameHelper.isPosInRect(cursorPos,QRect(objmov->pos(),objmov->size()))){
            sunNum+=50;
            ((MainWindow*)mainWin)->checkWidgetList();
            sunNumTxt->setNum(sunNum);
            ((Sun*)objmov)->clr();
            return 1;
        }
    }
//    qDebug()<<"head";
//    int ym=180;
//    Head* head=new Head(mainWin);
//    head->initInfo(QPoint(100,100),ym);
//    head->arc.rect.setRect(100,100,80,80);
    return 0;
}

char Game::clicked(char sure)
{
//    if(plants[0][0]==nullptr){
//        plants[0][0]=new PeaShooter(100,100,mainWin);
//    }
//    cursorPlt->setPixmap(cursorPixs[1]);
//    cursorPlt->show();

    if(state!=PLANT&&state!=SHOVEL)
        return 0;
    if(sure){//确定
        if(state==PLANT){
//            qDebug()<<shovel->rect();
            QRect rect(shovel->pos(),shovel->size());
            if(!findSun() && gameHelper.isPosInRect(cursorPos,rect)){
                state=SHOVEL;
                curPltId=-1;
                showCursorImg=0;
                cursorPlt->hide();
                whiteCell->hide();
//                qDebug()<<"get shovel";
            }
            else if(curPltId>=0&&gameHelper.isPosInRect(cursorPos,lawnRect)){
                //若草地空白，则种下
                qDebug()<<"种下";
                char c=plantHandle(1);
                if(c){
                    curPltId=-1;
                    showCursorImg=0;
                    cursorPlt->hide();
                    whiteCell->hide();
                }
                return c;
            }
//            else{
//                findSun();
//            }
        }
        else {
            //删除植物
            return plantHandle(0);

        }
    }
    else{//取消
        showCursorImg=0;
        if(state==PLANT){
            cursorPlt->hide();
            whiteCell->hide();
        }
        else{
            shovel->move(shovelBegin);
            whiteCell->hide();
            state=PLANT;
        }
        curPltId=-1;
    }
    return 0;
}

//void Game::plantsAct()
//{
//    qDebug()<<"plant act";
//}

//void Game::zombiesAct()
//{
//    qDebug()<<"zombie act";
//}

void Game::bulletsAct()
{
//    qDebug()<<"bullet act";
    Zombie *zmb;
    for(int i=0;i<ROW_NUM;i++){
        for(int j=zombies[i].size()-1;j>=0;j--){
            zmb=(Zombie*)zombies[i][j];
//            zmb->movePos();
            zmb->raise();
            if(zmb->isEnd()){
                delete zmb;
                zombies[i].erase(zombies[i].begin()+j);
            }
        }
//        for(ObjMov* objmov:bullets[i]){
//            objmov->movePos();
//        }
        for(int j=bullets[i].size()-1;j>=0;j--){
            bullets[i][j]->movePos();
        }
    }
}

void Game::setStart(bool sure)
{
    if(sure){
        state=PLANT;
        tmrBlt.start();
        tmrSys.start();
//        tmrZmb.start();
        for(ObjMov* objmov:suns)
            objmov->tmr.start();
//        for(ObjMov* objmov:heads)
//            objmov->tmr.start();

    }
    else{
        state=PAUSE;
        tmrBlt.stop();
        tmrSys.stop();
//        tmrZmb.stop();
        for(ObjMov* objmov:suns)
            objmov->tmr.stop();
//        for(ObjMov* objmov:heads)
//            objmov->tmr.stop();
    }
    for(int i=0;i<ROW_NUM;i++){
        for(int j=0;j<COL_NUM;j++){
            if(plants[i][j]){
                if(sure)
                    plants[i][j]->tmr.start();
                else
                    plants[i][j]->tmr.stop();
            }
        }
        for(ObjMov* objmov:zombies[i]){
            Zombie* zmb=(Zombie*)objmov;
            if(sure){
                zmb->tmr.start();
                zmb->tmrHit.start();
                zmb->attackMv->start();
            }
            else{
                zmb->tmr.stop();
                zmb->tmrHit.stop();
                zmb->attackMv->stop();
            }
        }
    }

}

void Game::end()
{
   state=END;
   QPoint p;
//   endLab=new QLabel(mainWin);
   QPixmap endPix(interfaceFilePre+"ZombiesWon.png");
   p=gameHelper.posAlignCenter(mainWin->rect(),endPix.size());
   endLab->resize(endPix.size());
   endLab->setPixmap(endPix);
   endLab->move(p);
   endLab->show();
}

void Game::clrList(QList<ObjMov *> &objList, int id)
{

    if(id<0){
        for(ObjMov* objmov:objList)
            delete objmov;
        objList.clear();
    }
    else{
       qDebug()<<"clr ls id"<<id;
       delete objList[id];
       objList.erase(objList.begin()+id);
    }
}

void Game::clrObjects()
{
//    if(which==0){//清理植物
//        for(int i=0;i<ROW_NUM;i++)
//            for(int j=0;j<COL_NUM;j++){
//                delete plants[i][j];
//                plants[i][j]=nullptr;
//            }
//    }
//    else {

//    }
    for(int i=0;i<ROW_NUM;i++){
        for(int j=0;j<COL_NUM;j++){
            delete plants[i][j];
            plants[i][j]=nullptr;
        }
        clrList(bullets[i]);
        clrList(zombies[i]);
    }
    clrList(suns);
    endLab->hide();
//    clrList(heads);


}

char Game::plantHandle(bool add)
{
//    int xx=0,yy=0;
//    if(!add){
//        xx=-shovel->width()/2;
//        yy=shovel->height()/2;
//    }

//    int col=(cursorPos.x()-lawnRect.x()+xx)/CELL_W;
//    int row=(cursorPos.y()-lawnRect.y()+yy)/CELL_H;
//    Plant* plt=plants[row][col];
    std::pair<int,int> pr=gameHelper.rowAndCol(add);
    int row=pr.first;
    int col=pr.second;
    if(add){
        if(plants[row][col]==nullptr){
            sunNum-=getSunNum(curPltId);
            ((MainWindow*)mainWin)->checkWidgetList();
            sunNumTxt->setNum(sunNum);
            plants[row][col]=gameHelper.whichPlant(row,col);
            return 1;
        }
    }
    else {
        if(plants[row][col]!=nullptr){
            delete plants[row][col];
            return 1;
        }
    }

    return 0;
}

void Game::putSysSun()
{
//    int x,y;
//    y=-CELL_H;
    if(state!=PLANT&&state!=SHOVEL)
        return;
    qDebug()<<"put sys sun";

//    gameHelper.putZmbs();

    int x=qrand()%lawnRect.width()+lawnRect.x();
    int h=qrand()%lawnRect.height()+lawnRect.y()*2+CELL_H;
    Sun* sun=new Sun(QRect(x,-CELL_H,CELL_W,h),mainWin);
    suns.push_back(sun);
}

//Plant *Game::whichPlant(int row,int col)
//{
//    Plant* plt=nullptr;
//    int x=col*CELL_W+lawnRect.x();
//    int y=row*CELL_H+lawnRect.y();
//    QRect rect(x,y,CELL_W,CELL_H);
//    switch (curPltId) {
//    case 0:
//        plt=new SunFlower(mainWin);
//        break;
//    case 1:
//        plt=new PeaShooter(mainWin);
//        break;
//    case 2:
//        plt=new SnowShooter(mainWin);
//        break;
//    }
//    plt->move(posAlignBottom(rect,plt->size()));
//    return plt;
//}

////bool Game::eventFilter(QObject *target, QEvent *event)
////{
////    if(event->type()==QEvent::MouseMove){
////        qDebug()<<"mouse move ";

////        return 1;
////    }
////    return 0;
////}

//QPoint Game::posAlignBottom(const QRect &destRect, const QSize &srcSize)
//{
//    int x=destRect.x()+destRect.width()/2-srcSize.width()/2;
//    int y=destRect.y()+destRect.height()-srcSize.height();
//    return QPoint(x,y);
//}

//QPoint Game::posAlignCenter(const QRect &destRect, const QSize &srcSize)
//{
////    qDebug()<<destRect<<endl<<srcSize;
//    int x=destRect.x()+(destRect.width()-srcSize.width())/2;
//    int y=destRect.y()+(destRect.height()-srcSize.height())/2;
////    qDebug()<<"center x,y"<<x<<' '<<y;
//    return QPoint(x,y);
//}

//bool Game::posInRect(const QPoint &pos, const QRect &rect)
//{
//    int x=pos.x();
//    int y=pos.y();
//    return x>=rect.x()&&x<=(rect.x()+rect.width())&&
//            y>=rect.y()&&y<=(rect.y()+rect.height());
//}

void Game::updateCursorPix()
{
//    curPltId = id;
    QRect rect(cursorPos.x(),cursorPos.y(),0,0);
//    QSize size;
    if(state==PLANT){
        if(curPltId<0)
            return;
        QSize size=cursorPixs[curPltId].size();
//        cursorPlt->setPixmap(cursorPixs[curPltId]);
//        cursorPlt->resize(size);
//        QPoint posTmp=gameHelper.posAlignCenter(rect,size);

        if(showCursorImg==0){
            showCursorImg=1;
            cursorPlt->setPixmap(cursorPixs[curPltId]);
            cursorPlt->resize(size);
            whiteCell->show();
            cursorPlt->show();
            cursorPlt->raise();
        }
        cursorPlt->move(gameHelper.posAlignCenter(rect,size));
        whiteCell->move(gameHelper.posWhiteCell(1));

    }
    else{
//        size=shovel->size();
        shovel->move(gameHelper.posAlignCenter(rect,shovel->size()));
        whiteCell->move(gameHelper.posWhiteCell(0));
        if(showCursorImg==0){
            showCursorImg=1;
            whiteCell->show();
        }
    }

}


