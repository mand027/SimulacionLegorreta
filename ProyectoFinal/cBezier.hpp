//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//  cBezier.hpp
//  BezierPr
//
//  Created by Luis Eduardo Brime Gomez on 3/31/19.
//  Copyright © 2019 Luis Eduardo Brime Gomez. All rights reserved.
//
#pragma once
#include "cPoint.hpp"

class Bezier {
public:
    Bezier(int _degree, Point** _ctrlPoints);
    ~Bezier();
    
    void calculateCoefficients();
    int factorial(int n);
    float combination(int n, int i);
    Point* evaluateBezier(float t);
    
    int degree;
    Point** ctrlPoints;
    float* coefficient;
};
