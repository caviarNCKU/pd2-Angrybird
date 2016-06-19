#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>



#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <whitebird.h>
#include <greenbird.h>
#include <blackbird.h>
#include <log.h>
#include <pig.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    Bird *red_bird;
    Greenbird *green_bird;
    Blackbird *black_bird;
    Whitebird *white_bird;
    Pig *piggy;
    Log *log1;
    Log *log2;
    Log *log3;
    int deletestatus;
    void Restart();
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    int pressX;
    int pressY;
    int releaseX;
    int releaseY;
    int distanceX;
    int distanceY;
    int birdstatus;
    int formbird;
    float currentX;
    float currentY;
    float Vx,Vy;

};

#endif // MAINWINDOW_H
