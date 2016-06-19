#include "whitebird.h"

Whitebird::Whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
        :Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void Whitebird::ability()
{
    setLinearVelocity(b2Vec2(50,0));
}

void Whitebird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
