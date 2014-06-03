//
//  Circle.cpp
//  CinderDrawing
//
//  Created by Sean Turner on 5/30/14.
//
//

#include "Circle.h"
#include "Cinder/gl/gl.h"

using namespace ci;

void Circle::draw() {
    gl::drawSolidCircle(mPosition, mRadius);
}