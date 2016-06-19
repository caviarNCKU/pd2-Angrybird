#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/image/background.png").scaled(800, 600));
    QGraphicsPixmapItem *bow = new QGraphicsPixmapItem();
    QPixmap shooter;
    shooter.load(":/image/shooter.png");
    shooter = shooter.scaled(40,100);
    bow->setPixmap(shooter);
    bow->setPos(80,400);
    ui->graphicsView->scene()->addItem(bow);

    QGraphicsPixmapItem *restart = new QGraphicsPixmapItem();
    QPixmap restarter;
    restarter.load(":/image/restart.png");
    restarter = restarter.scaled(90,90);
    restart->setPixmap(restarter);
    restart->setPos(10,10);
    ui->graphicsView->scene()->addItem(restart);

    QGraphicsPixmapItem *quit = new QGraphicsPixmapItem();
    QPixmap quiter;
    quiter.load(":/image/exit.png");
    quiter = quiter.scaled(90,90);
    quit->setPixmap(quiter);
    quit->setPos(700,10);
    ui->graphicsView->scene()->addItem(quit);

    birdstatus = 0;
    deletestatus = 0;
    formbird = 0;
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(40,30),QSizeF(800,600));
    // Create ground
    itemList.push_back(new Land(20,2.5,40,5,QPixmap(":/ground.png").scaled(width(),height()/6),world,scene));
    // Create enemy
    piggy = new Pig(32.0f,5.0f,1.15f,&timer,QPixmap(":/image/pig.png").scaled(46,46),world,scene);
    itemList.push_back(piggy);
    // Create Log
    log1 = new Log(30.0f,10.0f,0.5f,5.125f,&timer,QPixmap(":/image/thinwood1.png").scaled(10,102.5),world,scene);
    log2 = new Log(34.0f,10.0f,0.5f,5.125f,&timer,QPixmap(":/image/thinwood1.png").scaled(10,102.5),world,scene);
    log3 = new Log(32.0f,15.0f,5.125f,0.5f,&timer,QPixmap(":/image/thinwood.png").scaled(102.5,10),world,scene);
    itemList.push_back(log1);
    itemList.push_back(log2);
    itemList.push_back(log3);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);

    if(event->type() == QEvent::MouseButtonPress)
    {
        pressX = keyEvent->pos().x();
        pressY = keyEvent->pos().y();
        if((pressX>=655)&&(pressX<=745)&&(pressY>=-80)&&(pressY<=100)){
            emit quitGame();
        }
        if((pressX>=-80)&&(pressX<=100)&&(pressY>=-80)&&(pressY<=100)){
            Restart();
            deletestatus+=1;
        }
        std::cout << "Press !" << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        releaseX = keyEvent->pos().x();
        releaseY = keyEvent->pos().y();
        distanceX = pressX - releaseX;
        distanceY = releaseY - pressY;
        Vx = distanceX/5.0;
        Vy = distanceY/5.0;
        /*if(deletestatus>0){
            if(red_bird != NULL){
                delete red_bird;
                deletestatus = 0;

            }
            if(black_bird != NULL){
                delete black_bird;
                deletestatus = 0;
            }
            if(white_bird != NULL){
                delete white_bird;
                deletestatus = 0;
            }
            if(green_bird != NULL){
                delete green_bird;
                deletestatus = 0;
            }
        }*/
        if(birdstatus ==0 ){
            red_bird = new Bird(1.0f,5.0f,1.15f,&timer,QPixmap(":/bird.png").scaled(46,46),world,scene);
            itemList.push_back(red_bird);
            red_bird->setLinearVelocity(b2Vec2(Vx,Vy));
        }
        else if(birdstatus == 1){
            delete red_bird;
            green_bird = new Greenbird(1.0f,5.0f,1.15f,&timer,QPixmap(":/image/green.png").scaled(46,46),world,scene);
            itemList.push_back(green_bird);
            green_bird->setLinearVelocity(b2Vec2(Vx,Vy));

        }
        else if(birdstatus == 2){
            green_bird->ability();
        }
        else if(birdstatus ==3 ){
            delete green_bird;
            black_bird = new Blackbird(1.0f,5.0f,1.15f,&timer,QPixmap(":/image/black.png").scaled(46,46),world,scene);
            itemList.push_back(black_bird);
            black_bird->setLinearVelocity(b2Vec2(Vx,Vy));
        }
        else if(birdstatus ==4){
            black_bird->ability();
        }
        else if(birdstatus ==5){
            delete black_bird;
            white_bird = new Whitebird(1.0f,5.0f,1.15f,&timer,QPixmap(":/image/white.png").scaled(46,46),world,scene);
            itemList.push_back(white_bird);
            white_bird->setLinearVelocity(b2Vec2(Vx,Vy));
        }
        else if(birdstatus ==6){
            white_bird->ability();
        }
        birdstatus++;

        if(birdstatus >6) {
            delete white_bird;
            birdstatus = 0;
        }
        std::cout << "Release !" << std::endl ;
        std::cout << birdstatus << std::endl ;
        return true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::Restart()
{
    delete piggy;
    delete log1;
    delete log2;
    delete log3;
    birdstatus = -1;
    piggy = new Pig(32.0f,5.0f,1.15f,&timer,QPixmap(":/image/pig.png").scaled(46,46),world,scene);
    itemList.push_back(piggy);
    log1 = new Log(30.0f,10.0f,0.5f,5.125f,&timer,QPixmap(":/image/thinwood1.png").scaled(10,102.5),world,scene);
    log2 = new Log(34.0f,10.0f,0.5f,5.125f,&timer,QPixmap(":/image/thinwood1.png").scaled(10,102.5),world,scene);
    log3 = new Log(32.0f,15.0f,5.125f,0.5f,&timer,QPixmap(":/image/thinwood.png").scaled(102.5,10),world,scene);
    itemList.push_back(log1);
    itemList.push_back(log2);
    itemList.push_back(log3);
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    close();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
