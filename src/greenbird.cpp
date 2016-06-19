#include "greenbird.h"

Greenbird::Greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
            :Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void Greenbird::ability()
{
    g_pixmap.setPixmap(QPixmap(":/image/green.png").scaled(92,92));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
}
