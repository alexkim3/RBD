#ifndef BALL_H
#define BALL_H
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Pile.h"
#include "Container.h"

struct Ball
{
    static size_t instance_id;
    const size_t id;
    ngl::Vec3 velocity = ngl::Vec3::zero();
    float radius = 2.f;
    ngl::Vec3 position;
    double m_gravity = 0.005f;
    float dampingY = 0.0f;
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

    void setGravity(double _gravity);
    void setDamping(double _dampingY);
};

#endif // BALL_H
