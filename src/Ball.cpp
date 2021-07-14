#include "Ball.h"


void Ball::fall()
{
    Ball::position += Ball::direction * Ball::speed;
}

/*
bool Ball::collide()
{
    //if x and z are in sphere and y in the line dist
}*/
