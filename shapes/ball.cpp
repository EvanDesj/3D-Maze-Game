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

Point3D Ball::nextPosition(float x, float y, float z)
{
    Point3D newPoint;
    newPoint.x = position.x + (x * speed);
    newPoint.y = position.y + (y * speed);
    newPoint.z = position.z + (-1 * z * speed);
    return newPoint;
}

void Ball::update(Point3D newPosition)
{
    this->position = newPosition;
    if (rotationAngle <= 339)
    {
        rotationAngle += 20;
    }
    else
    {
        rotationAngle = 0;
    }
}