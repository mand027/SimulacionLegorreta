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
#include "cPlayere.hpp"

class Playere{
public:
    //variables
    float* position;
    float radius;
    float velocidad;
    
    //material
    GLfloat* ka;
    GLfloat* kd;
    GLfloat* ks;
    GLfloat* alpha;
    
    Playere(float* p, float m, float r);
    ~Playere();
    void Draw();
    void Update();
    //    float* substractVectors(float* v1, float* v2);
    void Moverse();
};
