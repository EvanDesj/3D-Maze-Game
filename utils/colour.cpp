#include "colour.h"
#include <math.h>

Colour::Colour(){
    this->mR = 0.3f * ((rand() % 3) + 1);
    this->mG = 0.3f * ((rand() % 3) + 1);
    this->mB = 0.3f * ((rand() % 3) + 1);
    this->mA = 1.0f;
};

Colour::Colour(float inR, float inG, float inB, float inA) {
    this->mR = inR;
    this->mG = inG;
    this->mB = inB;
    this->mA = inA;
}

void Colour::setColour(float r, float g, float b, float a) {
    this->mR = r;
    this->mG = g;
    this->mB = b;
    this->mA = a;
}
    
bool Colour::isColour(Colour other){
    return (this->mR == other.mR) && (this->mG == other.mG) && (this->mB == other.mB) && (this->mA == other.mA);
}