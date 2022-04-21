//---------------------------------------------------------------------------------
/// @file Ball.cpp
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#include "Ball.h"
#include "iostream"
#include <cstdlib>

size_t Ball::s_instance_id = 0;

Ball::Ball() : c_id(++s_instance_id),
               m_velocity(ngl::Vec3::zero()),
               m_radius(2.f),
               m_position(ngl::Vec3::zero()),
               m_gravity(0.005f),
               m_dampingY(0.9f),
               m_dampingXZ(0.995)
{}


void Ball::fall()
{

  m_position += m_velocity;
  m_velocity.m_y -= m_gravity;
  m_velocity.m_x *= m_dampingXZ;
  m_velocity.m_z *= m_dampingXZ;

/*
    std::cout << "x: " << Ball::m_position.m_x <<
              " y: " << Ball::m_position.m_y <<
              " z: " << Ball::m_position.m_z << "\n";*/

    /*
    std::cout <<" m_velocity X: " << Ball::m_velocity.m_x <<
              " Y: " << Ball::m_velocity.m_y <<
              " Z: " << Ball::m_velocity.m_z << "\n";*/
}

void Ball::set(ngl::Vec3 &dir_, ngl::Vec3 &pos_)
{
  m_velocity = dir_/4;
  //std::cout<< dir_.m_x<<" " << dir_.m_y<< " "<< dir_.m_z<< " "<< "\n";
  m_position = pos_;


}

void Ball::bounceOnY()
{
  //std::cout<<"Bounced" << "\n";
  m_velocity.m_y *= -1;
  m_velocity.m_y *= m_dampingY;
}

void Ball::bounceOnX()
{
  m_velocity.m_x *= -1;
}

void Ball::bounceOnZ()
{
  m_velocity.m_z *= -1;
}

void Ball::reflectedVector()
{
  m_velocity.m_x *= -1;
  m_velocity.m_z *= -1;
    //std::cout << "reflected " << std::endl;
}
