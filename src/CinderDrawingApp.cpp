#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Circle.h"

using namespace ci;
using namespace ci::app;


//! this code is based on code from Cameron, @cdacamar on GitHub
class CinderDrawingApp : public AppNative {
    std::vector<Vec2f> points;
public:
    void mouseDrag(MouseEvent e);
    void mouseDown(MouseEvent e);
    void mouseUp(MouseEvent e);
    void update() { }
    void draw();
};

//! draw the line
void CinderDrawingApp::draw() {
    gl::clear(Color::black(), true);
    gl::color(Color(255, 255, 255));
    gl::begin(GL_LINE_STRIP);
    for (const auto& pt : points)
        gl::vertex(pt);
    gl::end();
}

//! Add position data to the vector as the mouse drags
void CinderDrawingApp::mouseDrag(MouseEvent e) {
    points.push_back(e.getPos());
}

//! Draw a Vertex on left mouse click. Not working :(
void CinderDrawingApp::mouseDown(MouseEvent e) {
    if (e.isLeft()) {
        Circle v(e.getPos());
        v.draw();
    }
    mouseDrag(e); // allows a connected line
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )