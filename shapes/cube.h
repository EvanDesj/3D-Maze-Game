#ifndef CUBE_H
#define CUBE_H

// Include required libraries
#include "shape.h"
#include "../utils/colour.h"
#include "../utils/material.h"
#include "../utils/mathLib3D.h"

class Cube : public Shape
{
public:
    Vec3D center;
    Vec3D size;
    Vec3D rotationAngle;
    Colour colour;
    Material material;

    Cube(Vec3D center, Vec3D size, Vec3D rotationAngle, Colour colour, Material material);

    void draw();
};

#endif