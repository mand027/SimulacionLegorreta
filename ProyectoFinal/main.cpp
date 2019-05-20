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
#include "cPlayere.hpp"
#include "cPoint.hpp"
#include "cBezier.hpp"
#include "cPlano.hpp"
#include "cPersone.hpp"
#include "cCamera.hpp"
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

Camera* mainCam;
const int numPerson = 100;
Plano* plano;
Persone* persone[numPerson];
Persone* other;
Playere* player;
Bezier* bez[5];
Point* ctrl[CTRL_POINTS];
Point* traveler[5];
Point* Try;
float param;
float dir;
float* pos;
int mouseCords[2];
int mouseMotionType = 0;
int playerDir;


void init( void )
{
    playerDir = 5;
    mainCam = new Camera();
    
    mainCam->pos.x = 0.0f;
    mainCam->pos.y = 30.0f;
    mainCam->pos.z = 0.0f;
    mainCam->dir.x = 0;
    mainCam->dir.y = 0;
    mainCam->dir.z = 0;
    mainCam->up.y = 0;
    mainCam->up.x = 0;
    mainCam->up.z = 1;
    
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
        ctrl[i] = new Point(0, 0, 0.5f);
    }
    
    ctrl[5]->x = 8; ctrl[5]->z = -0.6; ctrl[5]->y = 0.0f;
    ctrl[4]->x = 5.5; ctrl[4]->z = -0.4; ctrl[4]->y = 0.0f;
    ctrl[3]->x = 2.5; ctrl[3]->z = 0; ctrl[3]->y = 0.0f;
    ctrl[2]->x = -0.5; ctrl[2]->z = 1; ctrl[2]->y = 0.0f;
    ctrl[1]->x = -3.0; ctrl[1]->z = 1.5; ctrl[1]->y = 0.0f;
    ctrl[0]->x = -5; ctrl[0]->z = 4; ctrl[0]->y = 0.0f;
    bez[0] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 0; ctrl[5]->z = 6.5; ctrl[5]->y = 0.0f;
    ctrl[4]->x = 0.2; ctrl[4]->z = 5.5; ctrl[4]->y = 0.0f;
    ctrl[3]->x = 0.0; ctrl[3]->z = 4; ctrl[3]->y = 0.0f;
    ctrl[2]->x = -0.5; ctrl[2]->z = 2; ctrl[2]->y = 0.0f;
    ctrl[1]->x = -3.0; ctrl[1]->z = -0.5; ctrl[1]->y = 0.0f;
    ctrl[0]->x = -5; ctrl[0]->z = 4; ctrl[0]->y = 0.0f;
    bez[1] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = -3.5; ctrl[5]->z = -7.6; ctrl[5]->y = 0.0f;
    ctrl[4]->x = -3; ctrl[4]->z = -5.4; ctrl[4]->y = 0.0f;
    ctrl[3]->x = -2.3; ctrl[3]->z = -2.5; ctrl[3]->y = 0.0f;
    ctrl[2]->x = -1; ctrl[2]->z = 0; ctrl[2]->y = 0.0f;
    ctrl[1]->x = -2.0; ctrl[1]->z = 2.5; ctrl[1]->y = 0.0f;
    ctrl[0]->x = -5; ctrl[0]->z = 4; ctrl[0]->y = 0.0f;
    bez[2] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 8; ctrl[5]->z = -0.6; ctrl[5]->y = 0.0f;
    ctrl[4]->x = 5.5; ctrl[4]->z = -0.4; ctrl[4]->y = 0.0f;
    ctrl[3]->x = 2.5; ctrl[3]->z = 0; ctrl[3]->y = 0.0f;
    ctrl[2]->x = -0.5; ctrl[2]->z = 1; ctrl[2]->y = 0.0f;
    ctrl[1]->x = -3.0; ctrl[1]->z = 1.5; ctrl[1]->y = 0.0f;
    ctrl[0]->x = -5; ctrl[0]->z = 4; ctrl[0]->y = 0.0f;
    bez[3] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    ctrl[5]->x = 0; ctrl[5]->z = 6.5; ctrl[5]->y = 0.0f;
    ctrl[4]->x = 0.2; ctrl[4]->z = 5.5; ctrl[4]->y = 0.0f;
    ctrl[3]->x = 0.0; ctrl[3]->z = 4; ctrl[3]->y = 0.0f;
    ctrl[2]->x = -0.5; ctrl[2]->z = 2; ctrl[2]->y = 0.0f;
    ctrl[1]->x = -3.0; ctrl[1]->z = -0.5; ctrl[1]->y = 0.0f;
    ctrl[0]->x = -5; ctrl[0]->z = 4; ctrl[0]->y = 0.0f;
    bez[4] = new Bezier(CTRL_POINTS - 1, ctrl);
    
    plano = new Plano();
    
    player = new Playere();
    
    for(int i = 0; i< numPerson; i++){
        //printf("%Persona: %d", i);
        float vel = 0.0003 + (0.0006 - 0.0003) * (float)rand() / RAND_MAX;
        int linea = (rand() %5 );
//        printf("Persona: %d, Linea: %d, Speedo: %f\n", i, linea, vel);
        persone[i] = new Persone(linea, vel);
    }
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glClearColor(0.0, 0.0, 0.0, 0.0);                                // Clear the color state.
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    
    glLightfv(GL_LIGHT0, GL_POSITION, L0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ia);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Id);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is);
    
    glLightfv(GL_LIGHT1, GL_POSITION, L1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, Ia);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Id);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Is);
    
