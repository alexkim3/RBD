#ifndef BALL_H
#define BALL_H
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Container.h"


struct Ball
{
    ngl::Vec3 direction;
    float speed;
    float radius;
    ngl::Vec3 position;


    Ball() : direction(ngl::Vec3::down()),
                   speed(0.01f),
                   radius(0.05f),
                   position(ngl::Vec3::zero())

    {}

    ~Ball() = default;

    void fall();
    bool collide();
};

#endif // BALL_H
