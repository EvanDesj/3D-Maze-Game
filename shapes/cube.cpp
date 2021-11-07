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
// If windows, include <windows.h> to get the API functions
#ifdef _WIN32
#include <windows.h>
#endif

Cube::Cube(Vec3D center, Vec3D size, Vec3D rotationAngle, Colour colour, Material material)
            : Shape(center, size, rotationAngle, colour, material)
{
    this->center = center;
    this->size = size;
    this->rotationAngle = rotationAngle;
    this->colour = colour;
    this->material = material;
};

void Cube::draw() {
    glPushMatrix();

    // Apply transformations
    glTranslatef(this->center.x, this->center.y, this->center.z);
    glScalef(this->size.x, this->size.y, this->size.z);
    glRotatef(this->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotationAngle.z, 0.0f, 0.0f, 1.0f);

    // Apply lighting from material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular.getColour());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);

    // Colour the cube
    glColor3f(this->colour.r, this->colour.g, this->colour.b);

    // Draw the cube
    glutSolidCube(1);
    glPopMatrix();
};