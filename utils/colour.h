#ifndef COLOUR_H
#define COLOUR_H

class Colour {
public:

    float mR;
    float mG;
    float mB;
    float mA;

    Colour();
    Colour(float r, float g, float b, float a);
    void setColour(float r, float g, float b, float a);
    bool isColour(Colour other);
};

#endif