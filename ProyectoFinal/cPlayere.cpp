
//
//  cPlayere.cpp
//  ProyectoFinal
//
//  Created by Armando Hernandez on 5/16/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//

#include "cPlayere.hpp"
#include "math.h"



Playere::Playere(){
    position = new float[3];
    position[0] = 0.1;
    position[1] = 0.5f;
    position[2] = 0.1;
    velocidad = 0.026f;
    
    maxBrazo = 0.12f;
    minBrazo = -0.12f;
    dir = 1;
    
    bIzq = new float[3];
    bDer = new float[3];
    
    bIzq[0] = 0.20f;
    bIzq[1] = 0.0f;
    bIzq[2] = 0.0f;
    
    bDer[0] = -0.20f;
    bDer[1] = 0.0f;
    bDer[2] = 0.0f;
    
    dirD = 1;
    dirI = -1;
    
    ka = new GLfloat[4];
    ka[0] = 1; //red
    ka[1] = 0; //green
    ka[2] = 0; //blue
    ka[3] = 1.0f; //alpha
    
    kd = new GLfloat[4];
    kd[0] = 1;
    kd[1] = 0.3f;
    kd[2] = 0.3f;
    kd[3] = 1.0f; //always 1
    
    ks = new GLfloat[4];
    ks[0] = 1;
    ks[1] = 0.3f;
    ks[2] = 0.3f;
    ks[3] = 1.0f;
    
    alpha = new GLfloat[1];
    alpha[0] = 50.0f;
    
}


void Playere::Draw(){
    
    
    glPushMatrix();
    {
        glTranslatef(position[0], position[1], position[2]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alpha);
        glutSolidSphere(0.20f, 10, 10);
        glPushMatrix();
        {
            glTranslatef(bIzq[0], bIzq[1], bIzq[2]);
            glutSolidSphere(0.10f, 10, 10);
            
        }
        glPopMatrix();
        
        glPushMatrix();
        {
            
            glTranslatef(bDer[0], bDer[1], bDer[2]);
            glutSolidSphere(0.10f, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
    
}

void Playere::Moverse(){

    
}

void Playere::Animar(){

    if(bDer[2] < minBrazo || bDer[2] > maxBrazo){
        dirD = -dirD;
    }
    if(bIzq[2] < minBrazo || bIzq[2] > maxBrazo){
        dirI = -dirI;
    }
    
    bIzq[2] += dirI * 0.031;
    bDer[2] += dirD * 0.031;
    
    if(LoR == 0)
    {
        position[2] += dir * velocidad;
    }
    else if(LoR == 1)
    {
        position[0] += dir * velocidad;
    }
    else if(LoR == 2)
    {
        position[2] -= dir * velocidad;
    }
    else if(LoR == 3)
    {
        position[0] -= dir * velocidad;
    }
    
}
