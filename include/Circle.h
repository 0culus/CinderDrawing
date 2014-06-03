#pragma once
//
//  Circle.h
//  CinderDrawing
//
//  Created by Sean Turner on 5/30/14.
//
//

#ifndef __CinderDrawing__Point__
#define __CinderDrawing__Point__

#include <iostream>

#endif /* defined(__CinderDrawing__Point__) */

#include "cinder/gl/gl.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"

class Circle {
public:
    Circle(ci::Vec2i pos, ci::Color color, float radius) {}
    Circle(ci::Vec2i pos) : Circle(pos, ci::Color(255, 255, 255), 3.0f) {}
    void    draw();
    //void    remove(Vertex v);
    
    ci::Vec2i   mPosition;
    ci::Color   mColor;
    
    float       mRadius;
    float       mScale;
};