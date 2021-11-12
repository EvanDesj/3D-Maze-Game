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
#include "utils/objectLoader.h"
using namespace std;

// Define GLUT Constants
#define WINDOW_TITLE "3GC3 Final Project"

// Global variables for gameboard rotation increments
float xIncr = 0;
float yIncr = 0;
float zIncr = 0;
// ------------------------//

int timerFunc = 20;
int windowWidth = 800;
int windowHeight = 600;

objl::Loader Ball;
bool fileLoaded = false;
void loadBall()
{
    fileLoaded = Ball.LoadFile("shapes/ball.obj");
}

void drawFromObj(objl::Loader Object)
{
    if (fileLoaded)
    {
        for (int i = 0; i < Object.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = Object.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Indices.size(); j += 3)
            {
                glBegin(GL_TRIANGLES);

                glColor3f(1, 1, 1);
                int indice1 = curMesh.Indices[j];
                int indice2 = curMesh.Indices[j + 1];
                int indice3 = curMesh.Indices[j + 2];

                float ambient[4] = {curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z, 1};
                float diffuse[4] = {curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z, 1};
                float specular[4] = {curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z, 1};
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
                
                glNormal3f(curMesh.Vertices[indice1].Normal.X, curMesh.Vertices[indice1].Normal.Y, curMesh.Vertices[indice1].Normal.Z);
                glTexCoord2f(curMesh.Vertices[indice1].TextureCoordinate.X,curMesh.Vertices[indice1].TextureCoordinate.Y);
                glVertex3f(curMesh.Vertices[indice1].Position.X, curMesh.Vertices[indice1].Position.Y, curMesh.Vertices[indice1].Position.Z);

                glNormal3f(curMesh.Vertices[indice2].Normal.X, curMesh.Vertices[indice2].Normal.Y, curMesh.Vertices[indice2].Normal.Z);
                glTexCoord2f(curMesh.Vertices[indice2].TextureCoordinate.X,curMesh.Vertices[indice2].TextureCoordinate.Y);
                glVertex3f(curMesh.Vertices[indice2].Position.X, curMesh.Vertices[indice2].Position.Y, curMesh.Vertices[indice2].Position.Z);
                
                glNormal3f(curMesh.Vertices[indice3].Normal.X, curMesh.Vertices[indice3].Normal.Y, curMesh.Vertices[indice3].Normal.Z);
                glTexCoord2f(curMesh.Vertices[indice3].TextureCoordinate.X,curMesh.Vertices[indice3].TextureCoordinate.Y);
                glVertex3f(curMesh.Vertices[indice3].Position.X, curMesh.Vertices[indice3].Position.Y, curMesh.Vertices[indice3].Position.Z);

                glEnd();
            }
        }
    }
    return;
}

CameraSystem camera = CameraSystem();
Board gameBoard = Board(Vec3D(0, 0, 0), 5);

// Draw axis on board (for debugging help)
void drawAxis()
{
    glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();
}

// Display Callback Function
void display()
{
    // Clear and prepare
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0, 0, 0, camera.rotX, camera.rotY, camera.rotZ);
    glColor3f(1, 1, 1);

    //drawAxis(); <-- Helps to debug movement issues

    // Gameboard rotation code
    glPushMatrix();
    glRotatef(0 + xIncr, 1, 0, 0);
    glRotatef(0 + yIncr, 0, 1, 0);
    glRotatef(0 + zIncr, 0, 0, 1);
    gameBoard.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, 0);
    drawFromObj(Ball);
    glPopMatrix();
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
    case 27:
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'w':
    case 'W':
        camera.zoomIn();
        break;
    case 's':
    case 'S':
        camera.zoomOut();
        break;
    case 'a':
    case 'A':
        camera.moveLeft();
        break;
    case 'd':
    case 'D':
        camera.moveRight();
        break;
    case 'r':
    case 'R':
        camera.reset();
        //Gameboard rotation reset
        xIncr = 0;
        yIncr = 0;
        zIncr = 0;
        break;
    case 't':
    case 'T':
        gameBoard.rotate(Vec3D(1, 0, 0));
        break;
    case 'f':
    case 'F':
        gameBoard.rotate(Vec3D(0, 0, 1));
        break;
    case 'g':
    case 'G':
        gameBoard.rotate(Vec3D(-1, 0, 0));
        break;
    case 'v':
    case 'V':
        gameBoard.rotate(Vec3D(0, 0, -1));
        break;
    case 'x': //<--- New code added: gameboard rotation
        xIncr += 15;
        break;
    case 'y':
        yIncr += 15;
        break;
    case 'z':
        zIncr += 15;
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
    case GLUT_KEY_UP:
        camera.cameraUp();
        break;
    case GLUT_KEY_DOWN:
        camera.cameraDown();
        break;
    case GLUT_KEY_LEFT:
        camera.tiltLeft();
        break;
    case GLUT_KEY_RIGHT:
        camera.tiltRight();
        break;
    default:
        break;
    }
    glutPostRedisplay();
};

// Glut Initialization Function
void init()
{
    loadBall();
    glClearColor(0.5, 0.5, 0.5, 0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-2, 2, -2, 2, -2, 2);
    gluPerspective(45, 1, 1, 100);
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
    glutInit(&argc, argv); //starts up GLUT

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Labyrinth"); //creates the window

    glutDisplayFunc(display);         //registers "display" as the display callback function
    glutKeyboardFunc(keyboard);       //registers "keyboard" as the keyboard callback function
    glutSpecialFunc(specialKeyboard); //registers "specialKeyboard" as the special callback function

    //Set up efficient 3D
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    init();

    glutMainLoop(); //starts the event loop

    return (0);
};