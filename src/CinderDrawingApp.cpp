#include "cinder/app/AppNative.h"
#include "cinder/app/AppBasic.h" // allows us to specify window dimensions and framerate
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
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
	void update();
    void draw();

	gl::GlslProgRef	mShader;
	float mAngle;
};

//! compile the shaders and setup any other resources
void CinderDrawingApp::setup() {
	try {
		mShader = gl::GlslProg::create(loadResource(RES_PASSTHRU_VERT), loadResource(RES_BLUR_FRAG));
	}
	catch (gl::GlslProgCompileExc &exc) {
		std::cout << "Shader compile error: " << std::endl;
		std::cout << exc.what() << std::endl;
	}
	catch (Exception &exc) {
		std::cout << "Unable to load shader" << std::endl;
		std::cout << exc.what() << std::endl;
	}
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

void CinderDrawingApp::update() {
	mAngle += 0.05f;
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

	// this is quick n dirty. Might not be the cleanest way to exit though. 
	else if (e.getCode() == app::KeyEvent::KEY_ESCAPE) {
		exit(0);
	}
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )
