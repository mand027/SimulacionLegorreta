//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//  cBezier.cpp
//  BezierPr
//
//  Created by Luis Eduardo Brime Gomez on 3/31/19.
//  Copyright © 2019 Luis Eduardo Brime Gomez. All rights reserved.
//

#include "cBezier.hpp"

Bezier::Bezier(int _degree, Point** _ctrlPoints)
{
    degree = _degree;
    coefficient = new float[degree + 1];
    ctrlPoints = new Point*[degree + 1];
    // copy the points
    for (int i = 0; i <= degree; i++) {
        ctrlPoints[i] = new Point(_ctrlPoints[i]);
    }
    calculateCoefficients();
}


Bezier::~Bezier()
{
    // Manage memory (no GC in C++)
    delete ctrlPoints;
}

void Bezier::calculateCoefficients() {
    for (int i = 0; i <= degree; i++) {
        coefficient[i] = combination(degree, i);
    }
}

int Bezier::factorial(int n) {
    if (n == 0) return 1;
    else return n * factorial(n - 1);
}

float Bezier::combination(int n, int i) {
    float nf = (float)factorial(n);
    return nf / (factorial(i)*factorial(n - i));
}

Point* Bezier::evaluateBezier(float t) {
    
    Point* p = new Point(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < degree; i++)
    {
        float c = pow(1 - t, degree - i)* pow(t, i);
        p = p->add(ctrlPoints[i]->multiplyByScalar(coefficient[i] * c));
        
    }
    return p;
}

// Development only
void Bezier::draw() {
    for (int i = 0; i < 6; i++) {
        ctrlPoints[i]->draw();
    }
}
