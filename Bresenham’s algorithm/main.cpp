//
//  main.cpp
//  Bresenham’s algorithm
//
//  Created by Andie Goode on 10/15/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>

GLsizei winWidth = 300, winHeight=400;

void init (void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
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

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    //house 1
    glColor3f (0.0, 0.0, 0.0);
    lineBres(5,5,5,20);
    lineBres(5,20,47,20);
    lineBres(47,5,47,20);
    lineBres(5,5,47,5);
    lineBres(5,20,26,41);
    lineBres(26,41,47,20);
    //house 2
    glColor3f (0.6, 0.4, 0.3);
    lineBres(55,5,55,20);
    lineBres(55,20,97,20);
    lineBres(97,5,97,20);
    lineBres(55,5,97,5);
    lineBres(55,20,76,100);
    lineBres(76,100,97,20);
    //house 3
    glColor3f (0.6, 0.0, 0.3);
    lineBres(105,5,105,20);
    lineBres(105,20,147,20);
    lineBres(147,5,147,20);
    lineBres(105,5,147,5);
    lineBres(105,20,126,25);
    lineBres(126,25,147,20);
    //star
    glColor3f(1.0,1.0,0.0);
    lineBres(105,100,147,100);
    lineBres(126,76,126,124);
    lineBres(147,124,105,76);
    lineBres(105,124,147,76);
    lineBres(137,76,116,124);
    lineBres(137,124,116,76);
    lineBres(147,88,105,112);
    lineBres(147,112,105,88);
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Houses");
    init();
    glutDisplayFunc (drawScene);
    glutMainLoop();
}
