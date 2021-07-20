#ifndef CONTAINER_H
#define CONTAINER_H
#include <ngl/Vec3.h>


struct Container
{
    float radius;
    ngl::Vec3 position;

    Container() : radius(20.f),
                  position(ngl::Vec3::zero())
    {}

    ~Container()=default;

};
#endif // CONTAINER_H
