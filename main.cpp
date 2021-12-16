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

// include standard libraries
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "camera.h"
#include "board.h"
#include "utils/PPM.h"
#include "HUD.h"
#include "utils/objectLoader.h"
#include "shapes/ball.h"
#include "utils/levelManager.h"
#include "utils/fileManager.h"
#include "utils/mazeGen.h"
#include <string.h>
#include <chrono>
using namespace std;

// Define GLUT Constants
#define WINDOW_TITLE "3GC3 Final Project - Labyrinth"

// Configuration Variables (Modify before build)
int timerFunc = 10; // Duration between animation frames, lower is better
int windowWidth = 800;
int windowHeight = 800;
bool debugMode = false;

// Print Program Instructions
void printInstructions()
{
    using namespace std;
    cout << "Program Instructions:" << endl;
    cout << "Use q/Q to close the program at any time." << endl;
    cout << "Use U and J to zoom in and out with the camera." << endl;
    cout << "Use the left and right arrow keys to move the camera around the board." << endl;
    cout << "Use the up and down arrow keys to move the camera above and below the board." << endl;
    cout << "Use C to reset the camera to its initial view." << endl;
    cout << "Use W,A,S,D to tilt the gameboard. This allows the ball to roll in the direction the board is tilted if there are no walls obstructing it." << endl;
    cout << "Use R to reset the game." << endl;
    cout << "Use I to print this instructions menu." << endl;
    cout << "Use 0 to toggle debug menu." << endl;
    cout << "Use 1-3 to select predefined levels." << endl;
    cout << "Use 4 to select randomly generated level." << endl;
    cout << "Use 5 to load game from board.txt" << endl;
    cout << "Use E to export current game to board.txt" << endl;
}

// Do not modify
// Global variables for gameboard rotation increments
float xIncr = 0;
float yIncr = 0;
float zIncr = 0;
objl::Loader BallObject;        // Ball object where ball.obj will be loaded in
bool ballTextureLoaded = false; // Boolean to check if the ball object has been loaded or not
bool completionStatus = false;
std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
bool timerStarted = false;
bool consoleWarning = false;
float timeElapsed = 0;
Ball football = Ball(Point3D(0, 1, 0), 0.5, 0); // Initialize ball with base position (origin)
CameraSystem camera = CameraSystem();           // Initialize camera system
FileManager fileManager = FileManager();
Maze_Path mazeGen = Maze_Path();
unordered_map<int, float> highScores = fileManager.getHighScores();
int selectedLevel = 1;

//Texture variables
int gridWidth, gridHeight;
int floorWidth, floorHeight;
GLuint textures[2];

//Lighting variables
float light_pos0[] = {-7, 3, -1};
float light_pos1[] = {7, 10, -2};
float amb[] = {0.20, 0.22, 0.25};
float diff[] = {0.75, 0.62, 0.55};
float spec[] = {0.55, 0.45, 0.55};

float amb2[] = {0.20, 0.18, 0.15};
float diff2[] = {0.37, 0.37, 0.20};
float spec2[] = {0.26, 0.17, 0.20};

// HUD variables
HUD HUDinterface = HUD();

// Begin walls at level1
vector<vector<int>> Wall = level1;

int baseSize()
{
    return Wall.size();
}

// Initialize game board
Board gameBoard = Board(Vec3D(0, 0, 0), baseSize(), Wall);

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
    if (!(xIncr == 0 && zIncr == 0))
    {
        glRotatef(football.rotationAngle, xIncr, yIncr, zIncr);
    }
    glScalef(football.size, football.size, football.size);
    drawFromObj(BallObject);
}

void startTimer()
{
    if (timerStarted == false)
    {
        beginTime = std::chrono::steady_clock::now();
        timerStarted = true;
    }
    consoleWarning = false;
}

