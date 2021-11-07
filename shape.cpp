// Include the header file for syntax
#include "shape.h"
#include "mathLib3D.h"
#include "colour.h"
#include "/material.h"

Shape::Shape(Vec3D center, Vec3D size, Colour colour, Material material)
{
    this->center = center;
    this->size = size;
    this->colour = colour;
    this->material = material;
};

void Shape::draw()
{
    //Placeholder, does nothing
};