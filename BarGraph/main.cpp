//
//  main.cpp
//  BarGraph
//
//  Created by Andie Goode on 10/4/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <fstream>

using namespace std;

GLsizei winWidth = 900;
GLsizei winHeight = 600;    // Initial display window size.

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void renderBitmapString(float x, float y, void *font, string w){
    glRasterPos2f (x, y);
    for (int k = 0; k < w.length(); k++){
        glutBitmapCharacter (GLUT_BITMAP_8_BY_13, w [k]);
        
    }
}

void barChart (void)
{
    GLint names, values, k;
    glClear (GL_COLOR_BUFFER_BIT); //  Clear display window.
    glColor3f (0.0, 0.0, 1.0);     //  Set bar color to blue.
    
    //read in nBars and dataValues from file
    ifstream inFile;
    inFile.open("data.txt");
    
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1); // terminate with error
    }
    while(!inFile.eof()){
        string line;
        string temp;
        string name;
        int nBars, x;
        int value;
        
        //create array for data
        getline(inFile, temp);
        nBars = stoi(temp);
        GLfloat dataValues[nBars];
        //create array for data descriptors
        string dataNames[nBars];
        //adding values to arrays
        for(int i = 0; i < nBars; i++){
            getline(inFile, line);
            int temp = line.find(" ");
            value = stoi(line.substr(0,temp));
            name = line.substr(temp+1,sizeof(line)-1);
            dataValues[i] = value;
            dataNames[i] = name;
        }
    
        //draw bars
        for (int k = 0; k < nBars; k++)
            glRecti (40 + k*80, 100, 80 + k*80, 100+dataValues[k]*2);
        //draw text
        glColor3f (0.0, 0.0, 0.0); // Set text color to black.
        for (names = 0; names < nBars; names++) {
            for (k = 0; k < nBars; k++){
                x = 40 + k*80;
                string word = dataNames[k];
                renderBitmapString(x, 80, GLUT_BITMAP_HELVETICA_10, word);
            }
            x += 80;
        }
        glFlush ( );
    }
}
    
void glutBitmapCharacter(void *font, int character);
    
void winReshapeFcn (GLint newWidth, GLint newHeight){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
    glClear (GL_COLOR_BUFFER_BIT);
}
    
int main (int argc, char** argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Bar Graph");
    init ( );
    glutDisplayFunc (barChart);
    glutReshapeFunc (winReshapeFcn);
    glutMainLoop ( );
}
