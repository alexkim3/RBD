#ifndef BALL_H
#define BALL_H
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Container.h"

struct Ball
{
    static size_t instance_id;
    const size_t id;
    ngl::Vec3 velocity = ngl::Vec3::zero();
    float radius = 2.f;
    ngl::Vec3 position;
    double m_gravity = 0.0f;
    float dampingY = 0.9f;
    float dampingXZ = 0.995f;

    Ball();

    ~Ball() = default;

    void fall();
    void bounceOnY();
    void bounceOnX();
    void bounceOnZ();
    void set(ngl::Vec3 &dir_, ngl::Vec3 &pos_);
    void reflectedVector();
    double getGravity() const
    {
        return m_gravity;
    }


};

#endif // BALL_H
