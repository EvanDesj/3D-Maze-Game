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
#include <vector>

Board::Board(std::vector<std::vector <int>> vect) {
    this->vect = vect;
    this->rows = vect.size();
    this->cols = vect[0].size();
}

// void Board::tiltX() {
//     for(int i = 0; i < this->rows; i++) {
//         for(int j = 0; j < this->cols; j++) {
//             if (this->vect[i][j] == 1) {
                
//             }
//         }
//     }
// }
//     void tiltY();
//     void tiltZ();

void Board::draw() {
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            if (this->vect[i][j] == 1) {
                glPushMatrix();
                glTranslatef(i - 2, 0, j - 2);
                glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
}