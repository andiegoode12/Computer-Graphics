//
//  main.cpp
//  Sutherland-Hodgman Clipping
//
//  Created by Andie Goode on 11/15/17.
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
    wcPt2D () {
        x = 0.0;
        y = 0.0;
    }
    wcPt2D (GLfloat x, GLfloat y) {
        this->x = x;
        this->y = y;
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

typedef enum { Left, Right, Bottom, Top } Boundary;

const GLint nClip = 4;

GLint inside (wcPt2D p, Boundary b, wcPt2D wMin, wcPt2D wMax){
    switch (b) {
        case Left:   if (p.x < wMin.x) return (false); break;
        case Right:  if (p.x > wMax.x) return (false); break;
        case Bottom: if (p.y < wMin.y) return (false); break;
        case Top:    if (p.y > wMax.y) return (false); break;
    }
    return (true);
}

GLint cross (wcPt2D p1, wcPt2D p2, Boundary winEdge, wcPt2D wMin, wcPt2D wMax){
    if (inside (p1, winEdge, wMin, wMax) == inside (p2, winEdge, wMin, wMax))
        return (false);
    else
        return (true);
}

wcPt2D intersect (wcPt2D p1, wcPt2D p2, Boundary winEdge, wcPt2D wMin, wcPt2D wMax){
    wcPt2D iPt;
    GLfloat m;
    if (p1.x != p2.x) m = (p1.y - p2.y) / (p1.x - p2.x);
    switch (winEdge) {
        case Left:
            iPt.x = wMin.x;
            iPt.y = p2.y + (wMin.x - p2.x) * m;
            break;
        case Right:
            iPt.x = wMax.x;
            iPt.y = p2.y + (wMax.x - p2.x) * m;
            break;
        case Bottom:
            iPt.y = wMin.y;
            if (p1.x != p2.x) iPt.x = p2.x + (wMin.y - p2.y) / m;
            else iPt.x = p2.x;
            break;
        case Top:
            iPt.y = wMax.y;
            if (p1.x != p2.x) iPt.x = p2.x + (wMax.y - p2.y) / m;
            else iPt.x = p2.x;
            break;
    }
    return (iPt);
}

void clipPoint (wcPt2D p, Boundary winEdge, wcPt2D wMin, wcPt2D wMax, wcPt2D * pOut, int * cnt, wcPt2D * first[], wcPt2D * s){
    
    wcPt2D iPt;
    
    /* If no previous point exists for this clipping boundary,
     * save this point.
     */
    if (!first[winEdge])
        first[winEdge] = &p;
    /*  Previous point exists.  If p and previous point cross
     *  this clipping boundary, find intersection.  Clip against
     *  next boundary, if any.  If no more clip boundaries, add
     *  intersection to output list.
     */
    else if (cross (p, s[winEdge], winEdge, wMin, wMax)) {
            iPt = intersect (p, s[winEdge], winEdge, wMin, wMax);
            if (winEdge < Top)
                clipPoint (iPt, (Boundary)(int)(winEdge+1), wMin, wMax, pOut, cnt, first, s);
            else {
                pOut[*cnt] = iPt;
                (*cnt)++;
            }
        }
    /*  Save p as most recent point for this clip boundary.  */
    s[winEdge] = p;
    /*  For all, if point inside, proceed to next boundary, if any.  */
    if (inside (p, winEdge, wMin, wMax))
        if (winEdge < Top)
            clipPoint (p, (Boundary)(int)(winEdge + 1), wMin, wMax, pOut, cnt, first, s);
        else {
            pOut[*cnt] = p;  (*cnt)++;
        }
}

void closeClip (wcPt2D wMin, wcPt2D wMax, wcPt2D * pOut, GLint * cnt, wcPt2D * first [ ], wcPt2D * s){
    wcPt2D pt;
    Boundary winEdge;
    //iterating through enum??? winEdge++
    for (winEdge = Left; winEdge <= Top; winEdge = (Boundary)((int)winEdge+1)){
        if (cross (s[winEdge], *first[winEdge], winEdge, wMin, wMax)) {
            pt = intersect (s[winEdge], *first[winEdge], winEdge, wMin, wMax);
            if (winEdge < Top)
                clipPoint (pt, (Boundary)(int)(winEdge + 1), wMin, wMax, pOut, cnt, first, s);
            else {
                pOut[*cnt] = pt;  (*cnt)++;
            }
        }
    }
}
    
GLint polygonClipSuthHodg (wcPt2D wMin, wcPt2D wMax, GLint n, wcPt2D * pIn, wcPt2D * pOut){
    /*  Parameter "first" holds pointer to first point processed for
        *  a boundary; "s" holds most recent point processed for boundary.
        */
    wcPt2D * first[nClip] = { 0, 0, 0, 0 }, s[nClip];
    GLint k, cnt = 0;
    for (k = 0; k < n; k++)
        clipPoint (pIn[k], Left, wMin, wMax, pOut, &cnt, first, s);
    closeClip (wMin, wMax, pOut, &cnt, first, s);
    return (cnt);
}

void displayFcn(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    wcPt2D in [10] = {{35,55}, {0,10}, {55,35}, {110,10}, {75,55}, {110,75}, {75,75}, {55,110}, {35,75}, {0,75}};
    wcPt2D window [2] = {{35, 10}, {75, 110}};
    wcPt2D out [50];
    
    GLint count =  polygonClipSuthHodg (window[0], window[1], 10, in, out);
    glBegin(GL_POLYGON);
    for(int i = 0; i<count; i++){
        glVertex2f(out[i].x, out[i].y);
    }
    
    glEnd();
    glFlush();
}

int main (int argc, char ** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Sutherland-Hodgman");
    init ( );
    glutDisplayFunc (displayFcn);
    glutMainLoop ( );
}
