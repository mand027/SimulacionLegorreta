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
#include "cPersone.hpp"
#include <cstdlib>
#define CTRL_POINTS 6

GLfloat*    global_ambient;
//GLMmodel*    plano;

GLfloat* ka;
GLfloat* kd;
GLfloat* ks;
GLfloat* alpha;
//4D arrays for light constraints
GLfloat* L0pos;
GLfloat* L1pos;
GLfloat* Ia;
GLfloat* Id;
GLfloat* Is;

Plano* plano;
Persone* persone;

Bezier* bez[5];
Point* ctrl[CTRL_POINTS];
Point* traveler[5];
float param;
float dir;
float* pos;

int randomBetween (float min, float max){
    float random = min + (max - min) * (float)rand() / RAND_MAX;
    return random;
}

void init( void )
{
    
    //material plane
    ka = new GLfloat[4];
    ka[0] = 0.0f; //red
    ka[1] = 0.0f; //green
    ka[2] = 0.1f; //blue
    ka[3] = 1.0f; //alpha
    
    kd = new GLfloat[4];
    kd[0] = 0.25f;
    kd[1] = 0.15f;
    kd[2] = 1.0f;
    kd[3] = 1.0f; //allways 1
    
    ks = new GLfloat[4];
    ks[0] = 0.2f;
    ks[1] = 0.2f;
    ks[2] = 0.3f;
    ks[3] = 1.0f;
    
    alpha = new GLfloat[1];
    alpha[0] = 50.0f;
    
    //light begins
    L0pos = new GLfloat[4];
    L0pos[0] = 5.0f;
    L0pos[1] = 5.0f;
    L0pos[2] = 5.0f;
    L0pos[3] = 1.0f;
    //l0pos [3] == 1 point light
    //L0pos [3] == 0 directional light
    
    //light begins
    L1pos = new GLfloat[4];
    L1pos[0] = -5.0f;
    L1pos[1] = 10.0f;
    L1pos[2] = -5.0f;
    L1pos[3] = 0.0f;
    //l0pos [3] == 1 point light
    //L0pos [3] == 0 directional light
    
    Ia = new GLfloat[4];
    Id = new GLfloat[4];
    Is = new GLfloat[4];
    for(int i =0; i<4; i++){
        Ia[i] = 1.0f;
        Id[i] = 1.0f;
        Is[i] = 1.0f;
    }
    //light is bright
    
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
    float vel = 0.000004;
    persone = new Persone(1, vel);
    
    
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    glLightfv(GL_LIGHT0, GL_POSITION, L0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ia);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Id);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is);
    
    glLightfv(GL_LIGHT1, GL_POSITION, L1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, Ia);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Id);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Is);
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    
    glMatrixMode(GL_MODELVIEW);                                      // Go to 3D mode.
    glLoadIdentity();
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(0,20,0,
              0,0,0,
              0,0,1);
   
    persone->Draw();
    plano->draw();

    for (int i =0; i<5; i++) {
        traveler[i] = bez[i]->evaluateBezier(persone->t);
        persone->position[0] = ;
    }
        //randomBetween(0, 2)
    glutSwapBuffers();
}

void idle( void )
{
    persone->t += dir * 0.0023f;
    if (persone->t > 1 || persone->t < 0) dir = -dir;
    glutPostRedisplay();
    
    persone->Animar();
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
