/*
Final Project:
    - Name: Evan Desjardine
    - Student ID: desjarde
    - Email: [desjarde@mcmaster.ca](mailto:desjarde@mcmaster.ca)
    - Operating System: Windows 10
*/

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

// include standard libraries
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "camera.h"
#include "board.h"

// Define GLUT Constants
#define WINDOW_TITLE "3GC3 Final Project"

int timerFunc = 20;
int windowWidth = 800;
int windowHeight = 600;

std::vector<std::vector <int>> board
{
    {1,1,1,1,1},
    {0,0,1,0,0},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1}
};

CameraSystem camera = CameraSystem();
Board gameBoard = Board(board);

// Display Callback Function
void display()
{
    // Clear and prepare
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0, 0, 0, camera.rotX, camera.rotY, camera.rotZ);
    glColor3f(1, 1, 1);

    // glPushMatrix();
    // glScalef(10, 1, 10);
    // glutSolidCube(1);
    // glPopMatrix();
    gameBoard.draw();
    // Swap Buffers
    glutSwapBuffers();
};

// Animate Callback Function
void animate(int v)
{

    // Redraw
    glutPostRedisplay();

    // Call this function again in 20 milliseconds
    glutTimerFunc(timerFunc, animate, 0);
};

// Reshape Callback Function
void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
};

// Keyboard Callback Function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q': case 'Q':
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
};

// Special Keyboard Callback Function
void specialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    default:
        break;
    }
    glutPostRedisplay();
};

// Mouse Callback Function
void mouse(int button, int state, int x, int y)
{
    y = windowHeight - y;
    glutPostRedisplay();
};

// Mouse Motion Callback Function
void mouseMotion(int x, int y)
{
    y = windowHeight - y;
};

// Mouse Passive Motion Callback Function
void mousePassiveMotion(int x, int y)
{
    y = windowHeight - y;
};

// Glut Initialization Function
void init()
{
    // Prepare the window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(WINDOW_TITLE);
    // Set background colour
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Set up the viewport
    glViewport(0, 0, windowWidth, windowHeight);
    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
};

// Print Program Instructions
void printInstructions()
{
    using namespace std;
    cout << "Program Instructions:" << endl;
};

// Main program
int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    // Initialize the window
    init();
    
    // Bind callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassiveMotion);

    // Animate function
    glutTimerFunc(timerFunc, animate, 0);

    // Set-Up 3D
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    
    // Start the main loop
    glutMainLoop();
};