void renderText(int x, int y, string stringInput)
{
    glColor3f(1, 1, 1);
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

string boolToText(bool val)
{
    if (val)
    {
        return "T";
    }
    return "F";
}

bool withinBoardLimits(int val)
{
    if (val < baseSize() && val >= 0)
    {
        return true;
    }
    return false;
}

bool allowedUp()
{
    int posX = ceil(football.position.x + baseSize() / 2);
    int posZL = ceil(football.position.z + baseSize() / 2);
    int posZR = floor(football.position.z + baseSize() / 2);
    if (withinBoardLimits(posZL) && withinBoardLimits(posZR) && withinBoardLimits(posX - 1) && Wall[posZL][posX - 1] && Wall[posZR][posX - 1])
    {
        return false;
    }
    return true;
}

bool allowedDown()
{
    int posX = floor(football.position.x + baseSize() / 2);
    int posZL = ceil(football.position.z + baseSize() / 2);
    int posZR = floor(football.position.z + baseSize() / 2);
    if (withinBoardLimits(posZL) && withinBoardLimits(posZR) && withinBoardLimits(posX + 1) && Wall[posZL][posX + 1] && Wall[posZR][posX + 1])
    {
        return false;
    }
    return true;
}

bool allowedLeft()
{
    int posXU = ceil(football.position.x + baseSize() / 2);
    int posXD = floor(football.position.x + baseSize() / 2);
    int posZ = ceil(football.position.z + baseSize() / 2);
    if (withinBoardLimits(posXU) && withinBoardLimits(posXD) && withinBoardLimits(posZ - 1) && Wall[posZ - 1][posXU] && Wall[posZ - 1][posXD])
    {
        return false;
    }
    return true;
}

bool allowedRight()
{
    int posXU = ceil(football.position.x + baseSize() / 2);
    int posXD = floor(football.position.x + baseSize() / 2);
    int posZ = floor(football.position.z + baseSize() / 2);
    if (withinBoardLimits(posXU) && withinBoardLimits(posXD) && withinBoardLimits(posZ + 1) && Wall[posZ + 1][posXU] && Wall[posZ + 1][posXD])
    {
        return false;
    }
    return true;
}

// Function to update ball's position
void updateBallPosition()
{
    if ((xIncr < 0 && allowedUp()) || (xIncr > 0 && allowedDown()))
    {
        football.update(football.nextPosition(xIncr, 0, 0)); // Move ball up or down
    }
    if ((zIncr < 0 && allowedRight()) || (zIncr > 0 && allowedLeft()))
    {
        football.update(football.nextPosition(0, 0, zIncr)); // Move ball left or right
    }
}

void screenText()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    float widthOffset = windowWidth - 130;
    if (debugMode)
    {
        renderText(10, windowHeight - 150, "Debug Mode:");
        renderText(10, windowHeight - 175, "Allowed | Left: " + boolToText(allowedLeft()) + " , Right: " + boolToText(allowedRight()) + " , Up: " + boolToText(allowedUp()) + " , Down: " + boolToText(allowedDown()));
        renderText(10, windowHeight - 200, "Ball Position | X: " + to_string(football.position.x) + " , Y: " + to_string(football.position.y) + " , Z: " + to_string(football.position.z));
        renderText(10, windowHeight - 225, "Tilt | X: " + to_string(xIncr) + " , Y: " + to_string(yIncr) + " , Z: " + to_string(zIncr));
        renderText(10, windowHeight - 250, "Camera | X: " + to_string(camera.getX()) + " , Y: " + to_string(camera.getY()) + " , Z: " + to_string(camera.getZ()));
    }
    if (highScores[selectedLevel] != 0)
    {
        float targetScore = highScores[selectedLevel];
        renderText(widthOffset, 125, to_string(targetScore).substr(0, 4));
    }
    else
    {
        renderText(widthOffset, 125, "No Record");
    }
    if (timeElapsed > 0)
    {
        char timeElapsedArray[10];
        sprintf(timeElapsedArray, "%.2f", timeElapsed);
        renderText(widthOffset, 40, (string)timeElapsedArray);
        if (completionStatus)
        {
            if (highScoreBeat())
            {
                renderText(10, windowHeight - 25, "You won!");
                renderText(10, windowHeight - 50, "Press r to reset, or change levels with 1-5 keys!");
            }
            else
            {
                renderText(10, windowHeight - 25, "Try again!");
                renderText(10, windowHeight - 50, "Press r to try again, or change levels with 1-5 keys!");
            }
        }
    }
    else
    {
        renderText(widthOffset, 40, "Not Started");
    }
    if (consoleWarning)
    {
        renderText(10, windowHeight - 75, "An unexpected error occurred. Please Look at console for more info.");
    }
}

