#include "colour.h"
#include <math.h>

Colour::Colour()
{
    this->r = 0.3f * ((rand() % 3) + 1);
    this->g = 0.3f * ((rand() % 3) + 1);
    this->b = 0.3f * ((rand() % 3) + 1);
    this->a = 1.0f;
};

Colour::Colour(float inR, float inG, float inB, float inA)
{
    this->r = inR;
    this->g = inG;
    this->b = inB;
    this->a = inA;
}

void Colour::setColour(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

float *Colour::getColour()
{
    float *colour = new float[4];
    colour[0] = this->r;
    colour[1] = this->g;
    colour[2] = this->b;
    colour[3] = this->a;
    return colour;
};

bool Colour::isColour(Colour other)
{
    return (this->r == other.r) && (this->g == other.g) && (this->b == other.b) && (this->a == other.a);
}