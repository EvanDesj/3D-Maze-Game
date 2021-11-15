
# 3GC3 Final Project (Fall 2021)

Authors:
> Anant Jain, jaina17@mcmaster.ca  
> Rahil Shah, shahr39@mcmaster.ca  
> Evan Desjardine, desjarde@mcmaster.ca  
> Lin Rozenszajn, rozensl@mcmaster.ca

---
This project repository contains a program that renders a 3D labyrinth that can be tilted on a fixed axis. There is a ball on the board, which needs to be navigated throughout the maze in order to complete the challenge.  

---

Table of Contents:
  - [Instructions to run](#instructions-to-run)
  - [Development Environment](#development-environment)
  - [What's Included](#whats-included)
    - [Base Board with Tilt](#base-board-with-tilt)
    - [.OBJ Loader](#obj-loader)
    - [Mesh Renderer](#mesh-renderer)
    - [Camera controls](#camera-controls)
    - [Ball](#ball)
    - [Walls/Maze](#wallsmaze)
    - [Collision Detection](#collision-detection)
  - [Identified Bugs](#identified-bugs)
  - [What's Next](#whats-next)
  - [Citations](#citations)
---
## Instructions to run
Download all the files in this directory.
```
sudo apt-get update
```
```
sudo apt-get install freeglut3 freeglut3-dev gcc g++ make
```
```
make clean && make
```
---
## Development Environment
- Ubuntu 21.04 64-bit running on Virtualbox, Microsoft Windows 10
- IDE : Visual Studio with C/C++ Extension
---

## What's Included
### Base Board with Tilt
`> Located in [Board Class](board.h)`

The board is drawn in [main.cpp](main.cpp) based on **baseSize** defined at the beginning of the program.

The board is redrawn on every animation cycle, with it's rotation/incline managed by **xIncr**, **yIncr** & **zIncr**.

The board can be tilted by using the **W**, **A**, **S**, **D** keys.

### .OBJ Loader
A .obj object loader has been implemented with the help of the [OBJ-Loader](https://github.com/Bly7/OBJ-Loader) library.

This library was chosen because:
- It is a single header file that can be reused in multiple locations throughout the project without additional imports.
- It is compatible with our requirements as it uses standard methods and data structures, without introducing additional dependencies (such as GLEW which other .obj loaders might include)
- It is available to use under the **MIT License** which allows us to use and modify this software as long as due credit is provided to the creators.
-  Support for **.mtl** files which can introduce material properties (lighting, colors, etc) while importing the object.
- It is extremely easy to use, with all the raw data available as needed, and this data is used by the **Mesh Renderer** to render the object. 

### Mesh Renderer
> Located in [main.cpp as drawFromObj()](main.cpp)

This rendered uses data obtained from the .obj loader, and uses it to render the object on the display.
For each mesh, multiple triangles are drawn, each with their own texture coordinates, normal and material properties.

The implementation of this renderer has been inspired from: 
 - [.obj loader's examples](https://github.com/Bly7/OBJ-Loader/blob/master/examples/1%20-%20LoadAndPrint/e1_loadandprint.cpp) for instruction about obtaining the data.
 - [# Lecture 6-objects and meshes](https://avenue.cllmcmaster.ca/d2l/le/content/414625/viewContent/3401120/View) for guidance on rendering
 
 ### Camera controls
 > Located in [Camera class](camera.h)

A camera system has been implemented that revolves around the board with variable zoom.

The position is calculated by using the following formula:
 - x = radius \* sin(angle)
 - z = radius \* cos(angle)

Using this, we can place the camera at a distance of **radius** from the origin at angle **angle** and get the x and z co-ordinates.

Movement :
- The **angle/position** can be changed using **left** and **right** arrow keys.
- The **radius/zoom** can be changed using **U** and **J** keys.
- Camera's height can be changed using **up** and **down** arrow keys.
- Camera's rotation is fixed as {0,1,0} (upright on y axis).
- Camera is always focus on/looking at the origin {0,0,0}.

### Ball
> Located in [Ball class](shapes/ball.h)

This is the ball that is placed on the board, and it moves and rotates as the board is tilted. This class contains information about the position, rotation and speed of the ball, while the material, color and other visual properties are loaded in via the .obj loader.

### Walls/Maze
> Located in [main.cpp](main.cpp)

- The walls are represented as a 2D Matrix. 
- The size of the walls needs to be the same as the size of the base board (**baseSize**), otherwise it might exceed the boundaries of the board.
- This wall is re-rendered on every animation cycle, on top of the base matrix which contains the board. This has been implemented this way because the walls also need to rotate as the base board rotates, otherwise clipping will occur.
- The wall/maze is rendered via the **renderWalls()** method. For each **1** present in the **Wall** matrix, a solid cube of size 1 is rendered at it's location.

### Collision Detection
> Located in [main.cpp](main.cpp)

A basic collision detection algorithm has been implemented. This algorithm is run on every animation cycle.
The way this works is:
- On every animation cycle, we detect where the ball will be next, based on the current tilt of the board.
- If the ball (or it's boundaries) appears to be in the same position as where a wall exists, we stop the ball from moving into that location).
- We do this again, but with tilt on only one axis, to determine if the movement towards another axis allows the ball to move without collision
- If collision is not detected on both axis, we allow the ball to move freely towards the direction of the tilt.
- If collision is only detected on one axis, we allow the ball to move towards the other axis.
- If collision is detected on both axis, we do not allow the ball to move.

Since we are only computing the expected position of the ball and then checking if a wall exists at that location, this is a constant time operation and it's time complexity is O(1).  

## Identified Bugs
- The ball clips through the walls if the tilt is too much, eventually breaking the game and requiring a restart.

## What's Next
- Lighting 
- Winning Conditions
- Advanced Ball Physics (Inertia and Momentum)
- Code cleanup and restructure

## Citations
 - **.OBJ Loader** : https://github.com/Bly7/OBJ-Loader 
	- Used as is without modifications
- **Ball Model** : https://free3d.com/3d-model/football-ball--64059.html 
	- Used with modification to .obj file
	- .mtl file added manually 
- **Lecture Slides** : https://avenue.cllmcmaster.ca/d2l/le/content/414625/viewContent/3401120/View
