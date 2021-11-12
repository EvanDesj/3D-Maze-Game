#include "ball.h"
#include <iostream>
using namespace std;

Ball::Ball(Point3D position, Vec3D direction, float size, int rotationAngle)
{
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->rotationAngle = rotationAngle;
    this->speed = 0.1;
}

void Ball::update(float x, float y, float z)
{
    position.x = position.x + (x * speed);
    position.y = position.y + (y * speed);
    position.z = position.z + (-1 * z * speed);
    if (rotationAngle <= 339)
    {
        rotationAngle += 20;
    }
    else
    {
        rotationAngle = 0;
    }
}