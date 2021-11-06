#ifndef BOARD_H
#define BOARD_H

//include required libraries
#include <vector>

class Board
{
private:
    int rows;
    int cols;
    std::vector<std::vector <int>> vect;

public:
    Board(std::vector<std::vector <int>> vect);
    // void tiltX();
    // void tiltY();
    // void tiltZ();
    void draw();
};

#endif