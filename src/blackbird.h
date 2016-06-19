#ifndef BLACKBIRD_H
#define BLACKBIRD_H
#include <bird.h>
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Blackbird : public Bird
{
public:
    Blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void ability();
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BLACKBIRD_H
