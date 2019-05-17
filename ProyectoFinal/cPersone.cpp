//
//  cPersone.cpp
//  ProyectoFinal
//
//  Created by Armando Hernandez on 5/16/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//

#include "cPersone.hpp"
#include "math.h"


int randomBetween (float min, float max){
    float random = min + (max - min) * (float)rand() / RAND_MAX;
    return random;
}

Persone::Persone(float linea_, float v){
    position = new float[3];
    position[0] = 0;
    position[1] = 0;
    position[2] = 0;
    linea = linea_;
    velocidad = v;
    t = 0.01;
    dir = 1;
    maxBrazo = 0.12f;
    minBrazo = -0.12f;
    
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
    
    float min = 0.01f;
    float max = 0.99f;
    ka = new GLfloat[4];
    ka[0] = min + (max - min) * (float)rand() / RAND_MAX; //red
    ka[1] = min + (max - min) * (float)rand() / RAND_MAX; //green
    ka[2] = min + (max - min) * (float)rand() / RAND_MAX; //blue
    ka[3] = 1.0f; //alpha
    
    kd = new GLfloat[4];
    kd[0] = min + (max - min) * (float)rand() / RAND_MAX;
    kd[1] = min + (max - min) * (float)rand() / RAND_MAX;
    kd[2] = min + (max - min) * (float)rand() / RAND_MAX;
    kd[3] = 1.0f; //always 1
    
    ks = new GLfloat[4];
    ks[0] = min + (max - min) * (float)rand() / RAND_MAX;
    ks[1] = min + (max - min) * (float)rand() / RAND_MAX;
    ks[2] = min + (max - min) * (float)rand() / RAND_MAX;
    ks[3] = 1.0f;
    
    alpha = new GLfloat[1];
    alpha[0] = 50.0f;}


void Persone::Draw(){
    
    
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

void Persone::CheckCollision(float cubeSize){
    
}

void Persone::OnCollision(Playere other){
    
}

void Persone::Avanzar(){
    
}

void Persone::Animar(){
    
    if(bDer[2] < minBrazo || bDer[2] > maxBrazo){
        dirD = -dirD;
    }
    if(bIzq[2] < minBrazo || bIzq[2] > maxBrazo){
        dirI = -dirI;
    }
    
    bIzq[2] += dirI * 0.031;
    bDer[2] += dirD * 0.031;
}
