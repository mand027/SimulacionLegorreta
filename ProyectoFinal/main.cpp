/*
 Armando Alberto Hernández Vargas A01334836
 José Gustavo Genel Castañeda A01331780
 Luis Eduardo Brime Gomez A01334886
 Jorge Eduardo Rivera Montes A01371945
 
 Computer Graphics. TC3022.
 Armando Hernandez Vargas A01334836
 
 Basic TGA textures.
 Displays a textured OBJ.
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <math.h>
//#include "glm.hpp"
#include "cPoint.hpp"
#include "cBezier.hpp"
#include "cPlano.hpp"
#include <cstdlib>
#define CTRL_POINTS 6

GLfloat*    global_ambient;
//GLMmodel*    plano;
Plano* plano;

Bezier* bez[5];
Point* ctrl[CTRL_POINTS];
Point* traveler[5];
float param;
float dir;

int randomBetween (float min, float max){
    float random = min + (max - min) * (float)rand() / RAND_MAX;
    return random;
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(0,20,0,
              0,0,0,
              0,0,1);
    glPushMatrix();
    {
        for (int i =0; i<5; i++) {
            traveler[i] = bez[i]->evaluateBezier(param);
            traveler[i]->draw();
        }
        //randomBetween(0, 2)

        plano->draw();
        glPopMatrix();
        glutSwapBuffers();
    }
}

void idle( void )
{
    param += dir * 0.0003f;
    if (param > 1 || param < 0) dir = -dir;
    glutPostRedisplay();
} 

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective( 60.0, w / h * 1.0, 0.01, 1024.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void init( void )
{
    dir = 1;
    param = 0;
    for (int i =0; i<5; i++) {
        traveler[i] = new Point(0, 0, 0);

    }
    
    for (int i = 0; i < CTRL_POINTS; i++) {
        ctrl[i] = new Point(0, 0, 0);
    }
    
    ctrl[5]->x = 6; ctrl[5]->z = -1; ctrl[5]->y = 1;
    ctrl[4]->x = 3.5; ctrl[4]->z = -2.5; ctrl[4]->y = 1;
    ctrl[3]->x = -0.5; ctrl[3]->z = -2.5; ctrl[3]->y = 1;
    ctrl[2]->x = -3.5; ctrl[2]->z = -2; ctrl[2]->y = 1;
    ctrl[1]->x = -5.5; ctrl[1]->z = -1; ctrl[1]->y = 1;
    ctrl[0]->x = -7.5; ctrl[0]->z = 2; ctrl[0]->y = 1;
    bez[0] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 10; ctrl[5]->z = -3; ctrl[5]->y = 1;
    ctrl[4]->x = 4; ctrl[4]->z = -3.5; ctrl[4]->y = 1;
    ctrl[3]->x = -2.5; ctrl[3]->z = -3.5; ctrl[3]->y = 1;
    ctrl[2]->x = -4.5; ctrl[2]->z = -3; ctrl[2]->y = 1;
    ctrl[1]->x = -8.5; ctrl[1]->z = -2; ctrl[1]->y = 1;
    ctrl[0]->x = -9.5; ctrl[0]->z = 3; ctrl[0]->y = 1;
    bez[1] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 4; ctrl[5]->z = -1; ctrl[5]->y = 1;
    ctrl[4]->x = 3; ctrl[4]->z = -3.5; ctrl[4]->y = 1;
    ctrl[3]->x = -1.5; ctrl[3]->z = -3.5; ctrl[3]->y = 1;
    ctrl[2]->x = -4.5; ctrl[2]->z = -3; ctrl[2]->y = 1;
    ctrl[1]->x = -5.5; ctrl[1]->z = -2; ctrl[1]->y = 1;
    ctrl[0]->x = -6.5; ctrl[0]->z = 3; ctrl[0]->y = 1;
    bez[2] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 3; ctrl[5]->z = -1; ctrl[5]->y = 1;
    ctrl[4]->x = 3; ctrl[4]->z = -3.5; ctrl[4]->y = 1;
    ctrl[3]->x = -1.5; ctrl[3]->z = -3.5; ctrl[3]->y = 1;
    ctrl[2]->x = -4.5; ctrl[2]->z = -3; ctrl[2]->y = 1;
    ctrl[1]->x = -5.5; ctrl[1]->z = -2; ctrl[1]->y = 1;
    ctrl[0]->x = -4.5; ctrl[0]->z = 3; ctrl[0]->y = 1;
    bez[3] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 3; ctrl[5]->z = -1; ctrl[5]->y = 1;
    ctrl[4]->x = 3; ctrl[4]->z = -3.5; ctrl[4]->y = 1;
    ctrl[3]->x = -1.5; ctrl[3]->z = -3.5; ctrl[3]->y = 1;
    ctrl[2]->x = -4.5; ctrl[2]->z = -3; ctrl[2]->y = 1;
    ctrl[1]->x = -5.5; ctrl[1]->z = -2; ctrl[1]->y = 1;
    ctrl[0]->x = -4.5; ctrl[0]->z = 5; ctrl[0]->y = 1;
    bez[4] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    plano = new Plano();
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    GLfloat diffusel0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambientl0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularl0[4]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[4]        = { 2.0f, 0.5f, 1.0f, 0.0f };
    glLightfv( GL_LIGHT0, GL_AMBIENT,   ambientl0  );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,   diffusel0  );
    glLightfv( GL_LIGHT0, GL_SPECULAR,  specularl0 );
    glLightfv( GL_LIGHT0, GL_POSITION,  position   );
    
    GLfloat global_ambient[4]            = {0.3f,0.3f,0.3f,1.0f};
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
}

void keyboard( unsigned char key, int x, int y )
{
}

int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 100, 10 );
    glutCreateWindow( "Legorreta" );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    init();
    glutDisplayFunc( display );
    glutIdleFunc( idle );
    glutMainLoop();
    return 0;
}
