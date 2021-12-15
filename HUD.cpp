
#include "HUD.h"


HUD::HUD(){
    std::string filename = "assets/brickTexture_1.ppm";
    int len = filename.size();
    char * HUDfilename = new char[len + 1];
    std::copy(filename.begin(), filename.end(), HUDfilename);
    HUDfilename[len] = '\0';
    this->mImage = LoadPPM(HUDfilename, &mWidth, &mHeight);
}

void HUD::draw(int xRasterPosition, int yRasterPosition) {
    glRasterPos2i(xRasterPosition + this->mWidth, yRasterPosition);
    glPixelZoom(-1, 1);
    glDrawPixels(this->mWidth, this->mHeight, GL_RGB, GL_UNSIGNED_BYTE, this->mImage);
}

void HUD::setOrthographicProjection(int* viewportWidth, int* viewportHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (*viewportWidth), 0, (*viewportHeight));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}