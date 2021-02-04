#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QLabel>
#include <QMap>
#include <QDebug>
#include <QMovie>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>
enum {SELECT,PLANT,SHOVEL,PAUSE,END};

enum {CYCLE_BLT=10,CYCLE_ZMB=70,CYCLE_COLD=130,CYCLE_PUT=10000};

enum {CARD_W=100,CARD_H=62,CELL_W=81,CELL_H=97,
      ROW_NUM=5,COL_NUM=9,MAX_W=910,MAX_H=592
};
enum {UP,DOWN,LEFT,RIGHT};

enum {GAP_MOV=1,NUM_PLANT=6,GAP2BOTTOM=6,BORDER=10,ZMB_BORDER=78};

//int max_w,
const QRect lawnRect(125,78,CELL_W*COL_NUM,CELL_H*ROW_NUM);
const QString pltFilePre="../resource/Plants/";
const QString cardFilePre="../resource/Card/";
const QString interfaceFilePre="../resource/Interface/";
const QString zmbFilePre="../resource/Zombies/";

int getSunNum(int pltId);

#endif // CONFIG_H
