#include "cinder/app/AppNative.h"
#include "cinder/app/AppBasic.h" // allows us to specify window dimensions and framerate
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

#include "Circle.h"
#include <vector>

using namespace ci;
using namespace ci::app;


//! this code is based on code from Cameron, @cdacamar on GitHub
class CinderDrawingApp : public AppNative {
    std::vector<Vec2f> points;
public:
	void setup();
	void prepareSettings(Settings *settings);
    void mouseDrag(MouseEvent e);
    void mouseDown(MouseEvent e);
	void keyDown(KeyEvent e);
    void update() { }
    void draw();

	gl::GlslProgRef	mShader;
};

void CinderDrawingApp::setup() {

}

//! setup the window
void CinderDrawingApp::prepareSettings(Settings *settings) {
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60.0f);
}

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

//! toggle fullscreen with f
void CinderDrawingApp::keyDown(KeyEvent e) {
	if (e.getCode() == app::KeyEvent::KEY_f) {
		setFullScreen(!isFullScreen());
	}
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )