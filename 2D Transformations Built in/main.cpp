//
//  main.cpp
//  2D Transformations Built in
//
//  Created by Andie Goode on 11/1/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>

GLsizei winWidth = 300, winHeight = 300;

void init (void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 300.0, 0.0, 300.0);
}

void drawImage(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);

    float temp =(180/3.14159)*((5*3.14159)/3);
    glColor3f(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(18, 45, 0);
    glTranslatef(0, 100, 0);
    glTranslatef(75, 50,0);
    glRotatef(temp , 0, 0, 1);
    glScalef(0.5, 0.5, 0);

    glBegin(GL_POLYGON);
    glVertex2f(0, 100);
    glVertex2f(50, 150.0);
    glVertex2f(100.0, 100.0);
    glVertex2f(50.0, 25.0);
    glEnd();
    
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 100);
    glVertex2f(50, 150.0);
    glVertex2f(100.0, 100.0);
    glVertex2f(50.0, 25.0);
    glEnd();
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Built-in Transformation");
    init();
    glutDisplayFunc (drawImage);
    glutMainLoop();
}


