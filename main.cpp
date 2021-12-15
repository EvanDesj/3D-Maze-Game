/*
Final Project:
    - Name: Anant Jain, Evan Desjardine, Lin Rozenszajn, Rahil Shah
    - Operating System: Windows 10, Ubuntu 21.04
*/

// Include OpenGL/GLUT Libraries
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
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
#include "HUD.h"
#include "camera.h"
#include "board.h"
#include "utils/PPM.h"
#include "utils/objectLoader.h"
#include "shapes/ball.h"
#include "utils/levelManager.h"
#include "utils/fileManager.h"
#include <string.h>
#include <chrono>
using namespace std;

// Define GLUT Constants
#define WINDOW_TITLE "3GC3 Final Project - Labyrinth"

// Configuration Variables (Modify before build)
// Global variables for gameboard rotation increments
float xIncr = 0;
float yIncr = 0;
float zIncr = 0;
// ------------------------//
int timerFunc = 1; // Duration between animation frames, lower is better
int windowWidth = 800;
int windowHeight = 600;

objl::Loader BallObject;        // Ball object where ball.obj will be loaded in
bool ballTextureLoaded = false; // Boolean to check if the ball object has been loaded or not
bool completionStatus = false;
std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
bool timerStarted = false;
float timeElapsed = 0;
Ball football = Ball(Point3D(0, 1, 0), 0.5, 0); // Initialize ball with base position (origin)
CameraSystem camera = CameraSystem();           // Initialize camera system
FileManager fileManager = FileManager();
unordered_map<string, float> highScores = fileManager.getHighScores();
string selectedLevel = "1";

//Texture variables
int gridWidth, gridHeight;
int floorWidth, floorHeight;
GLuint textures[1];

//Lighting variables
float light_pos0[] = {-7, 3, -1};
float light_pos1[] = {7, 10, -2};
float amb[] = {0.20, 0.22, 0.25};
float diff[] = {0.75, 0.62, 0.55};
float spec[] = {0.55, 0.45, 0.55};

float amb2[] = {0.20, 0.18, 0.15};
float diff2[] = {0.37, 0.37, 0.20};
float spec2[] = {0.26, 0.17, 0.20};
//Material variables
Material wallMat = Material('w');
Material ballMat = Material('w');
Material floorMat = Material(Colour(0.12f, 0.18f, 0.25f, 1.0f),
                             Colour(0.67f, 0.65f, 0.5f, 1.0f),
                             Colour(0.70f, 0.70f, 0.55f, 1.0f),
                             0.0f);

// HUD variables
HUD HUDinterface(stoi(selectedLevel)); 

vector<vector<int>> Wall = level1;
int baseSize()
{
    return Wall.size();
}

Board gameBoard = Board(Vec3D(0, 0, 0), baseSize()); // Initialize game board

// Function to load ball
void loadBall()
{
    ballTextureLoaded = BallObject.LoadFile("shapes/ball.obj");
}

// Function to render loaded object
void drawFromObj(objl::Loader Object)
{
    if (ballTextureLoaded) // Only render if the object has been loaded
    {
        for (int i = 0; i < Object.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = Object.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Indices.size(); j += 3)
            {
                glBegin(GL_TRIANGLES); // Draw triangle for each mesh indice

                glColor3f(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z);
                int indice1 = curMesh.Indices[j];
                int indice2 = curMesh.Indices[j + 1];
                int indice3 = curMesh.Indices[j + 2];

                glTexCoord2f(curMesh.Vertices[indice1].TextureCoordinate.X, curMesh.Vertices[indice1].TextureCoordinate.Y);
                glNormal3f(curMesh.Vertices[indice1].Normal.X, curMesh.Vertices[indice1].Normal.Y, curMesh.Vertices[indice1].Normal.Z);
                glVertex3f(curMesh.Vertices[indice1].Position.X, curMesh.Vertices[indice1].Position.Y, curMesh.Vertices[indice1].Position.Z);

                glTexCoord2f(curMesh.Vertices[indice2].TextureCoordinate.X, curMesh.Vertices[indice2].TextureCoordinate.Y);
                glNormal3f(curMesh.Vertices[indice2].Normal.X, curMesh.Vertices[indice2].Normal.Y, curMesh.Vertices[indice2].Normal.Z);
                glVertex3f(curMesh.Vertices[indice2].Position.X, curMesh.Vertices[indice2].Position.Y, curMesh.Vertices[indice2].Position.Z);

                glTexCoord2f(curMesh.Vertices[indice3].TextureCoordinate.X, curMesh.Vertices[indice3].TextureCoordinate.Y);
                glNormal3f(curMesh.Vertices[indice3].Normal.X, curMesh.Vertices[indice3].Normal.Y, curMesh.Vertices[indice3].Normal.Z);
                glVertex3f(curMesh.Vertices[indice3].Position.X, curMesh.Vertices[indice3].Position.Y, curMesh.Vertices[indice3].Position.Z);

                glEnd();
            }
        }
    }
    return;
}

