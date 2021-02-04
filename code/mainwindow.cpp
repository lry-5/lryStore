#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
//    game(this)
{

    ui->setupUi(this);
    game=new Game(this);
//    QPushButton* but=new QPushButton(this);
//    but->resize(50,50);
//    but->move(30,100);
//    but->setText("T");
//    but->setMouseTracking(1);
//    but->installEventFilter(this);
//    but->raise();
//    QObject::connect(but,&QPushButton::clicked,&game,&Game::plantsAct);

//    game=new Game(this);
//    setWindowTitle(tr("Main Window"));
//    this->setStyleSheet("QMainWindow{background-image:url(../resource/Interface/background0.jpg);"
//                        "background-position:top left;background-repeat:no-repeat;}");
//    this->setFixedSize(946,603);

//    QString zombieFilePre("../resource/Zombies/");
//    QString plantFilePre("../resource/Plants/");

//    qmov=new QMovie(plantFilePre+"PotatoMine/PotatoMine.gif");
//    //qmov=new QMovie(plantFilePre+"Peashooter/Peashooter.gif");
//    //qmov=new QMovie(zombieFilePre+"Zombie/HeadMov1.gif");
//    qpix=new QPixmap(plantFilePre+"PotatoMine/PotatoMine_mashed.gif");
//    pMovie1=new QMovie(plantFilePre+"PotatoMine/Mound.gif");

//    label0=new QLabel(this);
//    label0->resize(131,92);
//    label0->move(200,100);
//    label0->setMovie(pMovie0);
//    isBomb=0;


//    QPixmap qpixTmp(plantFilePre+"PotatoMine/PotatoMineNotReady.gif");


//    QPixmap board(label0->size());
//    //QPixmap qpixTmp;
//    QPainter qp(&board);
//    qp.drawPixmap(47,62,qpixTmp);
//    label0->setPixmap(board);

//    qmov=new QMovie(plantFilePre+"PotatoMine/PotatoMine.gif");

//    labelPix=new QLabel(this);
////    labelPix->move(28,71);
//    //labelPix->setPixmap(qPix);
//    labelPix->setMovie(qmov);
//    labelPix->setFixedSize(74,53);
//    //labelPix->setScaledContents(true);
//    qmov->start();
//    item = new QListWidgetItem(ui->listWidget );
//    item1 = new QListWidgetItem(ui->listWidget );
//    ui->listWidget->addItem(item);
//    ui->listWidget->addItem(item1);
//    item->setSizeHint(QSize(30,50));
//    item1->setSizeHint(QSize(30,50));
//    ui->listWidget->setItemWidget(item1,labelPix);

//    label1=new QLabel(label0);
//    label1->move(13,43);
//    label1->setMovie(pMovie1);
//    label1->setFixedSize(100,50);
//    label1->setScaledContents(true);
//    label1->raise();
//    pMovie1->start();

//    timers[3]=new QTimer(this);
//    timers[3]->start(100);
//    tmrCard=new QTimer(this);
//    tmrCard->start(100);

//    new PeaShooter(300,100,this);

//    qDebug()<<static_cast<int>(this);
//    ui->listWidget->installEventFilter(this);

//    QPixmap p0(interfaceFilePre+"ShovelBack.png");
//    ui->testPushButton->setIcon(QIcon(p0));
//    ui->testPushButton->setIconSize(p0.size());

    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_2->setFrameShape(QListWidget::NoFrame);
    ui->listWidget->setIconSize(QSize(CARD_W,CARD_H));
    ui->listWidget_2->setIconSize(QSize(CARD_W+3,CARD_H));
    ui->chooserBgd->setPixmap(QPixmap(interfaceFilePre+"SeedChooser_Background.png"));
    game->state=SELECT;
    game->curPltId=-1;
//    game.state=SELECT;
//    game.curPltId=-1;
//    PlantCard::setState(game->state);

    for(int i=0;i<NUM_PLANT;i++){
        card=new PlantCard(ui->listWidget_2,i);
        ui->listWidget_2->addItem(card);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;

}

//bool MainWindow::eventFilter(QObject *target, QEvent *event)
//{
//    if (event->type() == QEvent::MouseButtonPress) {
//        qDebug()<<"filter mouse pressed";
//    }
//    else if(event->type() == QEvent::MouseMove){
//        qDebug()<<"filter mouse move";
//        mouseMoveEvent((QMouseEvent*)event);
//        return 1;
//    }
////    qDebug()<<"filter";
////    if(target==button)
////    return QMainWindow::eventFilter(target,event);
//    return 0;
//}

//void MainWindow::addCardsRatio() {
//    int cnt=ui->listWidget->count();
//    for(int i=0;i<cnt;i++){
//        card=(PlantCard*)ui->listWidget->item(i);
//        card->addRatio();
//    }
//}

void MainWindow::showOrHideSelect(bool show) {
    if(show){
        game->state=SELECT;
//        PlantCard::setState(SELECT);
        int cnt=ui->listWidget_2->count();
        for(int i=0;i<cnt;i++){
            card=(PlantCard*)ui->listWidget_2->item(i);
            card->setChecked(0);
        }
        ui->listWidget->clear();

        ui->listWidget_2->show();
        ui->chooserBgd->show();
        ui->verify->show();
        ui->reset->show();
    }
    else{
        game->state=PLANT;
//        PlantCard::setState(PLANT);
//        int cnt=ui->listWidget->count();
//        for(int i=0;i<cnt;i++){
//            card=(PlantCard*)ui->listWidget->item(i);
//            if(getSunNum(card->getPltId())>game->sunNum)
//                card->setChecked(1);
//        }
        checkWidgetList();
        ui->listWidget_2->hide();
        ui->chooserBgd->hide();
        ui->verify->hide();
        ui->reset->hide();
    }
}

void MainWindow::checkWidgetList()
{
    int cnt=ui->listWidget->count();
    qDebug()<<"check list";
    for(int i=0;i<cnt;i++){
        card=(PlantCard*)ui->listWidget->item(i);
//        if(getSunNum(card->getPltId())>game->sunNum)
//            card->updateImg();
//        card->setChecked(1);
        card->updateImg();
    }
}
//void MainWindow::on_pushButton_clicked()
//{
//    ui->listWidget->takeItem(0);
//}

//void MainWindow::on_pushButton_2_clicked()
//{

////    PlantCard *card=new PlantCard(ui->listWidget,isBomb);
////    ui->listWidget->addItem(pltcard);
////    isBomb++;
//    qDebug()<<"add";
//}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int cnt=ui->listWidget->count();
    int pltId=game->curPltId;
    if(event->button()==Qt::LeftButton)
    {//确定
        qDebug()<<"press "<<event->pos();
        game->cursorPos=event->pos();
        if(!game->clicked(1)||pltId<0)
            return;
        for(int i=0;i<cnt;i++){
            card=(PlantCard*)ui->listWidget->item(i);
            if(pltId==card->getPltId()){
                card->setChecked(1);
                break;
            }
        }

    }
    else{
//        game.curPltId=-1;//取消选择
        game->clicked(0);

    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(game->curPltId>=0||game->state==SHOVEL){
//        qDebug()<<"move1 "<<event->pos();
        game->cursorPos=event->pos();
        game->updateCursorPix();
    }

//    qDebug()<<"move2 "<<event->pos();

//    game.cursorPos=event->pos();
//        // 这里必须使用buttons()
//        if(event->buttons() & Qt::LeftButton) //进行的按位与
//        {
//           qDebug()<<"move2 "<<event->pos();
//        }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    card=(PlantCard*)item;
    int pltId;
    if(!card->isChecked())
        pltId=card->getPltId();
    else
        return;
    if(game->state==SELECT){
        int row=ui->listWidget->row(item);
        ui->listWidget->takeItem(row);
        card=(PlantCard*)ui->listWidget_2->item(pltId);
        card->setChecked(0);
    }
    else if(game->state==PLANT){
        game->curPltId=pltId;
//        game.updateCursorPix();

    }
}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    card=(PlantCard*)item;
    if(card->isChecked())
        return;
    int pltId=card->getPltId();
    card->setChecked(1);
    ui->listWidget->addItem(new PlantCard(ui->listWidget,pltId));

}

void MainWindow::on_verify_clicked()
{
    showOrHideSelect(0);
    game->initInfo();
}

void MainWindow::on_reset_clicked()
{
    showOrHideSelect(1);
//    ui->listWidget->clear();
}

//void MainWindow::on_testPushButton_clicked()
//{
//    qDebug()<<"pushed";
////    ui->testPushButton->setAttribute(Qt::WA_TransparentForMouseEvents,true);
////    ui->testPushButton->setAttribute(Qt::WA_NoMousePropagation,false);


//}

void MainWindow::on_quit_clicked()
{
    game->clrObjects();
    showOrHideSelect(1);
}

void MainWindow::on_pause_clicked()
{
    if(game->state==PAUSE){
//        game->state=PLANT;
        ui->pause->setText("暂停");
        game->setStart(1);
    }
    else if(game->state==PLANT){
//        game->state=PAUSE;
        ui->pause->setText("开始");
        game->setStart(0);
    }
}
