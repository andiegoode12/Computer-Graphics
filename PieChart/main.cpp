//
//  main.cpp
//  PieChart
//
//  Created by Andie Goode on 10/3/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <fstream>

using namespace std;

GLsizei winWidth = 900, winHeight = 800;// Initial display window size.
const GLdouble twoPi = 6.283185; //2PI


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

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

//draw circle segments
void circleSegment (GLint xc, GLint yc, GLint radius, GLfloat previousAngle, GLfloat angle)
{
    float x, y;
    for (double i=previousAngle; i<=angle; i+=0.0001){
        x = xc + ((radius) * cos (i));
        y = yc + ((radius) * sin (i));
        glVertex2f(x,y);
    }
}

void setPixel (GLint xCoord, GLint yCoord)
{
    glBegin (GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd ( );
    
}


void renderBitmapString(float x, float y, void *font, string w){
    glRasterPos2f (x, y);
    for (int k = 0; k < w.length(); k++){
        glutBitmapCharacter (GLUT_BITMAP_8_BY_13, w [k]);
        
    }
}

void pieChart (void)
{
    screenPt circCtr, piePt;
    GLint radius = winWidth / 4;
    // Circle radius.
    GLdouble sliceAngle, previousSliceAngle = 0.0;
    
    //read in nSlices and dataValues from file
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
        int nSlices;
        int value;
        
        //create array for data
        getline(inFile, temp);
        nSlices = stoi(temp);
        GLfloat dataValues[nSlices];
        //create array for data descriptors
        string dataNames[nSlices];
        //adding values to arrays
        for(int i = 0; i < nSlices; i++){
            getline(inFile, line);
            int temp = line.find(" ");
            value = stoi(line.substr(0,temp));
            name = line.substr(temp+1,sizeof(line)-1);
            dataValues[i] = value;
            dataNames[i] = name;
        }
        float R = 1.0;
        float G = 1.0;
        float B = 1.0;
        GLfloat dataSum = 0.0;
        GLint circCtr_x = winWidth / 2;                  // Circle center position.
        GLint circCtr_y = winHeight / 2;
        GLint piePt_x, piePt_y,pieWord_x, pieWord_y;
        float x, y;
        
        for (int k = 0; k < nSlices; k++)
            dataSum += dataValues[k];
        
        for (int k = 0; k < nSlices; k++) {
            sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
            piePt_x = circCtr_x + radius * cos (sliceAngle);
            piePt_y = circCtr_y + radius * sin (sliceAngle);
            
            //set color
            R = (rand() / double(RAND_MAX))*0.9;
            G = (rand() / double(RAND_MAX))*0.8;
            B = (rand() / double(RAND_MAX))*0.7;
            glColor3f (R, G, B);
            
            glBegin (GL_POLYGON);
            //plot center of circle
            glVertex2i (circCtr_x, circCtr_y);
            //plot first point on curve
            glVertex2i (piePt_x, piePt_y);
            //plot curve
            circleSegment(circCtr_x, circCtr_y, radius, previousSliceAngle, sliceAngle);
            glEnd ( );
  
            //draw corresponding text
            int radius_words = radius*1.3;
            pieWord_x = (circCtr_x- 15)+ radius_words * cos (sliceAngle-0.25);
            pieWord_y = circCtr_y + radius_words * sin (sliceAngle-0.25);
            
            string word = dataNames[k];
            renderBitmapString(pieWord_x, pieWord_y, GLUT_BITMAP_8_BY_13, word);
            
            previousSliceAngle = sliceAngle;
        }
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (double angle=0; angle<=2*3.14159; angle+=0.001){
            x = circCtr_x + ((radius) * cos (angle));
            y = circCtr_y + ((radius) * sin (angle));
            glVertex2f(x,y);
        }
        glEnd();
    }
}


void glutBitmapCharacter(void *font, int character);

void displayFcn (void){
    glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
    //glColor3f (0.0, 0.0, 1.0);       //  Set circle color to blue.
    pieChart ( );
    glFlush ( );
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

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Pie Chart");
    init();
    glutDisplayFunc (displayFcn);
    glutReshapeFunc (winReshapeFcn);
    glutMainLoop();
}