// Display Callback Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(), 0, -5, 0, camera.rotX, camera.rotY, camera.rotZ);

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
    gameBoard.draw(textures);

    //Add Ball
    glPushMatrix();
    glDisable(GL_LIGHTING);
    renderBall();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    screenText();
    HUDinterface.draw(0, 20);

    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Swap Buffers
    glutSwapBuffers();
};

bool outOfBounds()
{
    // Point3D expectedPoint = football.nextPosition(xIncr, yIncr, zIncr, Wall); // Check where ball will be next due to current board's tilt
    float posX = football.position.x + baseSize() / 2;
    float posZ = football.position.z + baseSize() / 2;
    if ((posX > baseSize() || posX < 0) || (posZ > baseSize() || posZ < 0))
    {
        return true;
    }
    return false;
}

void autoTilt()
{
    if (xIncr > 0)
    {
        xIncr = xIncr - 0.1;
    }
    if (xIncr < 0)
    {
        xIncr = xIncr + 0.1;
    }
    if (zIncr > 0)
    {
        zIncr = zIncr - 0.1;
    }
    if (zIncr < 0)
    {
        zIncr = zIncr + 0.1;
    }
    if (xIncr >= -0.1 && xIncr <= 0.1)
    {
        xIncr = 0;
    }
    if (zIncr >= -0.1 && zIncr <= 0.1)
    {
        zIncr = 0;
    }
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
    autoTilt();
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

void gameReset()
{
    HUDinterface.changeLevel(selectedLevel);
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
    gameBoard = Board(Vec3D(0, 0, 0), baseSize(), Wall); // Reinitialize game board
    highScores = fileManager.getHighScores();
    consoleWarning = false;
    fileManager.reset();
}

// Keyboard Callback Function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        Wall = level1;
        selectedLevel = 1;
        gameReset();
        break;
    case '2':
        Wall = level2;
        selectedLevel = 2;
        gameReset();
        break;
    case '3':
        Wall = level3;
        selectedLevel = 3;
        gameReset();
        break;
    case '4':
        // prettyPrintLevel(getMaze(11));
        Wall = mazeGen.getMaze(25);
        selectedLevel = 4;
        gameReset();
        break;
    case '5':
        if (fileManager.loadLevel())
        {
            selectedLevel = 5;
            Wall = fileManager.loadedLevel;
            gameReset();
            cout << "Board loaded from external file" << endl;
        }
        else
        {
            consoleWarning = true;
            cout << "Please place a file in root directory titled board.txt. Refer to readme for more information." << endl;
        }
        break;
    case 'e':
    case 'E':
        if (fileManager.exportLevel(Wall))
        {
            cout << "Board saved as board.txt" << endl;
        }
        else
        {
            consoleWarning = true;
            cout << "Board could not be saved. Please try again later" << endl;
        }
        break;
    case 'i':
    case 'I':
        printInstructions();
        break;
    case '0':
        debugMode = !debugMode;
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
        gameReset();
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
    glClearColor(0.0, 0.0, 0.0, 0);
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
    setTexture(0, "assets/floor.ppm", floorWidth, floorHeight);
    setTexture(1, "assets/brickTexture.ppm", gridWidth, gridHeight);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
};

// Main program
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(WINDOW_TITLE); //creates the window
    printInstructions();
    glutDisplayFunc(display);         //registers "display" as the display callback function
    glutKeyboardFunc(keyboard);       //registers "keyboard" as the keyboard callback function
    glutSpecialFunc(specialKeyboard); //registers "specialKeyboard" as the special callback function
    init();
    animate(1);
    glutMainLoop();
    return (0);
};
