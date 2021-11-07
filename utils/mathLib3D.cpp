#include <math.h>
#include "mathLib3D.h"

Point3D::Point3D(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
};

Point3D::Point3D(float inX, float inY, float inZ) {
    this->x = inX;
    this->y = inY;
    this->z = inZ;
}

float Point3D::distanceTo(Point3D other) {
    return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2) + pow(other.z - this->z, 2));
}

float Point3D::fastDistanceTo(Point3D other) {
    return (pow(other.x - this->x, 2) + pow(other.y - this->y, 2) + pow(other.z - this->z, 2));
}

Vec3D::Vec3D(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
};

Vec3D::Vec3D(float inX, float inY, float inZ) {
    this->x = inX;
    this->y = inY;
    this->z = inZ;
}

float Vec3D::length() {
    return abs(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Vec3D Vec3D::normalize() {
    float x = this->x / this->length();
    float y = this->y / this->length();
    float z = this->z / this->length();
    return Vec3D(x, y, z);
}

Vec3D Vec3D::add(Vec3D other) {
    float x = this->x + other.x;
    float y = this->y + other.y;
    float z = this->z + other.z;
    return Vec3D(x, y, z);
}

Vec3D Vec3D::multiply(float scalar) {
    float x = this->x * scalar;
    float y = this->y * scalar;
    float z = this->z * scalar;
    return Vec3D(x, y, z);
}

Point3D Vec3D::movePoint(Point3D source) {
    float x = this->x + source.x;
    float y = this->y + source.y;
    float z = this->z + source.z;
    return Point3D(x, y, z);
}

void Vec3D::reverse() {
    this->x = -x;
    this->y = -y;
    this->z = -z;
}

Vec3D Vec3D::createVector(Point3D p1, Point3D p2) {
    float x = p2.x - p1.x;
    float y = p2.y - p1.y;
    float z = p2.z - p1.z;
    return Vec3D(x, y, z);
}