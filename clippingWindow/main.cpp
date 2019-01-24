//
//  main.cpp
//  clippingWindow
//
//  Created by Andie Goode on 11/4/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <vector>
GLsizei winWidth = 300, winHeight = 300;

class wcPt2D {
public:
    GLint x, y;
};

void init (void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    //clipping window
    gluOrtho2D (-51, 51, -5, 21);
    glMatrixMode(GL_MODELVIEW);
}

void displayFcn (void){
    wcPt2D verts [30] = { {-35,-50}, {-20, 30}, {-20, 30}, {-12, -10}, {-12, -10}, {5, 50}, {5, 50}, {12, -10}, {12, -10}, {25, 30}, {25, 30}, {40, -50}, {-35, -50}, {40, -50}, {-25, 0}, {-20, -10}, {-20, -10}, {-15, 0}, {-10, 0}, {-5, -10}, {-5, -10}, {5, 0}, {5, 0}, {7, -10}, {7, -10}, {10, 0}, {15, 0}, {20, -10}, {20, -10}, {30, 0} };
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    glViewport(0, 0, 200, 200);

    glViewport(0, 0, 200, 200);
    glBegin(GL_LINES);
    for (int i = 0; i<30; i++){
        glVertex2i(verts[i].x, verts[i].y);
    }
    glEnd();
    glFlush ( );
}

int main (int argc, char ** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Clipping Window and Viewport");
    init ( );
    glutDisplayFunc (displayFcn);
    glutMainLoop ( );
}
