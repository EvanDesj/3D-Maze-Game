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

#include "board.h"
#include "./shapes/shape.h"
#include <math.h>
#include <iostream>
using namespace std;

Board::Board(Vec3D center, int size, vector<vector<int>> wallInput)
{
    this->center = center;
    this->size = size;

    //vector to hold gameboard
    vector<vector<vector<Cube>>> board;

    //since we want board centred on the center point given,
    int lowerIndexLimit = (int) (-1 * ceil((this->size - 1) / 2.0f));
    int upperIndexLimit = (int) floor((this->size - 1) / 2.0f);

    //create arrays of cubes for the floor and walls
    vector<vector<Cube>> floorBoard;
    vector<vector<Cube>> wallsBoard;

    //i is the x pos of a cube, k is the z pos
    for (int i = lowerIndexLimit; i <= upperIndexLimit; i++)
    {
        vector<Cube> wallsRow;
        vector<Cube> floorRow;
        for (int k = lowerIndexLimit; k <= upperIndexLimit; k++)
        {
            //no floor vector, so cube is added for every floor position
            floorRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y, this->center.z + k),
                                    Vec3D(1.0f, 1.0f, 1.0f),
                                    Vec3D(0.0f, 0.0f, 0.0f),
                                    Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                    Material(
                                        Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                        Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                        Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                        0.3f),
                                    0));

            //check if 1 at position in walls vector, push a cube at that positition if true
            if (wallInput.at(i + (-1 * lowerIndexLimit)).at(k + (-1 * lowerIndexLimit)) == 1)
            {
                wallsRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y + 1, this->center.z + k),
                                        Vec3D(1.0f, 1.0f, 1.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(1, 0, 1, 1.0f),
                                        Material(
                                            Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                            Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                            Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                            0.3f),
                                        1));
            
            }
            else //0 at position in walls, add a cube with NULL position, this is checked for when drawing board
            {
                wallsRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y + 1, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(1, 0, 1, 1.0f),
                                        Material(
                                            Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                            Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                            Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                            0.3f),
                                        1));
            }
        }
        wallsBoard.push_back(wallsRow);
        floorBoard.push_back(floorRow);
    }
    board.push_back(floorBoard);
    board.push_back(wallsBoard);
    this->board = board;
}


Board::Board(Vec3D center, int size, vector<vector<int>> wallInput, vector<vector<int>> floorInput)
{
    this->center = center;
    this->size = size;

    //vector to hold gameboard
    vector<vector<vector<Cube>>> board;

    //since we want board centred on the center point given,
    int lowerIndexLimit = (int) (-1 * ceil((this->size - 1) / 2.0f));
    int upperIndexLimit = (int) floor((this->size - 1) / 2.0f);

    //create arrays of cubes for the floor and walls
    vector<vector<Cube>> floorBoard;
    vector<vector<Cube>> wallsBoard;

    //i is the x pos of a cube, k is the z pos
    for (int i = lowerIndexLimit; i <= upperIndexLimit; i++)
    {
        vector<Cube> wallsRow;
        vector<Cube> floorRow;
        for (int k = lowerIndexLimit; k <= upperIndexLimit; k++)
        {
            //check if 1 at position in floorInput, push a cube to floorRow at that positition if true
            if (floorInput.at(i + (-1 * lowerIndexLimit)).at(k + (-1 * lowerIndexLimit)) == 1)
            {
                floorRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                        Material(
                                            Colour(0.12f, 0.18f, 0.25f, 1.0f),
                                            Colour(0.67f, 0.65f, 0.5f, 1.0f),
                                            Colour(0.70f, 0.70f, 0.55f, 1.0f),
                                            0.0f),
                                        0));
            }
            else //0 at position in floorInput, add a cube with 0 size, this won't be rendered
            {
                floorRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                        Material(
                                            Colour(0.12f, 0.18f, 0.25f, 1.0f),
                                            Colour(0.67f, 0.65f, 0.5f, 1.0f),
                                            Colour(0.70f, 0.70f, 0.55f, 1.0f),
                                            0.0f),
                                        0));
            }
            
            //check if 1 at position in wallInput, push a cube to wallsRow at that positition if true
            if (wallInput.at(i + (-1 * lowerIndexLimit)).at(k + (-1 * lowerIndexLimit)) == 1)
            {
                wallsRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y + 1, this->center.z + k),
                                        Vec3D(1.0f, 1.0f, 1.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(1, 0, 1, 1.0f),
                                        Material(
                                            Colour(1, 0.95, 0.80, 1.0),
                                            Colour(1, 1, 1, 1.0),
                                            Colour(1, 1, 1, 1.0),
                                            0.0f),
                                        1));
            
            }
            else //0 at position in wallInput, add a cube with 0 size, this won't be rendered
            {
                wallsRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y + 1, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(1, 0, 1, 1.0f),
                                        Material(
                                            Colour(1, 0.95, 0.80, 1.0),
                                            Colour(1, 1, 1, 1.0),
                                            Colour(1, 1, 1, 1.0),
                                            0.0f),
                                        1));
            }
        }
        wallsBoard.push_back(wallsRow);
        floorBoard.push_back(floorRow);
    }
    board.push_back(floorBoard);
    board.push_back(wallsBoard);
    this->board = board;
}


void Board::draw(GLuint textures[]) {
    // cout << "enter draw" << endl;
    // cout << "board size: " << this->board.size() << endl;
    // cout << "inner board size: " << this->board.at(0).size() << endl;
    // cout << "this->size: " << this->size << endl;
    for (int i = 0; i < this->board.size(); i++)
    {    
        for (int j = 0; j < this->size; j++)
        {
            for (int k = 0; k < this->size; k++)
            {
                Cube currentCube = this->board.at(i).at(j).at(k);
                if (currentCube.size.x != 0)
                {   
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, currentCube.material.ambient.getColour());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, currentCube.material.diffuse.getColour());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, currentCube.material.specular.getColour());
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
                    glBindTexture(GL_TEXTURE_2D, textures[currentCube.texture]);
                    glPushMatrix();
                    glTranslatef(currentCube.center.x, currentCube.center.y, currentCube.center.z);
                    this->board.at(i).at(j).at(k).drawBox(1);
                    glPopMatrix();
                }
            }
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