// Function to render ball
void renderBall()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslatef(football.position.z, football.position.y, football.position.x);
    glRotatef(football.rotationAngle, xIncr, yIncr, zIncr);
    glScalef(football.size, football.size, football.size);
    drawFromObj(BallObject);
}

void drawBox(GLfloat size)
{
    static GLfloat n[6][3] =
        {
            {-1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, -1.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, -1.0}};
    static GLint faces[6][4] =
        {
            {0, 1, 2, 3},
            {3, 2, 6, 7},
            {7, 6, 5, 4},
            {4, 5, 1, 0},
            {5, 6, 2, 1},
            {7, 4, 0, 3}};
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--)
    {
        glBegin(GL_POLYGON);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(1, 1);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(1, 0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0, 0);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0, 1);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

// Function to render walls/maze
void renderWalls()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wallMat.ambient.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wallMat.diffuse.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wallMat.specular.getColour());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    for (int i = 0; i < baseSize(); i++)
    {
        for (int j = 0; j < baseSize(); j++)
        {
            if (Wall[i][j] == 1)
            {
                glPushMatrix();
                glTranslatef(i, 1, j); // Draw wall at position (i,j) at fixed y position
                drawBox(1);            // Draw cube of size 1
                glPopMatrix();
            }
        }
    }
}
void renderFloor()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorMat.ambient.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorMat.diffuse.getColour());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floorMat.specular.getColour());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    gameBoard.draw();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
}

void startTimer()
{
    if (timerStarted == false)
    {
        beginTime = std::chrono::steady_clock::now();
        timerStarted = true;
    }
}

void renderText(int x, int y, string stringInput)
{
    glRasterPos2f(x, y);
    int len, i;
    len = (int)stringInput.length();
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stringInput[i]);
    }
}

//sets lighting parameters
void setLighting()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec2);
}

bool highScoreBeat()
{
    if (highScores[selectedLevel] == 0)
    {
        return true;
    }
    if (completionStatus && timeElapsed > 0 && timeElapsed < highScores[selectedLevel])
    {
        return true;
    }
    return false;
}

void screenText()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    float baseHeight = (float)windowHeight / 4;
    float widthOffset = 10;
    renderText(widthOffset, baseHeight, "Welcome");
    renderText(widthOffset, baseHeight - 20, "Use W,A,S,D to control board");
    renderText(widthOffset, baseHeight - 40, "Use arrow keys to control camera");
    if (highScores[selectedLevel] != 0)
    {
        float targetScore = highScores[selectedLevel];
        renderText(widthOffset, baseHeight - 60, "Level: " + selectedLevel + " | Time to beat: " + to_string(targetScore).substr(0, 4));
    }
    else
    {
        renderText(widthOffset, baseHeight - 60, "Level: " + selectedLevel);
    }
    if (timeElapsed > 0)
    {
        char timeElapsedArray[10];
        sprintf(timeElapsedArray, "%.2f", timeElapsed);
        if (!completionStatus)
        {
            renderText(widthOffset, baseHeight - 80, "Time elapsed: " + (string)timeElapsedArray + " seconds");
        }
        else
        {
            if (highScoreBeat())
            {
                renderText(widthOffset, baseHeight - 80, "You Won. You took: " + (string)timeElapsedArray + " seconds");
            }
            else
            {
                renderText(widthOffset, baseHeight - 80, "You didn't win. You took: " + (string)timeElapsedArray + " seconds");
            }
        }
    }
}

