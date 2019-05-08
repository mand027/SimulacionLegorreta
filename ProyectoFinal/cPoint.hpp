//
//  cPoint.hpp
//  BezierPr
//
//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//
#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
#include "freeglut.h"
#endif
#ifdef __unix__
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <math.h>

class Point
{
public:
    Point(float _x, float _y, float _z);
    Point(Point* other);
    ~Point();
    
    void draw();
    void update();
    Point* multiplyByScalar(float s);
    Point* add(Point* other);
    
    float x, y, z;
//    GLfloat* ka;
//    GLfloat* kd;
//    GLfloat* ks;
//    GLfloat* alpha;
};

