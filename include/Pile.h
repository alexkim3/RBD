#ifndef PILE_H
#define PILE_H
#include <array>
#include "Container.h"
#include <iostream>
#include <ngl/Random.h>
#include <tuple>

template<typename OBJECT, std::size_t N = 10>
struct Pile //collective movement of the balls
{
    std::array<OBJECT, N> m_objects;
    const Container &ball_container;

    Pile(const Container &ball_container_) :
         ball_container(ball_container_)
    {
        for(auto &&object : m_objects)
        {
            ngl::Vec3 rand_direction = ngl::Random::getRandomNormalizedVec3();
            ngl::Vec3 rand_position = ngl::Random::getRandomNormalizedVec3()*20;
            object.set(rand_direction, rand_position);
        }
    }

    void move()
    {
        for (auto &&object : m_objects)
        {
            if(collisiondetectOnY(object))
                object.bounceOnY();
            if(collisiondetectOnX(object))
                object.bounceOnX();
            if(collisiondetectOnZ(object))
                object.bounceOnZ();

            checkCollisionObjects(object);



            object.fall();
        }
    }
    void checkCollisionObjects(const OBJECT &object_)
    {
        for (int i = 0; i<m_objects.size(); ++i)
        {
            for (int j = 0; j<m_objects.size(); ++j)
            {
                if(i == j)
                    continue;
                if ((m_objects[i].position - m_objects[j].position).length() < object_.radius*2)
                {
                    object_.reflectedVector(i, j);
                    std::cout<<"Collided " << "\n";
                }
            }
        }
    }

    bool collisiondetectOnY(const OBJECT &object_)
    {
        if (object_.position.m_y < -(ball_container.radius+object_.radius))
            return true;
        else
            return false;
    }

    bool collisiondetectOnX(const OBJECT &object_)
    {
        if ((object_.position.m_x > (ball_container.radius-object_.radius)) || (object_.position.m_x < -(ball_container.radius+object_.radius)))
            return true;
        else
            return false;
    }

    bool collisiondetectOnZ(const OBJECT &object_)
    {
        if ((object_.position.m_z > (ball_container.radius-object_.radius)) || (object_.position.m_z < -(ball_container.radius+object_.radius)))
            return true;
        else
            return false;
    }
};

#endif // PILE_H