// Display Callback Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render HUD
    int y = 170;
    int* h = &y;
    HUDinterface.setOrthographicProjection(&windowWidth, &windowHeight);
    HUDinterface.draw(10, 425);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0, 0, 0, camera.rotX, camera.rotY, camera.rotZ);

    glEnable(GL_LIGHTING);
    glColor3f(1, 1, 1);

    // Matrix so ball and walls also move as board rotates
    glPushMatrix();
    // Activate lighting
    setLighting();

    // Add Gameboard
    glRotatef(0 + xIncr, 1, 0, 0);
    glRotatef(0 + yIncr, 0, 1, 0);
    glRotatef(0 + zIncr, 0, 0, 1);
    renderFloor();

    //Add Ball
    glPushMatrix();
    glDisable(GL_LIGHTING);
    renderBall();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Add Walls
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(-1 * (baseSize() / 2), 0, -1 * (baseSize() / 2)); // To offset maze to correct position to overlay maze over base board and fix alignment
    glPushMatrix();
    renderWalls();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    screenText();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Swap Buffers
    glutSwapBuffers();
};

// Function to detect collision
bool collisionDetected(float x, float z)
{
    int posX, posZ = 0;
    if (xIncr < 0)
    {
        posX = round(x - football.size + baseSize() / 2);
    }
    else
    {
        posX = round(x + football.size + baseSize() / 2);
    }
    if (zIncr < 0)
    {
        posZ = round(z + football.size + baseSize() / 2);
    }
    else
    {
        posZ = round(z - football.size + baseSize() / 2);
    }
    if (posX < baseSize() && posZ < baseSize() && Wall[posZ][posX]) // Check if a maze exists at ball's location
    {
        return true;
    }
    return false;
}

// Function to update ball's position
void updateBallPosition()
{
    Point3D expectedPoint = football.nextPosition(xIncr, yIncr, zIncr); // Check where ball will be next due to current board's tilt
    if (!collisionDetected(expectedPoint.x, expectedPoint.z))
    {
        football.update(expectedPoint); // If no collision is detected, move ball to expected position
        return;
    }
    // If collision is only detected on one axis, move ball along other axis if tilt is present.
    expectedPoint = football.nextPosition(xIncr, 0, 0);
    if (!collisionDetected(expectedPoint.x, expectedPoint.z))
    {
        football.update(expectedPoint);
        return;
    }
    expectedPoint = football.nextPosition(0, 0, zIncr);
    if (!collisionDetected(expectedPoint.x, expectedPoint.z))
    {
        football.update(expectedPoint);
        return;
    }
}

bool outOfBounds()
{
    Point3D expectedPoint = football.nextPosition(xIncr, yIncr, zIncr); // Check where ball will be next due to current board's tilt
    float posX = expectedPoint.x + baseSize() / 2;
    float posZ = expectedPoint.z + baseSize() / 2;
    if ((posX > baseSize() || posX < 0) || (posZ > baseSize() || posZ < 0))
    {
        return true;
    }
    return false;
}

// Animate Callback FunctionO
void animate(int v)
{
    if (timerStarted && !completionStatus)
    {
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        timeElapsed = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count()) / 1000000.0;
    }
    if (!outOfBounds())
    {
        updateBallPosition();
    }
    else
    {
        completionStatus = true;
        if (highScoreBeat())
        {
            fileManager.saveHighScore(selectedLevel, timeElapsed);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(timerFunc, animate, 0);
};

// Reshape Callback Function
void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
};

Vec3D computeTiltDirection()
{
    Point3D cameraPos = Point3D(camera.getX(), camera.getY(), camera.getZ());
    Point3D center = Point3D(0, 0, 0);
    Vec3D ray = Vec3D::createVector(cameraPos, center);
    ray = ray.normalize();
    return ray;
}

void boardReset()
{
    xIncr = 0;
    yIncr = 0;
    zIncr = 0;
    football.position.z = 0;
    football.position.y = 1;
    football.position.x = 0;
    completionStatus = false;
    beginTime = std::chrono::steady_clock::now();
    timerStarted = false;
    timeElapsed = 0;
    gameBoard = Board(Vec3D(0, 0, 0), baseSize()); // Reinitialize game board
    highScores = fileManager.getHighScores();
    fileManager.reset();
}

