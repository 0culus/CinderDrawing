//
//  Vertex.cpp
//  CinderDrawing
//
//  Created by Sean Turner on 5/30/14.
//
//

#include "Vertex.h"
#include "Cinder/gl/gl.h"

using namespace ci;

void Vertex::draw() {
    gl::drawSolidCircle(mPosition, mRadius);
}