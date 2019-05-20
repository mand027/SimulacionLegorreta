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
    //plano = glmReadOBJ("assets/plane.obj");
    plano = glmReadOBJ("assets/Legorreta.obj");
    glmUnitize(plano);
    glmScale(plano, 15.0);
    
    ka = new GLfloat[4];
    ka[0] = 1; //red
    ka[1] = 1; //green
    ka[2] = 1; //blue
    ka[3] = 1.0f; //alpha
    
    kd = new GLfloat[4];
    kd[0] = 1;
    kd[1] = 1;
    kd[2] = 1;
    kd[3] = 1.0f; //always 1
    
    ks = new GLfloat[4];
    ks[0] = 1;
    ks[1] = 1;
    ks[2] = 1;
    ks[3] = 1.0f;
    
    alpha = new GLfloat[1];
    alpha[0] = 50.0f;
}

Plano::~Plano() {
}

void Plano::draw() {
    
    
    glPushMatrix();
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha);
        glmDraw(plano, GLM_SMOOTH | GLM_TEXTURE );
    }
    glPopMatrix();

}

void Plano::update() {
    
}
