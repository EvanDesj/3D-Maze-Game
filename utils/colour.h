#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
public:
    float r;
    float g;
    float b;
    float a;

    Colour();
    Colour(float r, float g, float b, float a);
    void setColour(float r, float g, float b, float a);
    float *getColour();
    bool isColour(Colour other);
};

#endif