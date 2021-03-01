#include "ofApp.h"

//--------------------------------------------------------------
// Initial setup at the start of the app
void ofApp::setup() 
{
	ofSetLogLevel(OF_LOG_VERBOSE);  // ofLog provides an interface for writing text output from your app. It's basically a more useful version of cout or printf where output can be filtered and written to the console or to a file.

	ofBackground(50, 50, 0, 0);  // Sets the background color.


	ofDisableArbTex(); // we use GL_TEXTURE_2D for our models coords so we have to normalise the texture coordinates. By default openFrameworks uses rectangular textures instead of 2D textures 

	bAnimate = false;     // at the start no animation is played

	bAnimateMouse = false;

	animationPosition = 0;

	model.loadModel("astroBoy_walk.dae", false);  // load the initial model
	model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.85, 0);  // set intial position of the model
	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);  // animations will be played in a loop
	model.playAllAnimations();
	if (!bAnimate) 
	{
		model.setPausedForAllAnimations(true);
	}

	bHelpText = true;

}

//--------------------------------------------------------------
void ofApp::update()
{
	model.update();

	if (bAnimateMouse)
	{
		model.setPositionForAllAnimations(animationPosition);
	}

	mesh = model.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	ofSetColor(255);

	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // Sets and enables the blend mode for drawing

	ofEnableDepthTest();   // Turns on depth testing so rendering happens according to z-depth rather than draw order.

#ifndef TARGET_PROGRAMMABLE_GL
	glShadeModel(GL_SMOOTH); // Smooth shading, the default, causes the computed colors of vertices to be interpolated as the primitive is rasterized, typically assigning different colors to each resulting pixel fragment
#endif

	light.enable();  // enable lighting in the scene
	ofEnableSeparateSpecularLight();   // we use specular light in the scene

	ofPushMatrix(); // ofPushMatrix saves the current coordinate system allowing us to play the animations.

	ofTranslate(model.getPosition().x + 100, model.getPosition().y, 0); // ofTranslate produces a translation by (x,y,z) vector of our coordinate system. The call of ofTranslate modifies graphics positions. Use ofPushMatrix and ofPopMatrix to save and restore the untranslated coordinate system.

	ofRotateDeg(-mouseX, 0, 1, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);

	model.drawFaces();  // This draws the mesh as faces

	ofPopMatrix();  //  restores the prior coordinate system of the object.

#ifndef TARGET_PROGRAMMABLE_GL
	glEnable(GL_NORMALIZE);
#endif
	ofPushMatrix();
	ofTranslate(model.getPosition().x - 300, model.getPosition().y, 0);
	ofRotateDeg(-mouseX, 0, 1, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);

	ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);

	ofMultMatrix(model.getModelMatrix());
	ofMultMatrix(meshHelper.matrix);

	ofMaterial & material = meshHelper.material; //used in determining both the intensity and color of reflected light based on the lighting model in use and if the vertices are on a front or back sided face

	if (meshHelper.hasTexture()) 
	{
		meshHelper.getTextureRef().bind();
	}
	material.begin();
	mesh.drawWireframe();
	material.end();
	if (meshHelper.hasTexture()) 
	{
		meshHelper.getTextureRef().unbind();
	}
	ofPopMatrix();

	ofDisableDepthTest();
	light.disable();
	ofDisableLighting();
	ofDisableSeparateSpecularLight();

	// Displays helpful text regarding the scene
	if (bHelpText) 
	{
		ofSetColor(0, 0, 0);
		stringstream ss;
		ss << "FPS: " << ofToString(ofGetFrameRate(), 0) << endl << endl;
		ss << "(keys 1-4): load and display the 4 models" << endl;
		ss << "num of animations in this model: " + ofToString(model.getAnimationCount());
		ss << endl << "(Spacebar): toggle animation" << endl;
		ss << "(LEFT MOUSE BUTTON DRAG in y-axis): control animation." << endl;
		ofDrawBitmapString(ss.str().c_str(), 25, 15);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.85, 0);
	switch (key) 
	{
	case '1':
		model.loadModel("astroBoy_walk.dae");
		model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
		ofEnableSeparateSpecularLight();
		break;
	case '2':
		model.loadModel("TurbochiFromXSI.dae");
		model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
		ofEnableSeparateSpecularLight();
		break;
	case '3':
		model.loadModel("dwarf.x");
		model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
		ofDisableSeparateSpecularLight();
		break;
	case '4':
		model.loadModel("monster-animated-character-X.X");
		model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
		model.setRotation(0, -90, 0, 0, 1);
		ofDisableSeparateSpecularLight();
		break;
	case ' ':
		bAnimate = !bAnimate;
		break;
	default:
		break;
	}

	mesh = model.getMesh(0);

	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model.playAllAnimations();
	if (!bAnimate) 
	{
		model.setPausedForAllAnimations(true);
	}
}

void ofApp::keyReleased(int key)
{

}

void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{
	// move through animations manually
	animationPosition = y / (float)ofGetHeight();
}

void ofApp::mousePressed(int x, int y, int button)
{
	// pause all animations so they can be played manually
	model.setPausedForAllAnimations(true);
	animationPosition = y / (float)ofGetHeight();
	bAnimateMouse = true;
}

void ofApp::mouseReleased(int x, int y, int button)
{
	// unpause animations when done going through them with the mouse
	if (bAnimate)
	{
		model.setPausedForAllAnimations(false);
	}
	bAnimateMouse = false;
}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{

}

void ofApp::receiveMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
