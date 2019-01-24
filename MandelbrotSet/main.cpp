//
//  main.cpp
//  MandelbrotSet
//
//  Created by Andie Goode on 9/3/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,400.0,0.0,300.0);
}

void setPixel(float x, float y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    
    if(y==0){
        glFlush();
    }
}

void fractal(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    int i,j,count;
    float x_real;
    float x_imag;
    float z_real;
    float z_imag;
    float Re_max = 2.0;
    float Re_min = -2.5;
    float Im_min = -2.0;
    int N = 64;
    float delta = (Re_max-Re_min)/glutGet(GLUT_WINDOW_WIDTH);
    for(i=0, z_real = Re_min;i<glutGet(GLUT_WINDOW_WIDTH);i++,z_real += delta){
        for(j=0, z_imag = Im_min; j < glutGet(GLUT_WINDOW_HEIGHT); j++,z_imag += delta){
            count = 0;
            x_real = 0;
            x_imag = 0;
            
             while (((pow(x_real,2.0)+pow(x_imag,2.0))<=4.0f) && count<N){
                 float tempx = x_real;
                 x_real =(pow(x_real,2.0)-pow(x_imag,2.0)) + z_real;
                 
                 x_imag = 2*tempx*x_imag + z_imag;
                 
                 count++;
                }
            
            if((pow(x_real,2.0) + pow(x_imag,2.0))<=4.0){
                
                glColor3f(0.0, 0.0, 0.0);
                
            }
            else{
                float color =(1.0f + 254.0f * (float)count/(float)N)/255.0f;
                glColor3f(color,color,color);
            }
            
            setPixel(i,j);
            }
        }
    
    }

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("Fractal");
    init();
    glutDisplayFunc(fractal);
    glutMainLoop();
}
