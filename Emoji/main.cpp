//
//  main.cpp
//  Emoji
//
//  Created by Andie Goode on 9/12/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>


void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,900.0);
}
void Emoji(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    float x, y;
    float radius = 300.0;
    float centerx = 0.5 * glutGet(GLUT_WINDOW_WIDTH);
    float centery = 0.5 * glutGet(GLUT_WINDOW_HEIGHT);
    
    //Yellow filled circle
    for(float radius_yellow=radius;radius_yellow>=0;radius_yellow--){
        for (double angle=0; angle<=2*3.14159; angle+=0.01){
            x = centerx + ((radius_yellow) * cos (angle));
            y = centery + ((radius_yellow) * sin (angle));
            glVertex2f(x,y);
        }
    }
    //Black Border
    glColor3f(0.0,0.0,0.0);
    for (double angle=0; angle<=2*3.14159; angle+=0.001){
        x = centerx + ((radius) * cos (angle));
        y = centery + ((radius) * sin (angle));
        glVertex2f(x,y);
    }
    
    //left eye
    float radius_eye= radius-(0.85*radius);
    float y_eye=centery+(0.3*radius);
    float x_eye=centerx-(0.4*radius);
    for(float i= radius_eye;i>0;i--){
        for(double angle=0; angle<=2*3.14159; angle+=0.001){
            x = x_eye + (i * cos (angle));
            y = y_eye + (i * sin (angle));
            glVertex2f(x,y);
        }
    }
    float y_shine = y_eye+(0.05*radius);
    float x_shine = x_eye - (0.05 *radius);
    glColor3f(1.0,1.0,1.0);
    for(float i= radius_eye-(0.85*radius_eye);i>0;i--){
        for(double angle=0; angle<=2*3.14159; angle+=0.001){
            x = x_shine + (i * cos (angle));
            y = y_shine + (i * sin (angle));
            glVertex2f(x,y);
        }
    }
    //right eye
    glColor3f(0.0,0.0,0.0);
    y_eye=centery+(0.3*radius);
    x_eye=centerx+(0.4*radius);
    for(float i= radius_eye;i>0;i--){
        for(double angle=0; angle<=2*3.14159; angle+=0.001){
            x = x_eye + (i * cos (angle));
            y = y_eye + (i * sin (angle));
            glVertex2f(x,y);
        }
    }
    y_shine = y_eye+(0.05*radius);
    x_shine = x_eye - (0.05 *radius);
    glColor3f(1.0,1.0,1.0);
    for(float i= radius_eye-(0.85*radius_eye);i>0;i--){
        for(double angle=0; angle<=2*3.14159; angle+=0.001){
            x = x_shine + (i * cos (angle));
            y = y_shine + (i * sin (angle));
            glVertex2f(x,y);
        }
    }
    //mouth
    glColor3f(0.0,0.0,0.0);
    float y_mouth = centery - (0.7*radius);
    float x_mouth =centerx;
    for (double angle=0; angle<=3.14159; angle+=0.001){
        x = x_mouth + ((radius-(radius*0.5)) * cos (angle));
        y = y_mouth + ((radius-(radius*0.5)) * sin (angle));
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}
int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,900);
    glutCreateWindow("Emoji");
    init();
    glutDisplayFunc(Emoji);
    glutMainLoop();
}
