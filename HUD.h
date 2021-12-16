#ifndef HUD_H
#define HUD_H

//include required libraries
#include "utils/PPM.h"
#include <string>

class HUD
{
public:

	int mWidth;
    int mHeight;
    GLubyte * mImage;

    HUD();

	void draw(int xRasterPosition, int yRasterPosition);
	void setOrthographicProjection(int* viewportWidth, int* viewportHeight);
	void changeLevel(int selectedLevel);
};

#endif