// Keyboard Callback Function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        Wall = level1;
        selectedLevel = "1";
        boardReset();
        break;
    case '2':
        Wall = level2;
        selectedLevel = "2";
        boardReset();
        break;
    case '3':
        Wall = level3;
        selectedLevel = "3";
        boardReset();
        break;
    case '5':
        selectedLevel = "Custom";
        if (fileManager.loadLevel())
        {
            Wall = fileManager.loadedLevel;
            boardReset();
            cout << "Board loaded from external file" << endl;
        }
        else
        {
            cout << "Please place a file in root directory titled board.txt. Refer to readme for more information." << endl;
        }
        break;
    case 27:
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'u':
    case 'U':
        camera.zoomIn();
        break;
    case 'j':
    case 'J':
        camera.zoomOut();
        break;
    case 'c':
    case 'C':
        camera.reset();
        break;
    case 'r':
    case 'R':
        camera.reset();
        boardReset();
        break;
    // Update gameboard rotation
    case 'w':
    case 'W':
        zIncr -= computeTiltDirection().x;
        xIncr += computeTiltDirection().z;
        if (zIncr < -10)
        {
            zIncr = -10;
        }
        if (zIncr > 10)
        {
            zIncr = 10;
        }
        if (xIncr < -10)
        {
            xIncr = -10;
        }
        if (xIncr > 10)
        {
            xIncr = 10;
        }
        startTimer();
        break;
    case 's':
    case 'S':
        zIncr += computeTiltDirection().x;
        xIncr -= computeTiltDirection().z;
        if (zIncr < -10)
        {
            zIncr = -10;
        }
        if (zIncr > 10)
        {
            zIncr = 10;
        }
        if (xIncr < -10)
        {
            xIncr = -10;
        }
        if (xIncr > 10)
        {
            xIncr = 10;
        }
        startTimer();
        break;
    case 'a':
    case 'A':
        zIncr -= computeTiltDirection().z;
        xIncr -= computeTiltDirection().x;
        if (zIncr < -10)
        {
            zIncr = -10;
        }
        if (zIncr > 10)
        {
            zIncr = 10;
        }
        if (xIncr < -10)
        {
            xIncr = -10;
        }
        if (xIncr > 10)
        {
            xIncr = 10;
        }
        startTimer();
        break;
    case 'd':
    case 'D':
        zIncr += computeTiltDirection().z;
        xIncr += computeTiltDirection().x;
        if (zIncr < -10)
        {
            zIncr = -10;
        }
        if (zIncr > 10)
        {
            zIncr = 10;
        }
        if (xIncr < -10)
        {
            xIncr = -10;
        }
        if (xIncr > 10)
        {
            xIncr = 10;
        }
        startTimer();
        break;
    default:
        break;
    }
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
        camera.moveLeft();
        break;
    case GLUT_KEY_RIGHT:
        camera.moveRight();
        break;
    default:
        break;
    }
};

//set texture parameters
void setTexture(int i, const char *name, int width, int height)
{
    GLubyte *img_data = LoadPPM(name, &width, &height);
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, img_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// Glut Initialization Function
void init()
{
    loadBall(); // Load ball only once
    glClearColor(0.05, 0.05, 0.05, 0);
    glColor3f(1, 1, 1);
    // Enable Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glGenTextures(2, textures);
    setTexture(0, "assets/brickTexture_2.ppm", gridWidth, gridHeight);
    setTexture(1, "assets/floor2.ppm", floorWidth, floorHeight);
};

// Print Program Instructions
void printInstructions()
{
    using namespace std;
    cout << "Program Instructions:" << endl;
    cout << "Use q to close the program at any time." << endl;
    cout << "Use u and j to zoom in and out with the camera." << endl;
    cout << "Use the left and right arrow keys to move the camera around the board." << endl;
    cout << "Use the up and down arrow keys to move the camera above and below the board." << endl;
    cout << "Use c to reset the camera to its initial view." << endl;
    cout << "Use w,a,s,d to tilt the gameboard. This allows the ball to roll in the direction the board is tilted if there are no walls obstructing it." << endl;
    cout << "Use r to reset the program." << endl;
}

// Main program
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE); //creates the window
    printInstructions();
    glutDisplayFunc(display);         //registers "display" as the display callback function
    glutKeyboardFunc(keyboard);       //registers "keyboard" as the keyboard callback function
    glutSpecialFunc(specialKeyboard); //registers "specialKeyboard" as the special callback function

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    init();
    animate(1);
    glutMainLoop();
    return (0);
};
