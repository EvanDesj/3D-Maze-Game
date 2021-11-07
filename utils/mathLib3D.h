#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H

class Point3D {
public:

    float mX;
    float mY;
    float mZ;

    Point3D(float inX, float inY, float inZ);
    float distanceTo(Point3D other);
    float fastDistanceTo(Point3D other);
};

class Vec3D {
public:
    float mX;
    float mY;
    float mZ;
    Vec3D(float inX, float inY, float inZ);
    float length();
    Vec3D normalize();
    Vec3D multiply(float scalar);
    Point3D movePoint(Point3D source);
    void reverse();
    static Vec3D createVector(Point3D p1, Point3D p2);
};

#endif
