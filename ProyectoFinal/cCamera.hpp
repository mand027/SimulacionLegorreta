//  cCamera.hpp
//  Particles
//
//  Created by Armando Hernandez on 4/22/19.
//  Copyright © 2019 Armando Hernandez. All rights reserved.
//
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#pragma once
#include <stdio.h>
#include "vecs.hpp"

#ifndef __CAM
#define __CAM
class Camera{
public:
    Camera();
    ~Camera();
    
    void setView();
    void move(float dir, float angle);
    void rotate(float angle, vector3f p);
    bool pointInFrustum(vector3f p);
    void moveAround(float angle, vector3f axis);
    void newFarClose();
    vector3f pos;
    vector3f dir;
    vector3f up;
    vector3f pivot;
    float near_plane;
    float far_plane;
    float fov;
};
#endif /* cCamera_hpp */
