#include "plantcard.h"
#include "game.h"

//char PlantCard::game->state=SELECT;
//int PlantCard::curSunNum=50;
const int PlantCard::coolDur[NUM_PLANT]={
    8000/20, 10000/20, 14000/20, 16000/20,
    18000/20, 18000/20
};

Game* PlantCard::game;
PlantCard::PlantCard(QListWidget* parent,int pltId):
    QListWidgetItem (parent)
{    
    plantId=pltId;
    checked=0;
    ratio=1;
//    mytmr.incRatio=addRatio;
//    mytmr.start(100);

    timer.start(coolDur[pltId]);
    QObject::connect(&timer,&QTimer::timeout,this,&PlantCard::addRatio);

    QPixmap pix(cardFilePre+getCardInfo(pltId));
    int w=pix.width();
    int h=pix.height()/2;
    activePix=pix.copy(0,0,w,h);
    inactivePix=pix.copy(0,h,w,h);

    QString sunNum=QString::number(getSunNum(pltId));

    painter.begin(&activePix);
    QFont font=painter.font();
    font.setPixelSize(22);//改变字体大小
    painter.setFont(font);
    painter.setPen(Qt::yellow);
    painter.drawText(activePix.rect(),Qt::AlignRight|Qt::AlignBottom,sunNum);
    painter.end();
    painter.begin(&inactivePix);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(inactivePix.rect(),Qt::AlignRight|Qt::AlignBottom,sunNum);
    painter.end();

    coolPix=activePix;
    painter.begin(&coolPix);
//    painter.setCompositionMode(QPainter::CompositionMode_ColorDodge);
    painter.fillRect(coolPix.rect(), QColor(255, 255, 255, 110));
    painter.end();

//    QRect target(0, h/2, w, h/2); //建立目标矩形，该区域是显示图像的目的地
//    QRect source(0, h/2, w, h/2);
//    QPixmap tmp=inactivePix;
//    painter.begin(&tmp);
//    painter.drawPixmap(target,showPix,source);
//    painter.end();

    setIcon(QIcon(activePix));
    setSizeHint(QSize(CARD_W+2,CARD_H+2));
    setFlags(flags() & ~Qt::ItemIsSelectable);
}


PlantCard::~PlantCard() {
//    delete pix;
//    delete activePix;
//    delete inactivePix;
}

int PlantCard::getPltId() {
    return plantId;
}

//void PlantCard::setgame->state(char x) {
//    game->state=x;
//}

//void PlantCard::setSunNum(int x) {
//    curSunNum=x;
//}

void PlantCard::addRatio() {
    if(game->state==PLANT&&checked){
        if(ratio<1)
            ratio+=0.05;
        updateImg();
    }
//    qDebug()<<"add ratio";
}

void PlantCard::updateImg() {
    if(game->state==PLANT){
//        if(ratio>=1||!checked){
          if(ratio>=1){
            if(game->sunNum>=getSunNum(plantId)){
                setIcon(QIcon(activePix));
                checked=0;
//                ratio=0;
            }
            else {
                setIcon(QIcon(inactivePix));
                checked=1;
            }
//            ratio=0;
//            checked=0;
        }
        else {
            QPixmap tmp=inactivePix;
            int h=tmp.height()*ratio;
            QRect target(0, tmp.height()-h, tmp.width(), h); //建立目标矩形，该区域是显示图像的目的地
            QRect source=target;
            painter.begin(&tmp);
            painter.drawPixmap(target,coolPix,source);
            painter.end();
            setIcon(QIcon(tmp));
        }
    }
    else if(game->state==SELECT){
       if(checked)
           setIcon(QIcon(inactivePix));
       else
           setIcon(QIcon(activePix));
    }
}
void PlantCard::setChecked(char c) {
    if(game->state==END)
        return;
//    if(c<0){
//        checked=checked>0?0:1;
//    }
//    else
//        checked=c;
    checked=c;
    if(c)
        ratio=0;
    updateImg();
}
char PlantCard::isChecked() {
    return checked;
}
QString PlantCard::getCardInfo(int pltId) {
    QString cardFileName="";
//    int sunNeed=0;
    switch(pltId)
    {
    case 0:
//        coolCycle=50;
        cardFileName="SunFlower.png";
        break;
    case 1:
//        coolCycle=100;
        cardFileName="Peashooter.png";
        break;
    case 2:
//        coolCycle=100;
        cardFileName="SnowPea.png";
        break;
    case 3:
//        coolCycle=150;
        cardFileName="Repeater.png";
        break;
    case 4:
//        coolCycle=200;
        cardFileName="WallNut.png";
        break;
    case 5:
        cardFileName="CherryBomb.png";
        break;
    case 6:
        cardFileName="PotatoMine.png";
        break;
    }
    return cardFileName;
//    return QPair<name,sunNeed>;
}

//MyTimer::MyTimer(PlantCard* card, QWidget *parent):QTimer (parent)
//{
////    incRatio=f;
//    pltcard=card;
//    QObject::connect(this,&QTimer::timeout,this,&MyTimer::myslot);
//}

//void MyTimer::myslot()
//{
//    pltcard->addRatio();
//}
