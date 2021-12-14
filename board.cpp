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

#include "board.h"
#include "./shapes/shape.h"
#include <math.h>
#include <iostream>

Board::Board(Vec3D center, int size)
{
    this->center = center;
    this->size = size;

    //create the gameboard
    std::vector<std::vector<Cube>> board;

    //boards that have even length and width (like 8x8) do not have a center cube, meaning more camera and board math
    //may not allow that type of board to exist, but this works for now.
    float indexLimit = ((this->size - 1) / 2.0f);

    //i is the x pos of a cube, j is the z pos
    for (int i = (int)(ceil(indexLimit) * -1); i <= (int)(floor(indexLimit)); i++)
    {
        std::vector<Cube> row;
        for (int j = (int)(ceil(indexLimit) * -1); j <= (int)(floor(indexLimit)); j++)
        {
            row.push_back(Cube(Vec3D(i + this->center.x, 0.0f, j + this->center.y),
                               Vec3D(1.0f, 1.0f, 1.0f),
                               Vec3D(0.0f, 0.0f, 0.0f),
                               Colour(0.36f, 0.27f, 0.54f, 1.0f),
                               Material(
                                   Colour(0.0f, 0.0f, 0.0f, 1.0f),
                                   Colour(0.50f, 0.5f, 0.50f, 1.0f),
                                   Colour(0.20f, 0.15f, 0.20f, 1.0f),
                                   15.0f)));
        }
        board.push_back(row);
    }
    this->board = board;
}

void Board::draw()
{
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            this->board[i][j].draw();
        }
    }
}

void Board::rotate(Vec3D rotate)
{
    //float indexLimit = (this->size - 1) / 2;
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            this->board[i][j].rotationAngle = this->board[i][j].rotationAngle.add(rotate);
        }
    }
}

void Board::drawBox() {
  GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  GLint faces[6][4] =
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

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1 / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1 / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1 / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1 / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1 / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = 1 / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(GL_POLYGON);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}