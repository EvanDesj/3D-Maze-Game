#ifndef BALL_H
#define BALL_H

#include "../utils/mathLib3D.h"

class Ball
{
public:
    Point3D position;
    Vec3D direction;
    float size;
    int rotationAngle;
    float speed;
    Ball(Point3D position, Vec3D direction, float size, int rotationAngle);
    void update(Point3D newPosition);
    Point3D nextPosition(float x, float y, float z);
    void draw();
};

#endif