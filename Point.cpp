/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point.cpp
 * Author: torc
 * 
 * Created on March 17, 2017, 11:19 AM
 */

#include "Point.h"
#include <iostream>
#include <cstdlib>

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}

Point::Point(string strPoint){
    size_t posY = strPoint.find("Y");
    size_t posX = strPoint.find("X");
    size_t strSize = strPoint.size();    
    //X12Y123
    this->x = atof(strPoint.substr(posX+1, posY-1).c_str());
    this->y = atof(strPoint.substr(posY+1, strSize-1).c_str());

    size_t posUnd = strPoint.find("_");
    this->type = strPoint.substr(0, posUnd).c_str();
    
}

double Point::euclideanDistance(double x2, double y2) {
    double x = this->x - x2;
    double y = this->y - y2;
    double dist;

    dist = pow(x, 2) + pow(y, 2);
    dist = sqrt(dist);

    return dist;
}

