//
//  cPoint.cpp
//  BezierPr
//
//
// Armando Alberto Hernández Vargas A01334836
// José Gustavo Genel Castañeda A01331780
// Luis Eduardo Brime Gomez A01334886
// Jorge Eduardo Rivera Montes A01371945
//
//

#include "cPoint.hpp"

Point::Point(float _x, float _y, float _z)
{
    x = _x; y = _y; z = _z;
    
}

Point::Point(Point* other)
{
    x = other->x;
    y = other->y;
    z = other->z;
}

Point::~Point()
{
}

Point* Point::multiplyByScalar(float s) {
    Point* p = new Point(this);
    p->x *= s;
    p->y *= s;
    p->z *= s;
    
    return p;
}

Point* Point::add(Point* other) {
    Point* p = new Point(this);
    p->x += other->x;
    p->y += other->y;
    p->z += other->z;
    return p;
}

void Point::update() {
    
}

void Point::draw() {
    glPushMatrix();
    {
        glTranslatef(x, y, z);
        glColor3f(1, 0, 0);
        glutSolidSphere(0.4, 10, 10);
    }
    glPopMatrix();
}
