//---------------------------------------------------------------------------------
/// @file Ball.h
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#ifndef BALL_H
#define BALL_H
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Container.h"

struct Ball
{
  static size_t s_instance_id;
  const size_t c_id;
  ngl::Vec3 m_velocity;
  float m_radius;
  ngl::Vec3 m_position;
  double m_gravity;
  float m_dampingY;
  float m_dampingXZ;

  Ball();

  ~Ball() = default;

  void fall();
  void bounceOnY();
  void bounceOnX();
  void bounceOnZ();
  void set(ngl::Vec3 &dir_, ngl::Vec3 &pos_);
  void reflectedVector();
  double getGravity()    const {return m_gravity;}


};

#endif // BALL_H
