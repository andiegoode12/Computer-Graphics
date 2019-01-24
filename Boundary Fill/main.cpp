//
//  main.cpp
//  Flood Fill
//
//  Created by Andie Goode on 10/25/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <math.h>



GLsizei winWidth = 400, winHeight = 200;// Initial display window size.

struct Color{
    float r;
    float g;
    float b;
    
    Color(float r, float g, float b) {
        this->r=r;
        this->g=g;
        this->b=b;
    }
    Color(){
        r=0;
        b=0;
        g=0;
    }
};

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

//inline int round (const float a)  { return int (a + 0.5); }

bool colorsEqual(Color a, Color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

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

Color getPixel (GLint xCoord, GLint yCoord){
    Color color;
    glReadPixels(xCoord, yCoord, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void ellipseMidpoint (int xCenter, int yCenter, int Rx, int Ry)
{
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2 * y;
    void ellipsePlotPoints (int, int, int, int);
    /* Plot the initial point in each quadrant. */
    ellipsePlotPoints (xCenter, yCenter, x, y);
    /* Region 1 */
    p = round (Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py) {
        x++;
        px += twoRy2;
        if (p < 0)
            p += Ry2 + px;
        else {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
    /* Region 2 */
    p = round (Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
    while (y > 0) {
        y--;
        py -= twoRx2;
        if (p > 0)
            p += Rx2 - py;
        else {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
}

void ellipsePlotPoints (int xCenter, int yCenter, int x, int y){
    setPixel (xCenter + x, yCenter + y);
    setPixel (xCenter - x, yCenter + y);
    setPixel (xCenter + x, yCenter - y);
    setPixel (xCenter - x, yCenter - y);
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

void boundaryFill4 (int x, int y, Color fillColor, Color borderColor)
{
    Color interiorColor;
    /* Set current color to fillColor, then perform the following operations. */
    glColor3f(fillColor.r, fillColor.g, fillColor.b);
    interiorColor = getPixel (x, y);
    if (!(colorsEqual(interiorColor, borderColor)) && !(colorsEqual(interiorColor, fillColor))) {
        setPixel (x, y);    // Set color of pixel to fillColor.
        boundaryFill4 (x + 1, y , fillColor, borderColor);
        boundaryFill4 (x - 1, y , fillColor, borderColor);
        boundaryFill4 (x , y + 1, fillColor, borderColor);
        boundaryFill4 (x , y - 1, fillColor, borderColor);
    } }

void displayFcn (void){
    glClear (GL_COLOR_BUFFER_BIT);//  Clear display window.
    glColor3f(0.0,0.0,0.0);
    ellipseMidpoint(winWidth/2, winHeight-75, 50, 40);
    boundaryFill4(winWidth/2, winHeight-75, Color(1.0f,0.0f,0.0f), Color(0.0f,0.0f,0.0f));
    glColor3f(1.0, 0.0, 0.0);
    ellipseMidpoint(winWidth/2 + 115, winHeight-75, 50, 40);
    boundaryFill4(winWidth/2 + 115, winHeight-75, Color(1.0f,1.0f,0.0f), Color(1.0f, 0.0f, 0.0f));
    glColor3f(0.0, 0.0, 1.0);
    ellipseMidpoint(winWidth/2 - 115, winHeight-75, 50, 40);
    boundaryFill4(winWidth/2 - 115, winHeight-75, Color(0.0f,0.0f,0.0f), Color(0.0f,0.0f,1.0f));
    glColor3f(0.0, 1.0, 0.0);
    ellipseMidpoint(winWidth/2 + 60, winHeight-125, 50, 40);
    boundaryFill4(winWidth/2 + 60, winHeight-125, Color(0.0f,0.0f,1.0f), Color(0.0f,1.0f,0.0f));
    glColor3f(1.0, 1.0, 0.0);
    ellipseMidpoint(winWidth/2 - 60, winHeight-125, 50, 40);
    boundaryFill4(winWidth/2 - 60, winHeight-125, Color(0.0f,1.0f,0.0f), Color(1.0f,1.0f,0.0f));
    glFlush ( );
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Flood Fill");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}


