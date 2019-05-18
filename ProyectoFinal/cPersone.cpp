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
    dir = 1;
    maxBrazo = 0.12f;
    minBrazo = -0.12f;
    radius = 0.35f;
    
    bIzq = new float[3];
    bDer = new float[3];
    
    bIzq[0] = 0.10f;
    bIzq[1] = 0.0f;
    bIzq[2] = 0.0f;
    
    bDer[0] = -0.10f;
    bDer[1] = 0.0f;
    bDer[2] = 0.0f;
    
    dirD = 1;
    dirI = -1;
    
    t = 0.01 + (0.99 - 0.01) * (float)rand() / RAND_MAX;

    
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
        glutSolidSphere(0.12f, 10, 10);
        
        glPushMatrix();
        {
            glTranslatef(bIzq[0], bIzq[1], bIzq[2]);
            glutSolidSphere(0.07f, 10, 10);

        }
        glPopMatrix();
        
        glPushMatrix();
        {

            glTranslatef(bDer[0], bDer[1], bDer[2]);
            glutSolidSphere(0.07f, 10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
    
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


void Persone::OnCollision(Persone* other){
    
    float sumRadius = radius + other->radius;
    float dx = other->position[0] - position[0];
    dx *= dx;
    float dy = other->position[1] - position[1];
    dy *= dy;
    float dz = other->position[2] - position[2];
    dz *= dz;
    
    float sumR2 = sumRadius * sumRadius;
    float dist2 = dx+dz+dy;
    if( dist2 < sumR2){
        Chokiamos(other);
    }
    else{
        //printf("No andamos Chiokando :D \n");
    }
}

void Persone::onCollision2(Playere* P1){
    
    float sumRadius = radius + P1->radius;
    float dx = P1->position[0] - position[0];
    dx *= dx;
    float dy = P1->position[1] - position[1];
    dy *= dy;
    float dz = P1->position[2] - position[2];
    dz *= dz;
    
    float sumR2 = sumRadius * sumRadius;
    float dist2 = dx+dz+dy;
    if( dist2 < sumR2){
        ChokiamosChief(P1);
    }
    else{
        //printf("No andamos Chiokando :D \n");
    }
}

void Persone::Chokiamos(Persone *other)
{
    int r = (rand() %100) +1;
    if(velocidad > other->velocidad ){
        printf("mevoa cambiar de: %d \n", linea);
        if(linea == 0) linea +=1;
        else if (linea == 4) linea -= 1;
        else {
            if(r < 50) linea = linea - 1 ;
            else if(r > 50) linea = linea + 1;
        }
        printf("me cambie a: %d \n", linea);
    }
}

void Persone::ChokiamosChief(Playere *P1)
{
    int r = (rand() %100) +1;
    
    printf("mevoa cambiar de: %d \n", linea);
    if(linea == 0) linea +=1;
        else if (linea == 4) linea -= 1;
        else {
        if(r < 50) linea = linea - 1 ;
        else if(r > 50) linea = linea + 1;
    }
    printf("me cambie a: %d \n", linea);
    
}
