//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//  cPlano.cpp
//  OBJ
//
//  Created by Luis Eduardo Brime Gomez on 4/1/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#include "cPlano.hpp"

Plano::Plano() {
    plano = glmReadOBJ("assets/plane.obj");
}

Plano::~Plano() {
}

void Plano::draw() {
    glmDraw(plano,GLM_SMOOTH | GLM_TEXTURE);
}

void Plano::update() {
    
}