//    global_ambient = new GLfloat[4];
//    global_ambient[0] = 0.3f;
//    global_ambient[1] = 0.3f;
//    global_ambient[2] = 0.3f;
//    global_ambient[3] = 1.0f;
//    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );
//    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
//    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );

    glMatrixMode(GL_MODELVIEW);                                      // Go to 3D mode.
    glLoadIdentity();
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);              // Clear color and depth buffers.
    glLoadIdentity();                                                // Reset 3D view matrix.
    gluLookAt(mainCam->pos.x, mainCam->pos.y, mainCam->pos.z,        // Where the camera is.
              mainCam->dir.x, mainCam->dir.y, mainCam->dir.z,        // To where the camera points at.
              mainCam->up.x, mainCam->up.y, mainCam->up.z
              );
    
    plano->draw();
    
    for(int i = 0; i < numPerson; i++){
        persone[i]->Draw();
    }
    player->Draw();
    
    // Development only
    //bez[3]->draw();
    
    glutSwapBuffers();
}

void idle( void )
{
    
    for(int i = 0; i< numPerson; i++){
        
        for(int j = 0; j< numPerson; j++){
            if(j != i && persone[i]->linea == persone[j]->linea) persone[i]->OnCollision(persone[j]);
        }

        float tAux = persone[i]->t;
        tAux += persone[i]->dir * persone[i]->velocidad;
        
        if (tAux > 1 || tAux < 0) persone[i]->dir = (persone[i]->dir)* -1;
        
        int aux = persone[i]->linea;
        Try = bez[aux]->evaluateBezier(tAux);
        persone[i]->position[0] = Try->x;
        persone[i]->position[1] = Try->y;
        persone[i]->position[2] = Try->z;
//        printf("PosX %f | PosY %f | PosZ %f | T %f\n", Try->x,Try->y,Try->z,tAux);
        
        persone[i]->onCollision2(player);
        persone[i]->Animar();
        persone[i]->t = tAux;

    }
    
    player->Animar();
    glutPostRedisplay();
}

void motion(int x, int y) {
    switch (mouseMotionType) {
        case 1:
            mainCam->moveAround(-(mouseCords[1]-y)*0.001, vector3f(1,0,0));
            mainCam->moveAround(-(mouseCords[0]-x)*0.001, vector3f(0,1,0));
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    mouseCords[0] = x;
    mouseCords[1] = y;
    int mods;
    
    if (state == GLUT_DOWN) {
        mods = glutGetModifiers();
        if (mods & GLUT_ACTIVE_SHIFT) {
            mouseMotionType = 2;
        }else
            mouseMotionType = 1;
    }
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

void littleKey(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            player->LoR = 0;
            printf("w");
            break;
        case 'a':
            player->LoR = 1;
            printf("a");
            break;
        case 's':
            player->LoR = 2;
            printf("s");
            break;
        case 'd':
            player->LoR = 3;
            printf("d");
            break;
    }
}

int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 100, 10 );
    glutCreateWindow( "Legorreta" );
    
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc( reshape );
    glutKeyboardFunc( littleKey );
    init();
    glutDisplayFunc( display );
    glutIdleFunc( idle );
    glutMainLoop();
    return 0;
}
