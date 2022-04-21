//---------------------------------------------------------------------------------
/// @file Container.h
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#ifndef CONTAINER_H
#define CONTAINER_H
#include <ngl/Vec3.h>


struct Container
{
  float m_radius;
  ngl::Vec3 m_position;

  Container() : m_radius(20.f),
                m_position(ngl::Vec3::zero())
  {}

  ~Container()=default;

};
#endif // CONTAINER_H
