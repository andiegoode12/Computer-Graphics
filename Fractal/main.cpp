//
//  main.cpp
//  Fractal
//
//  Created by Andie Goode on 8/31/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0); //Red,Gree,Blue,transparency
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}

void setColor(int x, int y){
    glBegin(GL_POINTS);
    glPointSize(10);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

void lineSegment(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);//clear buffer
    
    glColor3f(1.0, 0.0, 0.0);
    setColor(100,100);
    

    /*
     glColor3f(0.0,0.4,0.2); //set color
     glBegin(GL_LINES); //begin line
     glVertex2i(180,15); //coordinates of one endpoint
     glVertex2i(10,145); //coordinates of second endpoint
     glEnd(); //end line
     
     glColor3f(1.0,0.4,0.2);
     glBegin(GL_LINES);
     glVertex2i(0,15);
     glVertex2i(10,145);
     glEnd();
     
     glPointSize(10);
     glBegin(GL_POINTS);
     for(int i=0;i<20;i++){
     glColor3f(0.0,0.0,0.0);
     glVertex2i(i+10,i+10);
     }
     glEnd();
     */
    
    glFlush();
}
int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("Fractal");
    init();
    glutDisplayFunc(lineSegment); //one per window
    glutMainLoop();
}
