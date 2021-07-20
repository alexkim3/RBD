#include "Ball.h"
#include "iostream"
#include <cstdlib>

size_t Ball::instance_id = 0;

Ball::Ball() : id(++instance_id),
               velocity(ngl::Vec3::zero()),
               radius(2.f),
               position(ngl::Vec3::zero()),
               gravity(0.005f),
               dampingY(0.9f),
               dampingXZ(0.995)
{}

void Ball::fall()
{

    Ball::position += Ball::velocity;
    Ball::velocity.m_y -= Ball::gravity;
    Ball::velocity.m_x *= Ball::dampingXZ;
    Ball::velocity.m_z *= Ball::dampingXZ;


    std::cout << "x: " << Ball::position.m_x <<
              " y: " << Ball::position.m_y <<
              " z: " << Ball::position.m_z << "\n";

    /*
    std::cout <<" velocity X: " << Ball::velocity.m_x <<
              " Y: " << Ball::velocity.m_y <<
              " Z: " << Ball::velocity.m_z << "\n";*/
}

void Ball::set(ngl::Vec3 &dir_, ngl::Vec3 &pos_)
{
    Ball::velocity = dir_/4;
    //std::cout<< dir_.m_x<<" " << dir_.m_y<< " "<< dir_.m_z<< " "<< "\n";
    Ball::position = pos_;


}

void Ball::bounceOnY()
{
    std::cout<<"Bounced" << "\n";
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

void Ball::reflectedVector(ngl::Vec3 &moving_vec, ngl::Vec3 &reflection_plane)
{
    ngl::Vec3 inversed_vec = (-moving_vec.m_x, moving_vec.m_y, moving_vec.m_z);
    float scalar = ((inversed_vec.m_x*reflection_plane.m_x) +
                    (inversed_vec.m_y*reflection_plane.m_y) +
                    (inversed_vec.m_z*reflection_plane.m_z) / ((reflection_plane.m_x * reflection_plane.m_x)+
                                                               (reflection_plane.m_y * reflection_plane.m_y)+
                                                               (reflection_plane.m_z * reflection_plane.m_z)));
    ngl::Vec3 new_vector = (inversed_vec.m_x *scalar, inversed_vec.m_y * scalar, inversed_vec.m_z * scalar);
    velocity = new_vector;

}
