#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;


//! this code is from Cameron, @cdacamar on GitHub
class CinderDrawingApp : public AppNative {
    std::vector<Vec2f> points;
public:
    void mouseDrag(MouseEvent e) { points.push_back(e.getPos()); }
    void update() { }
    void draw();
};

void CinderDrawingApp::draw() {
    gl::clear(Color::black(), true);
    gl::color(Color(255, 255, 255));
    gl::begin(GL_LINE_STRIP);
    for (const auto& pt : points)
        gl::vertex(pt);
    gl::end();
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )