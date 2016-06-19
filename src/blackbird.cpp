#include "blackbird.h"

Blackbird::Blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
           :Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void Blackbird::ability()
{
    setLinearVelocity(b2Vec2(0,-100));
}

void Blackbird::setLinearVelocity(b2Vec2 velocity)
{
     g_body->SetLinearVelocity(velocity);
}
