//---------------------------------------------------------------------------------
/// @file Pile.h
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#ifndef PILE_H
#define PILE_H
#include <array>
#include "Container.h"
#include <iostream>
#include <ngl/Random.h>

template<typename OBJECT, std::size_t N = 6>
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
        {object.bounceOnY();}
      if(collisiondetectOnX(object))
        {object.bounceOnX();}
      if(collisiondetectOnZ(object))
        {object.bounceOnZ();}
      if(checkCollisionObjects(object))
        {object.reflectedVector();}
      object.fall();
    }
  }
  bool checkCollisionObjects(OBJECT &object_)
  {
    for (int i = 0; i<m_objects.size(); ++i)
    {
      for (int j = 0; j<m_objects.size(); ++j)
      {
        if(i == j)
          {continue;}
        else
        {
          if ((m_objects[i].m_position - m_objects[j].m_position).length() < object_.m_radius*2)
          {
            return true;
          }
        }
      }
    }
    return false;
  }


  bool collisiondetectOnY(const OBJECT &object_)
  {
    if (object_.m_position.m_y < -(ball_container.m_radius-object_.m_radius*2))
      {return true;}
    else
      {return false;}
  }

  bool collisiondetectOnX(const OBJECT &object_)
  {
    if ((object_.m_position.m_x > (ball_container.m_radius-object_.m_radius*2)) ||
        (object_.m_position.m_x < -(ball_container.m_radius+object_.m_radius*2)))
      {return true;}
    else
      {return false;}
  }

  bool collisiondetectOnZ(const OBJECT &object_)
  {
    if ((object_.m_position.m_z > (ball_container.m_radius-object_.m_radius*2)) ||
        (object_.m_position.m_z < -(ball_container.m_radius+object_.m_radius*2)))
      {return true;}
    else
      {return false;}
  }

};

#endif // PILE_H
