#include "shape.h"
#include "../utils/colour.h"
#include "../utils/material.h"
#include "../utils/mathLib3D.h"

Shape::Shape(Vec3D center, Vec3D size, Vec3D rotationAngle, Colour colour, Material material)
{
    this->center = center;
    this->size = size;
    this->rotationAngle = rotationAngle;
    this->colour = colour;
    this->material = material;
};