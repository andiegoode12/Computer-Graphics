//
//  main.cpp
//  Bouncing Ball
//
//  Created by Andie Goode on 11/27/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdlib.h>
#include "lodepng.h"

const double TWO_PI = 6.2831853;
GLsizei winWidth = 500, winHeight = 500; // Initial display window size.
GLuint regShape; // Define name for display list.
static GLfloat rotTheta = 0.0;
GLint radius = 50;
GLint x = -150;
GLint y = 200;
std::vector<unsigned char> image;
std::vector<unsigned char> image2;
class scrPt {
public:
    GLint x, y;
};

void rotateShape (void)
{
    if(x != 0)
        rotTheta += log(1000.0f/(x+152.0f));
    if (rotTheta > 360.0)
        rotTheta -= 360.0;
    glutPostRedisplay ( );
}

static void init (void)
{
    //ARSUUU
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, "arsuuu.png");
    if(error != 0)
    {
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    
    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1; while(u2 < width) u2 *= 2;
    size_t v2 = 1; while(v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double)width / u2;
    double v3 = (double)height / v2;
    
    // Make power of two version of the image.
    image2.resize(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++)
        for(size_t x = 0; x < width; x++)
            for(size_t c = 0; c < 4; c++)
            {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
    
    scrPt shapeVertex;
    GLdouble shapeTheta;
    GLint k;
    glClearColor (1.0, 1.0, 1.0, 0.0);
    /* Set up a display list for a red regular hexagon.
     * Vertices for the hexagon are six equally spaced
     * points around the circumference of a circle.
     */
    regShape = glGenLists (1);
    glNewList (regShape, GL_COMPILE);
    glColor3f (1.0, 1.0, 1.0);
    glBegin (GL_POLYGON);
    for (double angle=0; angle<=TWO_PI; angle+=0.01){
        shapeVertex.x = ((radius) * cos (angle));
        shapeVertex.y = ((radius) * sin (angle));
        glTexCoord2d((cos(angle)+1)/2,(-sin(angle)+1)/2);
        glVertex2f(shapeVertex.x,shapeVertex.y);
    }
    glEnd ( );
    
//    glColor3f (0.0, 1.0, 0.0);
//    glBegin(GL_TRIANGLES);
//    for (k = 0; k < 3; k++) {
//        shapeTheta = TWO_PI * k / 3;
//        shapeVertex.x = radius * cos (shapeTheta);
//        shapeVertex.y = radius * sin (shapeTheta);
//        glVertex2i (shapeVertex.x, shapeVertex.y);
//    }
    
    glEndList ( );
    glutIdleFunc(rotateShape);
}
void displayShape (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    x = x + 1;
    y = -400 + 600 * abs(sin((6.26 * x) + TWO_PI))*pow(2.71828,-(0.005) * x);
    glPushMatrix ( );
    glTranslatef(x-150, y+200, 0.0);
    //glTranslatef(-25.0, -25.0, 0.0);
    glRotatef (-(rotTheta), 0.0, 0.0, 1.0);
    //glTranslatef(25.0, 25.0, 0.0);
    
    glCallList (regShape);
    glPopMatrix ( );
        glutSwapBuffers ( );
    glFlush ( );
}


void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (-320.0, 320.0, -320.0, 320.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ( );
    glClear (GL_COLOR_BUFFER_BIT);
}

void mouseFcn (GLint button, GLint action, GLint x, GLint y)
{
    switch (button) {
        case GLUT_MIDDLE_BUTTON: // Start the rotation.
            if (action == GLUT_DOWN)
                glutIdleFunc (rotateShape);
            break;
        case GLUT_RIGHT_BUTTON: // Stop the rotation.
            if (action == GLUT_DOWN)
                glutIdleFunc (NULL);
            break;
        default:
            break;
    }
}
void MyKeyboardFunc(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 'x': glutIdleFunc (rotateShape); break;
        case 'c': glutIdleFunc (NULL); break;
    };
}
int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (150, 150);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Bouncy Boi");
    init ( );
    glutDisplayFunc (displayShape);
    glutReshapeFunc (winReshapeFcn);
    //glutIdleFunc (rotateShape);
    glutMouseFunc (mouseFcn);
    glutKeyboardFunc(MyKeyboardFunc);
    glutMainLoop ( );
}
