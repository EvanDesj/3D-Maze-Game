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

void Cube::drawBox(GLfloat size)
{
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(GL_POLYGON);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v [ faces[i][0] ] [0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}