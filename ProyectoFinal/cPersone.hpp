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
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include "cPlayere.hpp"

class Persone{
public:
    //variables
    float* position;
    float radius;
    float t;
    int linea;
    float velocidad;
    float dir;
    float maxBrazo;
    float minBrazo;
    float* bIzq;
    float* bDer;
    int dirD;
    int dirI;

    //material
    GLfloat* ka;
    GLfloat* kd;
    GLfloat* ks;
    GLfloat* alpha;
    
    Persone(float linea, float v);
    ~Persone();
    void Draw();
    void Update();
    void OnCollision(Persone* other);
    void Chokiamos(Persone* other);
    void onCollision2(Playere* P1);
    void ChokiamosChief(Playere* P1);
    void Avanzar();
    void Animar();
};
