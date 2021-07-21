#include "Ball.h"
#include "iostream"
#include <cstdlib>

size_t Ball::instance_id = 0;

Ball::Ball() : id(++instance_id)
{}

void Ball::setGravity(double _gravity)
{
    m_gravity = _gravity;
    std:: cout << "gravity: " << m_gravity << "\n";

}

void Ball::setDamping(double _dampingY)
{
   dampingY =  _dampingY;
}

void Ball::fall()
{

    Ball::position += Ball::velocity;
    Ball::velocity.m_y -= Ball::m_gravity;
    Ball::velocity.m_x *= Ball::dampingXZ;
    Ball::velocity.m_z *= Ball::dampingXZ;

/*
    std::cout << "x: " << Ball::position.m_x <<
              " y: " << Ball::position.m_y <<
              " z: " << Ball::position.m_z << "\n";*/


    std::cout <<" velocity X: " << Ball::velocity.m_x <<
              " Y: " << Ball::velocity.m_y <<
              " Z: " << Ball::velocity.m_z << "\n";
}

void Ball::set(ngl::Vec3 &dir_, ngl::Vec3 &pos_)
{
    Ball::velocity = dir_/4;
    //std::cout<< dir_.m_x<<" " << dir_.m_y<< " "<< dir_.m_z<< " "<< "\n";
    Ball::position = pos_;


}

void Ball::bounceOnY()
{
    //std::cout<<"Bounced" << "\n";
    Ball::velocity.m_y *= -1;
    Ball::velocity.m_y *= Ball::dampingY;
}

void Ball::bounceOnX()
{
    Ball::velocity.m_x *= -1;
}

void Ball::bounceOnZ()
{
    Ball::velocity.m_z *= -1;
}

void Ball::reflectedVector()
{
    Ball::velocity = -velocity;
    //std::cout << "reflected " << std::endl;
}
