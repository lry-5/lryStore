#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QMouseEvent>
#include <QtAlgorithms>
#include <QTimer>
#include "ui_mainwindow.h"

#include "plantcard.h"
#include "game.h"
namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    bool eventFilter(QObject *target,QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

//    void addCardsRatio();
    void showOrHideSelect(bool show);
    void checkWidgetList();
private slots:

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_verify_clicked();

    void on_reset_clicked();

//    void on_testPushButton_clicked();

    void on_quit_clicked();

    void on_pause_clicked();

private:
    Ui::MainWindow *ui;
//    Game game;
    Game* game;
    Plant* plt;
//    int isBomb;
    PlantCard *card;
//    int curPltId;
//    char state;

//    int x,y;
//    QTimer* tmrCard;
//    QTimer* timers[4];
};

#endif // MAINWINDOW_H



