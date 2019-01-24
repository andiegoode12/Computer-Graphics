//
//  main.cpp
//  3D Orthogonal Projection
//
//  Created by Andie Goode on 12/5/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <math.h>

GLint winWidth = 600, winHeight = 600; // Initial display-window size.
GLfloat x0 = 125.0, yO = 200.0, z0 = 200.0; // Viewing-coordinate origin.
GLfloat xref = 50.0, yref = 50.0, zref = -50.0; // Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // View-up vector.
/* Set coordinate limits for the clipping window: */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/* Set positions for near and far clipping planes: */
GLfloat dnear = 25.0, dfar = 600.0;

const double TWO_PI = 6.2831853;
const double PI = 3.14159;

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_MODELVIEW);
    gluLookAt (x0, yO, z0, xref, yref, zref, Vx, Vy, Vz);
    glMatrixMode (GL_PROJECTION);
    glFrustum (xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    /* Set parameters for a square fill area. */
    glColor3f (0.0, 0.7, 1.0); // Set fill color to green.
    glPolygonMode (GL_FRONT, GL_FILL);
    glPolygonMode (GL_BACK, GL_LINE); // Wire-frame back face.
    
    //CUBE
    glBegin (GL_QUADS);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (100.0, 0.0, 0.0);
    glVertex3f (100.0, 100.0, 0.0);
    glVertex3f (0.0, 100.0, 0.0);
    glEnd ( );
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(100.0, 100.0,0.0);
    glVertex3f(100.0, 100.0, 100.0);
    glVertex3f(100.0, 0.0, 100.0);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 100.0,0.0);
    glVertex3f(0.0, 100.0, 100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f (0.0, 0.0, 100.0);
    glVertex3f (100.0, 0.0, 100.0);
    glVertex3f (100.0, 100.0, 100.0);
    glVertex3f (0.0, 100.0, 100.0);
    glEnd();
    
    
    //SPHERE
    float radius = 75.0;
    float xc = 200.0;
    float yc = 150.0;
    float zc = -100.0;
    float x, y, z;
    int vertical = 25;
    int horizontal = 25;
    
    glBegin(GL_LINE_LOOP);
    for(float p = 0; p < PI; p += (PI/vertical)){
         y = yc + radius * cos(p);
        for(float t = 0; t < TWO_PI; t += (PI/60)){
            x = xc + radius * cos(t) * sin(p);
            z = zc + radius * sin(t) * sin(p);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
    x = 0.0;
    y = 0.0;
    z = 0.0;
    glBegin(GL_LINE_LOOP);
    for(float p = 0; p < PI; p += (PI/horizontal)){
        for(float t = 0; t < TWO_PI; t += (PI/60)){
            x = xc + radius * cos(p) * sin(t);
            y = yc + radius * cos(t);
            z = zc + radius * sin(p) * sin(t);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
    
    //CONE
    glColor3f(0.5, 0.3, 0.1);
    float r = 150.0;
    float xc1 = -100.0;
    float zc1 = -150.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
    vertical = 15;
    horizontal = 15;
    
    glBegin(GL_LINE_LOOP);
    for(float y = 75; y < 150; y++){
        for(float t = 0; t<TWO_PI; t += (PI/60)){
            x = xc1 + r * cos(t);
            z = zc1 + r * sin(t);
            glVertex3f(x, y, z);
        }
        r -= 2;
    }
    glEnd();
    
    glFlush ( );
}

void reshapeFcn (GLint newWidth, GLint newHeight)
{
    glViewport (0, 0, newWidth, newHeight);
    winWidth = newWidth;
    winHeight = newHeight;
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Perspective View of A Square");
    init ( );
    glutDisplayFunc (displayFcn);
    glutReshapeFunc (reshapeFcn);
    glutMainLoop ( );
}
