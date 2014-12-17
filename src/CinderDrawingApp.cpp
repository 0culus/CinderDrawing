#include "cinder/app/AppNative.h"
#include "cinder/app/AppBasic.h" // allows us to specify window dimensions and framerate
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "Circle.h"
#include "cinder/gl/Fbo.h"
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
	void drawLine();

	gl::GlslProg		mShader;
	gl::Fbo::Format		format;
	gl::Fbo				mFboBlurred;
	gl::Fbo				mFboTemporary;
	bool				shaderOn;
	bool				clearFlag;
	float				mAngle;
	int					height;
	int					width;
};

//! compile the shaders and setup any other resources
void CinderDrawingApp::setup() {
	try {
		mShader = gl::GlslProg(loadResource(RES_PASSTHRU_VERT), loadResource(RES_BLUR_FRAG));
		//mShader = gl::GlslProg(loadResource(RES_BLUR_FRAG));
	}
	catch (gl::GlslProgCompileExc &exc) {
		std::cout << "Shader compile error: " << std::endl;
		std::cout << exc.what() << std::endl;
	}
	catch (Exception &exc) {
		std::cout << "Unable to load shader: " << std::endl;
		std::cout << exc.what() << std::endl;
	}

	gl::Fbo::Format format;
	format.enableMipmapping(false);
	format.setCoverageSamples(16);
	format.setSamples(8);
	try {
		mFboBlurred = gl::Fbo(512, 512, format);
		mFboTemporary = gl::Fbo(512, 512, format);
	}
	catch (gl::FboException &exc) {
		std::cout << "FBO error: " << exc.what() << std::endl;
	}
	catch (gl::FboExceptionInvalidSpecification &exc) {
		std::cout << "FBO error: " << exc.what() << std::endl;
	}
}

//! setup the window
void CinderDrawingApp::prepareSettings(Settings *settings) {
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60.0f);
	shaderOn = false;
}

//! draw scene
//! https://forum.libcinder.org/topic/fbo-gaussian-blur-shader-101
void CinderDrawingApp::draw() {
	if (clearFlag) {
		gl::clear(Color::black());
		clearFlag = false;
	}

	if (shaderOn) {
		Area viewport = gl::getViewport();
		gl::setViewport(mFboBlurred.getBounds());
		mFboBlurred.bindFramebuffer();
		gl::clear(Color::black());

		drawLine();

		mFboBlurred.unbindFramebuffer();
		gl::setViewport(viewport);

		mShader.bind();
		mShader.uniform("tex0", 0); // use mFboBlurred, see lower
		mShader.uniform("sampleOffset", Vec2f(1.5f / 512.0f, 0.0f));

		mFboTemporary.bindFramebuffer();
		gl::clear(Color::black());
		mFboBlurred.bindTexture(0); // use rendered scene as texture
		gl::pushMatrices();
		gl::setMatricesWindow(512, 512, false);
		gl::drawSolidRect(mFboBlurred.getBounds());
		gl::popMatrices();
		mFboBlurred.unbindTexture();
		mFboTemporary.unbindFramebuffer();

		mShader.uniform("sampleOffset", Vec2f(0.0f, 1.5f / 512.0f));

		mFboBlurred.bindFramebuffer();
		gl::clear(Color::black());
		mFboTemporary.bindTexture(0); // use horizontally blurred scene as texture
		gl::pushMatrices();
		gl::setMatricesWindow(512, 512, false);
		gl::drawSolidRect(mFboTemporary.getBounds());
		gl::popMatrices();
		mFboTemporary.unbindTexture();
		mFboBlurred.unbindFramebuffer();

		mShader.unbind();      // don't forget to unbind the blur shader now!

		// draw with additive blending
		gl::enableAdditiveBlending();
		gl::color(Color::white());
		gl::draw(mFboBlurred.getTexture(), getWindowBounds());
		gl::disableAlphaBlending();
	}
	else {
		drawLine();
	}
}

//! draw our mouse line
void CinderDrawingApp::drawLine() {
	//mShader.bind();
	//width = getWindowWidth();
	//height = getWindowHeight();

	gl::clear(Color::black(), true);
	gl::color(Color(255, 255, 255));
	//gl::color(Color(0, 0, 0));

	gl::begin(GL_LINE_STRIP);

	for (const auto& pt : points) {
		gl::vertex(pt);

		if (shaderOn) {
			mShader.uniform("width", pt.y);
			mShader.uniform("height", pt.x);
		}
	}

	gl::end();
	//mShader.unbind();
}


void CinderDrawingApp::update() {
	if (clearFlag) {
		points.clear();
	}

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

//! handle keyboard events
void CinderDrawingApp::keyDown(KeyEvent e) {
	switch (e.getCode()) {
	case KeyEvent::KEY_ESCAPE:
		quit();
		break;
	case KeyEvent::KEY_f:
		setFullScreen(!isFullScreen());
		break;
	case KeyEvent::KEY_s:
		if (shaderOn) {
			shaderOn = false;
			break;
		}
		else {
			shaderOn = true;
			break;
		}
	case KeyEvent::KEY_c:
		clearFlag = true;
		break;
	}
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )
