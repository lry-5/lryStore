#include "game.h"
#include "gamehelper.h"

GameHelper::GameHelper(Game* g)
{
    game=g;
    zmbCnt=1;
    cyclePut=CYCLE_PUT;
    tmrPut.start(cyclePut);

    QObject::connect(&tmrPut,&QTimer::timeout,this,&GameHelper::putZmbs);
}

Plant *GameHelper::whichPlant(int row, int col)
{
    Plant* plt=nullptr;
    int x=col*CELL_W+lawnRect.x();
    int y=row*CELL_H+lawnRect.y();
    QRect rect(x,y,CELL_W,CELL_H);
    switch (game->curPltId) {
        case 0:
            plt=new SunFlower(row,col,game->mainWin);
            break;
        case 1:
            plt=new PeaShooter(row,col,game->mainWin);
            break;
        case 2:
            plt=new SnowShooter(row,col,game->mainWin);
            break;
        case 3:
            plt=new DoubleShooter(row,col,game->mainWin);
            break;
        case 4:
            plt=new WallNut(row,col,game->mainWin);
            break;
        case 5:
            plt=new Cherry(row,col,game->mainWin);
            break;
    }
    plt->move(posAlignBottom(rect,plt->size()));
    return plt;
}

void GameHelper::putZmbs()
{
    if(game->state!=PLANT&&game->state!=SHOVEL)
        return;

//    return;

    int tmp=zmbCnt%31;
//    if(tmp==0){
//        cyclePut=CYCLE_PUT;
//        tmrPut.setInterval(cyclePut);
//    }
//    else if(tmp==15||tmp==25){
//        cyclePut>>=1;
//        tmrPut.setInterval(cyclePut);
//    }
    setCyclePut(tmp);
//    qDebug()<<"put zmb";
    Zombie* zmb;
    char rand=0;
    int rowTar=qrand()%ROW_NUM;
    qDebug()<<"put zmb tmp row"<<tmp<<' '<<rowTar;
    if(tmp<5){

        zmb=new CommonZmb(rowTar,game->mainWin);
        if(zmb){
            qDebug()<<"zmb not null";
            game->zombies[rowTar].push_back(zmb);
            qDebug()<<"pushed zmb";
        }
    }
    else if(tmp<25){
        rand=qrand()%3;
//        if(rand){
//            zmb=new ConeZmb(rowTar,game->mainWin);
//        }
//        else {
//            zmb=new CommonZmb(rowTar,game->mainWin);
//        }
        if(rand==0){
            zmb=new ConeZmb(rowTar,game->mainWin);
        }
        else if(rand==1){
            zmb=new CommonZmb(rowTar,game->mainWin);
        }
        else {
            zmb=new BucketZmb(rowTar,game->mainWin);
        }
        game->zombies[rowTar].push_back(zmb);
    }
    else{
        for(int i=0;i<ROW_NUM;i++){
            rand=qrand()%3;
//            if(rand){
//                zmb=new ConeZmb(i,game->mainWin);
//            }
//            else{
//                zmb=new CommonZmb(i,game->mainWin);
//            }
            if(rand==0){
                zmb=new ConeZmb(i,game->mainWin);
            }
            else if(rand==1){
                zmb=new CommonZmb(i,game->mainWin);
            }
            else {
                zmb=new BucketZmb(i,game->mainWin);
            }
            game->zombies[i].push_back(zmb);
        }
    }
    zmbCnt++;
}

void GameHelper::setCyclePut(int tmp)
{
    if(tmp==0){
        cyclePut=CYCLE_PUT;
        tmrPut.setInterval(cyclePut);
    }
    else if(tmp==15||tmp==25){
        cyclePut>>=1;
        tmrPut.setInterval(cyclePut);
    }
}

QPoint GameHelper::posAlignBottom(const QRect &destRect, const QSize &srcSize)
{
    int x=destRect.x()+destRect.width()/2-srcSize.width()/2;
    int y=destRect.y()+destRect.height()-srcSize.height()-GAP2BOTTOM;
    return QPoint(x,y);
}

QPoint GameHelper::posAlignCenter(const QRect &destRect, const QSize &srcSize)
{
    //    qDebug()<<destRect<<endl<<srcSize;
        int x=destRect.x()+(destRect.width()-srcSize.width())/2;
        int y=destRect.y()+(destRect.height()-srcSize.height())/2;
    //    qDebug()<<"center x,y"<<x<<' '<<y;
        return QPoint(x,y);
}

QPoint GameHelper::posAlignTop(const QRect &destRect, const QSize &srcSize)
{
    int x=destRect.x()+destRect.width()/2-srcSize.width()/2;
    int y=destRect.y();
//    int y=destRect.y()+destRect.height()-srcSize.height()-GAP2BOTTOM;
    return QPoint(x,y);
}

bool GameHelper::isPosInRect(const QPoint &pos, const QRect &rect)
{
    int x=pos.x();
    int y=pos.y();
    return x>=rect.x()&&x<=(rect.x()+rect.width())&&
            y>=rect.y()&&y<=(rect.y()+rect.height());
}

QPoint GameHelper::posWhiteCell(bool add)
{
    std::pair<int,int> pr=rowAndCol(add);
    int x=pr.second*CELL_W+lawnRect.x();
    int y=pr.first*CELL_H+lawnRect.y();
    return QPoint(x,y);
}

int GameHelper::findPtrId(QList<ObjMov*> &list, void *ptr)
{
//    int id=0;
    for(int id=0;id<list.size();id++){
        if(ptr==list[id]){
            return id;
        }
    }
    return -1;
}

char GameHelper::checkCrash(const QLabel &label0, const QLabel &label1, char strict)
{
    char res=0;
    int x0=label0.x(),x1=label1.x()+ZMB_BORDER;
    int w0=label0.width(),w1=label1.width()-ZMB_BORDER;
    if(strict){
        res=x0>(x1-w0)&&x0<=(x1+w1-w0-BORDER);
    }
    else{
        res=x0>(x1-w0+BORDER)&&x0<=(x1+w1-w0-BORDER);
    }
    return res;
}

std::pair<int, int> GameHelper::rowAndCol(bool center,int x,int y)
{
    int xx=0,yy=0;
    if(!center){
        xx=-game->shovel->width()/2;
        yy=game->shovel->height()/2;
    }
    int col,row;
    if(x<0||y<0){
        col=(game->cursorPos.x()-lawnRect.x()+xx)/CELL_W;
        row=(game->cursorPos.y()-lawnRect.y()+yy)/CELL_H;
    }
    else{
        col=(x-lawnRect.x()+xx)/CELL_W;
        row=(y-lawnRect.y()+yy)/CELL_H;
    }
    return std::pair<int,int>(row,col);
}

//int GameHelper::findPtrId(char which,int row, void *ptr)
//{
//    int id=0;
//    if(which){//查找僵尸
//        //        for(id=0;id<game->zombies[row].size();id++){

//        //        }
//    }
//    else{//查找子弹
//        for(id=0;id<game->bullets[row].size();id++){
//            if(ptr==game->bullets[row][id]){
//                return id;
//            }
//        }
//    }
//    return -1;
//}

