// Include the header file for syntax
#include "cube.h"
#include "shape.h"
#include "../utils/colour.h"
#include "../utils/material.h"
#include "../utils/mathLib3D.h"

// Include OpenGL/GLUT Libraries
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

Cube::Cube(Vec3D center, Vec3D size, Vec3D rotationAngle, Colour colour, Material material, int texture)
    : Shape(center, size, rotationAngle, colour, material)
{
            this->center = center;
            this->size = size;
            this->rotationAngle = rotationAngle;
            this->colour = colour;
            this->material = material;
            this->texture = texture;
}

void Cube::draw()
{
    glPushMatrix();

    // Apply transformations
    glTranslatef(this->center.x, this->center.y, this->center.z);
    glScalef(this->size.x, this->size.y, this->size.z);
    glRotatef(this->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotationAngle.z, 0.0f, 0.0f, 1.0f);

    // Draw the cube
    glNormal3f(0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();
}