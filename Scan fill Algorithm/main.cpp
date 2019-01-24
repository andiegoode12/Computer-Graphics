//
//  main.cpp
//  Scan fill Algorithm
//
//  Created by Andie Goode on 10/23/17.
//  Copyright © 2017 Andie Goode. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <vector>


GLsizei winWidth = 500, winHeight=500;

struct Edge{
public:
    double x0;
    int y0;
    int xEnd;
    int yEnd;
    int dx;
    int dy;
    int yMin;
    int yMax;
    int active;
    double m;
    double inverseSlope;
    
    Edge(int x1, int y1, int x2, int y2){
        x0 = x1;
        y0 = y1;
        xEnd = x2;
        yEnd = y2;
        active = 0; //???
        dx = fabs(xEnd - x0);
        dy = fabs(yEnd - y0);
        m = float(yEnd - y0)/float(xEnd - x0);
        inverseSlope = double(1/m);
    }
    
};

//swapPoint
//
//sort
//
//sortEdge
std::vector<Edge> sortEdge(std::vector<Edge> a){
    for(int i=0; i < a.size()-1; i++){
        for (int j = 0; j < a.size()-i-1; j++){
            if (a.at(j).y0>a.at(j+1).y0){
                Edge temp = a.at(j+1);
                a.at(j+1) =a.at(j);
                a.at(j) = temp;
            }
            else if(a.at(j).y0 == a.at(j+1).y0){
                if (a.at(j).x0>a.at(j+1).x0){
                    Edge temp = a.at(j+1);
                    a.at(j+1) =a.at(j);
                    a.at(j) = temp;
                }
                else if(a.at(j).x0 == a.at(j+1).x0){
                    if(a.at(j).xEnd>a.at(j+1).xEnd){
                        Edge temp = a.at(j+1);
                        a.at(j+1) =a.at(j);
                        a.at(j) = temp;
                    }
                }
            }
        }
    }
    return a;
}


void init (void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 500.0, 0.0, 500.0);
}

void setPixel (GLint xCoord, GLint yCoord) {
    glBegin (GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd ( );
}

//Line Breseneham Algorithm
void lineBres (int x0, int y0, int xEnd, int yEnd)
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
    glColor3f(0.0, 0.0, 0.0);
    
    std::vector<Edge> edges;
    std::vector<Edge> edgeList;
    edges.push_back(Edge(50,50,300,50));
    edges.push_back(Edge(50,50,55,200));
    edges.push_back(Edge(55,200,70,180));
    edges.push_back(Edge(70,180,80,250));
    edges.push_back(Edge(80,250,98,150));
    edges.push_back(Edge(98,150,200,120));
    edges.push_back(Edge(200,120, 205,210));
    edges.push_back(Edge(205,210,220,112));
    edges.push_back(Edge(220,112,250,160));
    edges.push_back(Edge(250,160,300,50));
    
    //remove horizontal slopes
    for(int i=0; i<edges.size(); i++){
        if(edges.at(i).m != 0)
            edgeList.push_back(Edge(edges.at(i)));
    }
    
    //order pairs from decrease to increase
    for(int i = 0; i<edgeList.size(); i++){
        if(edgeList.at(i).y0 > edgeList.at(i).yEnd){
            int temp = edgeList.at(i).yEnd;
            edgeList.at(i).yEnd = edgeList.at(i).y0;
            edgeList.at(i).y0 = temp;
            temp = edgeList.at(i).xEnd;
            edgeList.at(i).xEnd = edgeList.at(i).x0;
            edgeList.at(i).x0 = temp;
        }
    }
    //Sort List
    edgeList = sortEdge(edgeList);

    // printing
    for(int i = 0; i<edgeList.size(); i++){
        std::cout << edgeList.at(i).x0;
        std::cout << " ";
        std::cout << edgeList.at(i).y0;
        std::cout << " ";
        std::cout << edgeList.at(i).xEnd;
        std::cout << " ";
        std::cout << edgeList.at(i).yEnd;
        std::cout << " ";
        std::cout << edgeList.at(i).m;
        std::cout << " ";
        std::cout << edgeList.at(i).inverseSlope<<"\n";
    }
    
    //algorithm
    int yMin = edgeList.at(0).y0;
    int yMax = edgeList.at(0).yEnd;
    
    for(int i = 0; i < edgeList.size(); i++){
        if(edgeList.at(i).yEnd> yMax)
            yMax =edgeList.at(i).yEnd;
    }
    
    for(int i = yMin; i < yMax; i++){
        std::vector<int> xbois;
        //find active edges
        for(int j = 0; j < edgeList.size(); j++){
            if( i < edgeList.at(j).yEnd && i >= edgeList.at(j).y0){
                edgeList.at(j).active = 1;
            }
         }
        
        for(int j = 0; j < edgeList.size(); j++){
            if(edgeList.at(j).active == 1){
                xbois.push_back(edgeList.at(j).x0);
                //double inverseSlope = (1/edgeList.at(j).m);
                edgeList.at(j).x0 += edgeList.at(j).inverseSlope;
                edgeList.at(j).active = 0;
            }
        }
        
        sort(xbois.begin(), xbois.end());
        
        for(int k=0; k<xbois.size();k+=2){
            lineBres(xbois.at(k), i, xbois.at(k+1), i);
        }
//        print xbois
//        for(int i=0; i<xbois.size(); i++){
//            std::cout<<xbois.at(i)<<" ";
//        }
    }
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("Scan-Line Fill");
    init();
    glutDisplayFunc (drawScene);
    glutMainLoop();
}
