#ifndef CUBE_H
#define CUBE_H

// Include required libraries
#include "shape.h"
#include "../utils/colour.h"
#include "../utils/material.h"
#include "../utils/mathLib3D.h"
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>

class Cube : public Shape
{
public:
    Vec3D center;
    Vec3D size;
    Vec3D rotationAngle;
    Colour colour;
    Material material;
    int texture;

    Cube(Vec3D center, Vec3D size, Vec3D rotationAngle, Colour colour, Material material, int texture);

    void draw();
};

#endif