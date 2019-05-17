
//
//  cCamera.cpp
//  Particles
//
//  Created by Armando Hernandez on 4/22/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "cCamera.hpp"

Camera::Camera()
{
    pos.x = 0;
    pos.y = 0;
    pos.z = 10;
    
    dir.x = 0;
    dir.y = 0;
    dir.z = -1;
    
    up.x = 0;
    up.y = 1;
    up.z = 0;
    
    pivot.x = pivot.y = pivot.z = 0;
    
    near_plane = 1.0;
    far_plane = 100;
    fov = 45;
}


void Camera::setView()
{
    int viewportCoords[4];
    glGetIntegerv(GL_VIEWPORT, viewportCoords);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (GLfloat)viewportCoords[2] / (GLfloat)viewportCoords[3], near_plane, far_plane);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(pos.x, pos.y, pos.z,
              pos.x+dir.x, pos.y+dir.y, pos.z+dir.z,
              up.x, up.y, up.z
              );
}

void Camera::move(float dist, float angle)
{
    vector3f right;
    vector3f moveDir;
    float cosAng, sinAng, radAng;
    radAng = angle * M_PI / 180.0;
    cosAng = cos(radAng);
    sinAng = sin(radAng);
    
    float d[] = {dir.x, dir.y, dir.z};
    float u[] = {up.x, up.y, up.z};
    float r[] = {right.x, right.y, right.z};
    crossProduct(d, u, r);
    moveDir.x = d[0] * cosAng - r[0] * sinAng;
    moveDir.y = d[1] * cosAng - r[1] * sinAng;
    moveDir.z = d[2] * cosAng - r[2] * sinAng;
    pos.x += dist * moveDir.x;
    pos.y += dist * moveDir.y;
    pos.z += dist * moveDir.z;
    
}

void Camera::newFarClose()
{
    if(up.x>0){
        near_plane = pos.y - near_plane;
        far_plane = pos.y - far_plane;
    }else if(up.y>0){
        near_plane = near_plane - pos.x;
        far_plane = far_plane - pos.x;
    }else if (up.z>0){
        near_plane = near_plane - pos.y;
        far_plane = far_plane - pos.y;
    }
    
    if (near_plane < 0) near_plane = -near_plane;
    if (far_plane < 0) far_plane = -far_plane;
    
}

void Camera::moveAround(float angle, vector3f axis)
{
    float d[] = {dir.x, dir.y, dir.z};
    float u[] = {up.x, up.y, up.z};
    float r[] = {0,0,0};
    crossProduct(d, u, r);
    float a[] = {axis.x, axis.y, axis.z};
    unitVector(a);
    
    float negPos[] = {pos.x - pivot.x, pos.y - pivot.y, pos.z - pivot.z};
    float distPivot = vecMagnitude(negPos);
    unitVector(negPos);
    float radAng = DEGTORAD(angle);
    float newPos[] = {0,0,0};
    float newDir[] = {0,0,0};
    float newUp[] = {0,1,0};
    rotatePointAroundAxis(negPos, a, radAng, newPos);
    rotatePointAroundAxis(d, a, radAng, newDir);
    rotatePointAroundAxis(d, a, radAng, newUp);
    
    pos.set(pivot.x + newPos[0] * distPivot, pivot.y + newPos[1] * distPivot, pivot.z + newPos[2]* distPivot);
    dir.set(newDir[0], newDir[1], newDir[2]);
    up.set(newUp[0], 1, newUp[2]);
}

void Camera::rotate(float angle, vector3f axis)
{
    float ax[] = {axis.x, axis.y, axis.z};
    unitVector(ax);
    float radAng = DEGTORAD(angle);
    float d[] = {dir.x, dir.y, dir.z};
    float newD[] = {0, 0, 0};
    rotatePointAroundAxis(d, ax, radAng, newD);
    
    float u[] = {up.x, up.y, up.z};
    float newU[] = {0,0,0};
    rotatePointAroundAxis(u, ax, radAng, newU);
    
    dir.set(newD[0], newD[1], newD[2]);
    up.set(newU[0], newU[1], newU[2]);
}

bool Camera::pointInFrustum(vector3f p)
{
    bool iX, iY, iZ;
    float pointcz, pointcx, pointcy, temp;
    
    iX = iY = iZ = false;
    
    vector3f Z = pos - dir;
    Z.normalize();
    //printf("Z %f \n", Z);
    
    vector3f X = up - Z;
    X.normalize();
    //printf("X %f \n", X);
    
    vector3f Y = Z * X;
    Y.normalize();
    //printf("Y %f \n", Y);
    
    vector3f v = p - pos;
    //printf("v %f \n", v);
    
    float* aux1 = new float[3];
    float* aux2 = new float[3];
    
    aux1[0] = v.x;
    aux1[1] = v.y;
    aux1[2] = v.z;
    
    aux2[0] = Z.z;
    aux2[1] = Z.y;
    aux2[2] = Z.z;
    
    pointcz = dotProduct(aux1,aux2);
    if (pointcz < 0) pointcz = -pointcz;
    if(pointcz > far_plane || pointcz < near_plane)
    {
        iZ = false;
    }else iZ = true;
    
    aux2[0] = Y.z;
    aux2[1] = Y.y;
    aux2[2] = Y.z;
    pointcy = dotProduct(aux1, aux2);
    temp = pointcy*tan(DEGTORAD(fov));
    //printf("temp %f \n", temp);
    //printf("pointY %f \n", pointcy);
    if(pointcy > temp || pointcy < -temp)
    {
        iY = false;
    }else iY = true;
    
    aux2[0] = X.z;
    aux2[1] = X.y;
    aux2[2] = X.z;
    pointcx = dotProduct(aux1, aux2);
    //printf("pointX %f \n", pointcx);
    if(pointcx > temp || pointcx < -temp)
    {
        iX = false;
    }else iX = true;
    
    if(iX && iY && iZ){
        return true;
    }
    else return false;
}

Camera::~Camera(){
    
}
