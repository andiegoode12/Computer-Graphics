//
//  main.cpp
//  RedFlag!
//
//  Created by Andie Goode on 9/26/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

/*  Set initial display-window size. */
GLsizei winWidth = 400, winHeight = 300;
/*  Set range for world coordinates.  */
GLfloat xwcMin = 0.0, xwcMax = 400.0;
GLfloat ywcMin = 0.0, ywcMax = 300.0;

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void renderBitmapString(float x, float y, void *font,const char *string){
    glRasterPos2f (x, y);
    for (int k = 0; k < strlen(string); k++){
        glutBitmapCharacter (GLUT_BITMAP_9_BY_15, string [k]);
    
    }
}

void drawShapes(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //draw black pole
    glColor3f(0.0,0.0,0.0);
    
    glRecti(30, 250, 60, 0);
   
    //draw gold circle
	glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    float x, y;
    float radius = 15.0;
    float centerx = 45;
    float centery = 260;
    for(float radius_yellow=radius;radius_yellow>=0;radius_yellow--){
        for (double angle=0; angle<=2*3.14159; angle+=0.01){
            x = centerx + ((radius_yellow) * cos (angle));
            y = centery + ((radius_yellow) * sin (angle));
            glVertex2f(x,y);
        }
    }
    glEnd();
    
    //draw flag
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(75,200);
    glVertex2i(75, 150);
    glVertex2i(150, 150);
    glVertex2i(175, 200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(75, 215);
    glVertex2i(125, 215);
    glVertex2i(75, 170);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(150, 190);
    glVertex2i(100,135);
    glVertex2i(175, 135);
    glEnd();
    
    //draw strings
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(60, 215);
    glVertex2i(75, 215);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(60, 150);
    glVertex2i(75, 150);
    glEnd();
    
    //text
    renderBitmapString(150, 100, GLUT_BITMAP_8_BY_13, "Red Flag!");
    
    glFlush();
    }

//from textbook
void glutBitmapCharacter(void *font, int character);

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);
    glClear (GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("RedFlag!");
    init();
    glutDisplayFunc(drawShapes);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();

}
