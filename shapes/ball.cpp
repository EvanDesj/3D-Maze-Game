#include "ball.h"
#include <iostream>
using namespace std;

Ball::Ball(Point3D position, float size, int rotationAngle)
{
    this->position = position;
    this->size = size;
    this->rotationAngle = rotationAngle;
    this->speed = 0.1;
}

Point3D Ball::nextPosition(float x, float y, float z)
{
    Point3D newPoint;
    newPoint.x = position.x + (x * speed);
    newPoint.y = position.y;
    newPoint.z = position.z + (-1 * z * speed);
    return newPoint;
}

bool positionsEqual(Point3D p1, Point3D p2)
{
    return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
}

void Ball::update(Point3D newPosition)
{
    if (!positionsEqual(position, newPosition))
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
}
