#ifndef BOARD_H
#define BOARD_H

//include required libraries
#include <vector>
#include "./shapes/cube.h"
using namespace std;

class Board
{
public:
    Vec3D center;
    int size;
    vector<vector<vector<Cube>>> board;

    Board(Vec3D center, int size, vector<vector<int>> boardWalls);
    Board(Vec3D center, int size, vector<vector<int>> boardWalls, vector<vector<int>> boardFloor);
    void draw(GLuint textures[]);
    void drawBox();
};

#endif