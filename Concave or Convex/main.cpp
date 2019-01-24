//
//  main.cpp
//  Concave or Convex
//
//  Created by Andie Goode on 9/20/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <fstream>
using namespace std;

class vector3d {
public:
    int x,y,z;
    
    vector3d(){
        int x=0;
        int y=0;
        int z=0;
    }
    
    vector3d(int x, int y, int z){
        this -> x = x;
        this -> y = y;
        this -> z = z;
    }
    
};

vector3d subtract(vector3d i, vector3d j){
    vector3d edge;
    //calculate edge vertex
    edge.x = i.x - j.x;
    edge.y = i.y - j.y;
    edge.z = i.z - j.z;
    return edge;
}

vector3d cross(vector3d v1, vector3d v2){
    vector3d result(0,0,0);
    result.z = (v1.x*v2.y) - (v2.x*v1.y);
    return result;
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}
bool isConcave(vector3d x_products[], int length){
    bool isConcave = false;
    int x = 0;
    for(int i = 0; i < length; i++){
        if(x_products[i].z < 0)
            x--;
        if(!isConcave)
            x++;
    }
    if (x%length != 0){
        isConcave = true;
        cout << "*************" << endl;
        cout << "Concave" << endl;
    }
    else{
        cout << "*************" << endl;
        cout << "Convex" << endl;
    }
    return isConcave;
}

void drawPolygon(bool isConcave, vector3d vertices[], int length){
    if(isConcave){
        glColor3f(1.0, 0.0, 0.0);
    }
    else{
        glColor3f(0.0, 0.0, 1.0);
    }
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < length; i++){
        int points[2] = {vertices[i].x, vertices[i].y};
        glVertex2iv(points);
    }
    glEnd();
}

void Polygon(void)
{
    ifstream inFile;
    inFile.open("test.txt");
    
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1); // terminate with error
    }
    
    while(!inFile.eof()){
        string line;
        string temp;
        int length;
        int x,y;
        //create array of vertices with length elements
        getline(inFile, temp);
        length = stoi(temp);
        vector3d vertices[length];
        //read points into array of vertices
        for(int i = 0; i < length; i++){
            getline(inFile, line);
            int temp = line.find(",");
            x = stoi(line.substr(0, temp));
            y = stoi(line.substr(temp+1,sizeof(line)-1));
            vertices[i] = vector3d(x,y,0);
        }
        //subtract vertices to find edge vectors
        vector3d edges[length];
        for(int i = 0; i < length; i++){
            if(i==length-1)
                edges[i] = subtract(vertices[0],vertices[i]);
            else
                edges[i] = subtract(vertices[i+1],vertices[i]);
        }
        //calculate cross products of edge vectors
        vector3d x_products[length];
        for(int i = 0; i < length; i++){
            if(i == length - 1)
                x_products[i] = cross(edges[i],edges[0]);
            else
                x_products[i] = cross(edges[i],edges[i+1]);
        }
        drawPolygon(isConcave(x_products, length), vertices, length);
    }
    inFile.close();
    glFlush();
   }


int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Convex and Concave");
    init();
    glutDisplayFunc(Polygon);
    glutMainLoop(); //

}
