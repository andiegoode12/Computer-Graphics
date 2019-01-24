//
//  main.cpp
//  2D Transformations
//
//  Created by Andie Goode on 11/1/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>
GLsizei winWidth = 300, winHeight=300;

void init (void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 300.0, 0.0, 300.0);
}

std:: vector<float> translate (std::vector<float> pts, int tx, int ty){
    for(int i = 0; i < pts.size(); i += 2){
        pts.at(i) += tx;
        pts.at(i+1) += ty;
    }
    return pts;
}

std:: vector<float> rotate (std::vector<float> pts, float angle, float xr, float yr){
    std:: vector<float> newpts;
    float temp;
    for(int i = 0; i < pts.size(); i++){
        if((i)%2 == 0){
            temp = xr + ((pts.at(i) - xr) * cos(angle)) - ((pts.at(i+1) - yr) * sin(angle));
            newpts.push_back(temp);
        }
        else{
            temp = yr + ((pts.at(i-1) - xr) * sin(angle)) + ((pts.at(i) - yr) * cos(angle));
            newpts.push_back(temp);
        }
    }
    return newpts;
}

std:: vector<float> scale (std::vector<float> pts, float xf, float yf, float sx, float sy){
    for(int i = 0; i < pts.size(); i += 2){
        pts.at(i) = (pts.at(i) * sx) + (xf * (1 - sx));
        pts.at(i+1) = (pts.at(i+1) * sy) + (yf * (1 - sy)) ;
    }
    return pts;
}

void drawImage(){
    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<float> points= {0.0, 100.0, 50.0, 150.0, 100.0, 100.0, 50.0, 25.0};
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for(int i = 0; i<points.size(); i+=2){
        glVertex2f(points[i], points[i+1]);
    }
    glEnd();
    
    glColor3f(1.0,0.0,0.0);
    //rotate
    float theta = (5 * 3.1415926) / 3;
    points = rotate(points, theta, 50.0, 10.0);
    
//    glBegin(GL_POLYGON);
//    for(int i = 0; i<points.size(); i+=2){
//        glVertex2f(points[i], points[i+1]);
//    }
//    glEnd();
    
    //translate
    points = translate(points, 0, 100);
    
//    glBegin(GL_POLYGON);
//    for(int i = 0; i<points.size(); i+=2){
//        glVertex2f(points[i], points[i+1]);
//    }
//    glEnd();
    
    //scale
    points = scale(points, 200.0, 200.0, 0.5, 0.5);
    
    //draw final image
    glBegin(GL_POLYGON);
    for(int i = 0; i<points.size(); i+=2){
        glVertex2f(points[i], points[i+1]);
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("2D Transformation");
    init();
    glutDisplayFunc (drawImage);
    glutMainLoop();
}
