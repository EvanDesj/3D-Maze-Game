#ifndef SHAPE_H
#define SHAPE_H

// Include required libraries
#include "./utils/colour.h"
#include "./utils/material.h"
#include "mathLib3D.h"

class Shape
{
public:
    Vec3D center;
    Vec3D size;
    Colour colour;
    Material material;

    Shape(Vec3D center, Vec3D size, Colour colour, Material material);

    void draw();
};

#endif