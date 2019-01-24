//
//  main.cpp
//  Liang-Barsky Line clipping
//
//  Created by Andie Goode on 11/4/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>

GLsizei winWidth = 300, winHeight = 300;

class wcPt2D
{
private:
    
public:
    GLfloat x, y;
    /*  Default Constructor: initialize position as (0.0, 0.0).  */
    wcPt2D (GLfloat xCoord, GLfloat yCoord) {
        x = xCoord;
        y = yCoord;
    }
    void setCoords (GLfloat xCoord, GLfloat yCoord) {
        x = xCoord;
        y = yCoord;
    }
    GLfloat getx ( ) const {
        return x; }
    GLfloat gety ( ) const {
        return y; }
};

void init (void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0, 300, 0, 300);
}

void setPixel (GLint xCoord, GLint yCoord) {
    glBegin (GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd ( );
}


void lineBres (float x0, float y0, float xEnd, float yEnd)
{
    int dx = fabs (xEnd - x0),  dy = fabs(yEnd - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx), twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
    int x, y;
    if(dx==0){
        if (x0 > xEnd) {
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else {
            x = x0;
            y = y0; }
        setPixel (x, y);
        while (y < yEnd) {
            y++;
            setPixel (x, y);
        }
    }
    else if(dy==0){
        if (x0 > xEnd) {
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else {
            x = x0;
            y = y0; }
        setPixel (x, y);
        while (x < xEnd) {
            x++;
            setPixel (x, y);
        }
    }
    if (dy!=0 && dx!=0){
        double m = double(yEnd - y0)/double(xEnd - x0);
        //slope between 0 and 1
        if(0< m && m <= 1.0){
            if (x0 > xEnd) {
                x = xEnd;
                y = yEnd;
                xEnd = x0;
                yEnd = y0;
            }
            else {
                x = x0;
                y = y0; }
            setPixel (x, y);
            while (x < xEnd) {
                x++;
                if (p < 0)
                    p += twoDy;
                else {
                    y++;
                    p += twoDyMinusDx;
                }
                setPixel (x, y);
            }
        }
        //slope m>1
        else if(1 < m){
            if (x0 > xEnd) {
                x = xEnd;
                y = yEnd;
                xEnd = x0;
                yEnd = y0;
            }
            else {
                x = x0;
                y = y0; }
            setPixel (x, y);
            while (y < yEnd) {
                y++;
                if (p < 0)
                    p += twoDx;
                else {
                    x++;
                    p += twoDxMinusDy;
                }
                setPixel (x, y);
            }
        }
        //slope m between -1 and 0
        else if(-1 <= m && m < 0){
            if (x0 > xEnd) {
                x = xEnd;
                y = yEnd;
                xEnd = x0;
                yEnd = y0;
            }
            
            else {
                x = x0;
                y = y0; }
            setPixel (x, y);
            while (x < xEnd) {
                x++;
                if (p < 0)
                    p += twoDy;
                else {
                    y--;
                    p += twoDyMinusDx;
                }
                setPixel (x, y);
            }
        }
        //slope m < -1
        else if(m < -1.0){
            if (x0 > xEnd) {
                x = xEnd;
                y = yEnd;
                xEnd = x0;
                yEnd = y0;
            }
            else {
                x = x0;
                y = y0; }
            setPixel (x, y);
            while (y > yEnd) {
                y--;
                if (p < 0)
                    p += twoDx;
                else {
                    x++;
                    p += twoDxMinusDy;
                }
                setPixel (x, y);
            }
        }
    }
}

GLint clipTest (GLfloat p, GLfloat q, GLfloat * u1, GLfloat * u2)
{
    GLfloat r;
    GLint returnValue = true;
    if (p < 0.0) {
        r = q / p;
        if (r > *u2)
            returnValue = false;
        else
            if (r > *u1)
                *u1 = r;
    } else
        if (p > 0.0) {
            r = q / p;
            if (r < *u1)
                returnValue = false;
            else if (r < *u2)
                *u2 = r; }
        else
        /*  Thus p = 0 and line is parallel to clipping boundary.  */
            if (q < 0.0)
            /*  Line is outside clipping boundary.  */
                returnValue = false;
    return (returnValue);
}
void lineClipLiangBarsk (wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
    GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx ( ) - p1.getx ( ), dy;
    if (clipTest (-dx, p1.getx ( ) - winMin.getx ( ), &u1, &u2))
        if (clipTest (dx, winMax.getx ( ) - p1.getx ( ), &u1, &u2)) {
            dy = p2.gety ( ) - p1.gety ( );
            if (clipTest (-dy, p1.gety ( ) - winMin.gety ( ), &u1, &u2))
                if (clipTest (dy, winMax.gety ( ) - p1.gety ( ), &u1, &u2)) {
                    if (u2 < 1.0) {
                        p2.setCoords (p1.getx ( ) + u2 * dx, p1.gety ( ) + u2 * dy);
                    }
                    if (u1 > 0.0) {
                        p1.setCoords (p1.getx ( ) + u1 * dx, p1.gety ( ) + u1 * dy);
                    }
                    lineBres (round (p1.getx ( )), round (p1.gety ( )),
                              round (p2.getx ( )), round (p2.gety ( )));
                } }
}

void displayFcn(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    wcPt2D vertices [30] = { {15,0}, {30, 80}, {30, 80}, {38, 40}, {38, 40}, {55, 100}, {55, 100}, {62, 40}, {62, 40}, {75, 80}, {75, 80}, {90, 0}, {25, 50}, {30, 40}, {30, 40}, {35, 50}, {40, 50}, {45, 40}, {45, 40}, {55, 50}, {55, 50}, {57, 40}, {57, 40}, {60, 50}, {65, 50}, {70, 40}, {70, 40}, {80, 50}, {15, 0}, {90,0} };
    wcPt2D window [2] = {{0, 45}, {100, 100}};
    for (int i = 0; i < 30; i+=2){
        lineClipLiangBarsk(window[0], window[1], vertices[i], vertices[i+1]);
    }
    glEnd();
    glFlush();
}

int main (int argc, char ** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Liang-Barsky");
    init ( );
    glutDisplayFunc (displayFcn);
    glutMainLoop ( );
}
