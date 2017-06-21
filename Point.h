/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point.h
 * Author: torc
 *
 * Created on March 17, 2017, 11:19 AM
 */

#ifndef POINT_H
#define POINT_H

#include <string>
#include <math.h>
#include <iostream>

using namespace std;

class Point {
    
 private:
    double x;
    double y;
    string type;
    
public:
    Point();
    Point(double x = 0.0, double y = 0.0);
    Point(string strPoint);
    double euclideanDistance(double x1, double y1);
    double getX() {return this->x;}
    double getY() {return this->y;}
    void setX(double x){this->x = x;}
    void setY(double y){this->y = y;} 
    string getType() {return this->type;}
    void printPoint(){cout << "(" << this->x << "," << this->y << ")" << endl;}

};

#endif /* POINT_H */

