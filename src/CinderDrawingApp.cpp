#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderDrawingApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void CinderDrawingApp::setup()
{
}

void CinderDrawingApp::mouseDown( MouseEvent event )
{
}

void CinderDrawingApp::update()
{
}

void CinderDrawingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( CinderDrawingApp, RendererGl )
