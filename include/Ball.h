#ifndef BALL_H
#define BALL_H
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Container.h"

struct Ball
{
    static size_t instance_id;
    const size_t id;
    ngl::Vec3 velocity;
    float radius;
    ngl::Vec3 position;
    float gravity;
    float dampingY;
    float dampingXZ;

    Ball();

    ~Ball() = default;

    void fall();
    void bounceOnY();
    void bounceOnX();
    void bounceOnZ();
    void set(ngl::Vec3 &dir_, ngl::Vec3 &pos_);
    void reflectedVector(ngl::Vec3 &moving_vec, ngl::Vec3 &reflection_plane);


};

#endif // BALL_H
