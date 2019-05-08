//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//  cPlano.hpp
//  OBJ
//
//  Created by Luis Eduardo Brime Gomez on 4/1/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#include "glm.hpp"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma once

class Plano {
public:
    GLMmodel* plano;
    
    Plano();
    ~Plano();
    void draw();
    void update();
};
