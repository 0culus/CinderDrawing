#pragma once
//
//  Point.h
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

class Vertex {
public:
    Vertex(ci::Vec2f pos, ci::Color color, float radius, float scale);
    
    ci::Vec2f   mPosition;
    ci::Color   mColor;
    
    float       mRadius;
    float       mScale;
};