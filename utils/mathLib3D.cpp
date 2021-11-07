#include <math.h>
#include "mathLib3D.h"

Point3D::Point3D(float inX, float inY, float inZ) {
    this->mX = inX;
    this->mY = inY;
    this->mZ = inZ;
}

float Point3D::distanceTo(Point3D other) {
    return sqrt(pow(other.mX - this->mX, 2) + pow(other.mY - this->mY, 2) + pow(other.mZ - this->mZ, 2));
}

float Point3D::fastDistanceTo(Point3D other) {
    return (pow(other.mX - this->mX, 2) + pow(other.mY - this->mY, 2) + pow(other.mZ - this->mZ, 2));
}


Vec3D::Vec3D(float inX, float inY, float inZ) {
    this->mX = inX;
    this->mY = inY;
    this->mZ = inZ;
}

float Vec3D::length() {
    return abs(sqrt(pow(this->mX, 2) + pow(this->mY, 2) + pow(this->mZ, 2)));
}

Vec3D Vec3D::normalize() {
    float x = this->mX / this->length();
    float y = this->mY / this->length();
    float z = this->mZ / this->length();
    return Vec3D(x, y, z);
}

Vec3D Vec3D::multiply(float scalar) {
    float x = this->mX * scalar;
    float y = this->mY * scalar;
    float z = this->mZ * scalar;
    return Vec3D(x, y, z);
}

Point3D Vec3D::movePoint(Point3D source) {
    float x = this->mX + source.mX;
    float y = this->mY + source.mY;
    float z = this->mZ + source.mZ;
    return Point3D(x, y, z);
}

void Vec3D::reverse() {
    this->mX = -mX;
    this->mY = -mY;
    this->mZ = -mZ;
}

Vec3D Vec3D::createVector(Point3D p1, Point3D p2) {
    float x = p2.mX - p1.mX;
    float y = p2.mY - p1.mY;
    float z = p2.mZ - p1.mZ;
    return Vec3D(x, y, z);
}