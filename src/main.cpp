#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);	// setup the GL context and screen dimensions

	
	ofRunApp(new ofApp());  //Begins the openGL cycle of the application.

}
