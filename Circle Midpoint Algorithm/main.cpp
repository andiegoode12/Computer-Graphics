//
//  main.cpp
//  Circle Midpoint Algorithm
//
//  Created by Andie Goode on 10/18/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <GLUT/GLUT.h>

GLsizei winWidth = 400, winHeight = 200;// Initial display window size.

class screenPt
{
private:
    GLint x, y;
public:
    /*  Default Constructor: initializes coordinate position to (0, 0).  */
    screenPt ( )  {
        x = y = 0; }
    void setCoords (GLint xCoordValue, GLint yCoordValue)  {
        x = xCoordValue;
        y = yCoordValue;
    }
    GLint getx ( ) const  {
        return x;
    }
    GLint gety ( ) const  {
        return y;
    }
    void incrementx ( )  {
        x++; }
    void decrementy ( )  {
        y--;
    } };


void init (void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 400.0, 0.0, 200.0);
}

void setPixel (GLint xCoord, GLint yCoord){
    glBegin (GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd ( );
}

void circleMidpoint (GLint xc, GLint yc, GLint radius){
    screenPt circPt;
    GLint p = 1 - radius;         //  Initial value for midpoint parameter.
    circPt.setCoords (0, radius); //  Set coordinates for top point of circle.
    void circlePlotPoints (GLint, GLint, screenPt);
    /*  Plot the initial point in each circle quadrant.  */
    circlePlotPoints (xc, yc, circPt);
    /*  Calculate next point and plot in each octant.  */
    while (circPt.getx ( ) < circPt.gety ( )) {
        circPt.incrementx ( );
        if (p < 0)
            p += 2 * circPt.getx ( ) + 1;
        else {
            circPt.decrementy ( );
            p += 2 * (circPt.getx ( ) - circPt.gety ( )) + 1;
        }
        circlePlotPoints (xc, yc, circPt);
    }
}

void circlePlotPoints (GLint xc, GLint yc, screenPt circPt){
    setPixel (xc + circPt.getx ( ), yc + circPt.gety ( ));
    setPixel (xc - circPt.getx ( ), yc + circPt.gety ( ));
    setPixel (xc + circPt.getx ( ), yc - circPt.gety ( ));
    setPixel (xc - circPt.getx ( ), yc - circPt.gety ( ));
    setPixel (xc + circPt.gety ( ), yc + circPt.getx ( ));
    setPixel (xc - circPt.gety ( ), yc + circPt.getx ( ));
    setPixel (xc + circPt.gety ( ), yc - circPt.getx ( ));
    setPixel (xc - circPt.gety ( ), yc - circPt.getx ( ));
}

void winReshapeFcn (GLint newWidth, GLint newHeight){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
    glClear (GL_COLOR_BUFFER_BIT);
    /*  Reset display-window size parameters.  */
    winWidth = newWidth;
    winHeight = newHeight;
}

void displayFcn (void){
    glClear (GL_COLOR_BUFFER_BIT);//  Clear display window.
    glPointSize(5.0);
    glColor3f(0.0,0.0,0.0);
    circleMidpoint(winWidth/2, winHeight-75, 50);
    glColor3f(1.0, 0.0, 0.0);
    circleMidpoint(winWidth/2 + 115, winHeight-75, 50);
    glColor3f(0.0, 0.0, 1.0);
    circleMidpoint(winWidth/2 - 115, winHeight-75, 50);
    glColor3f(0.0, 1.0, 0.0);
    circleMidpoint(winWidth/2 + 60, winHeight-125, 50);
    glColor3f(1.0, 1.0, 0.0);
    circleMidpoint(winWidth/2 - 60, winHeight-125, 50);
    glFlush ( );
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Circle Midpoint");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}
