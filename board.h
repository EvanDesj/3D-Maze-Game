#ifndef BOARD_H
#define BOARD_H

//include required libraries
#include <vector>
#include "./shapes/cube.h"

class Board
{
public:
    Vec3D center;
    int size;
    std::vector<std::vector<Cube>> board;

    Board(Vec3D center, int size);
    void draw();
    void rotate(Vec3D rotate);
};

#endif