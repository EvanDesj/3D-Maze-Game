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
#include "./shapes/cube.h"
#include <vector>
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
                                   Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                   Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                   Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                   0.3f)));
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