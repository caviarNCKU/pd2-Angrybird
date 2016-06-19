#ifndef LOG_H
#define LOG_H

#include <gameitem.h>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#define LOG_DENSITY 10.0f
#define LOG_FRICTION 0.8f
#define LOG_RESTITUTION 0.5f

class Log : public GameItem
{
public:
    Log(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // LOG_H
