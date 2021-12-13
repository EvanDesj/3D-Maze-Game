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
#include "./shapes/cube.h"
#include <vector>
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
                                        0.3f)));

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
                                            0.3f)));
            
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
                                            0.3f)));
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
                                            Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                            Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                            Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                            0.3f)));
            }
            else //0 at position in floorInput, add a cube with 0 size, this won't be rendered
            {
                floorRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                        Material(
                                            Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                            Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                            Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                            0.3f)));
            }
            
            //check if 1 at position in wallInput, push a cube to wallsRow at that positition if true
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
                                            0.3f)));
            
            }
            else //0 at position in wallInput, add a cube with 0 size, this won't be rendered
            {
                wallsRow.push_back(Cube(Vec3D(this->center.x + i, this->center.y + 1, this->center.z + k),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Vec3D(0.0f, 0.0f, 0.0f),
                                        Colour(1, 0, 1, 1.0f),
                                        Material(
                                            Colour(0.36f, 0.27f, 0.54f, 1.0f),
                                            Colour(0.30f, 0.20f, 0.50f, 1.0f),
                                            Colour(0.45f, 0.35f, 0.70f, 1.0f),
                                            0.3f)));
            }
        }
        wallsBoard.push_back(wallsRow);
        floorBoard.push_back(floorRow);
    }
    board.push_back(floorBoard);
    board.push_back(wallsBoard);
    this->board = board;
}


void Board::draw() {
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
                if (this->board.at(i).at(j).at(k).size.x != 0)
                {
                    this->board.at(i).at(j).at(k).draw();
                }
            }
        }
    }
}