#include "ofApp.h"

//--------------------------------------------------------------
// Initial setup at the start of the app
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(30, 0);

	ofDisableArbTex(); // we use GL_TEXTURE_2D for our models coords.

	bAnimate = false;     // at the start no animation is played
	bAnimateMouse = false;  
	animationPosition = 0;

	model.loadModel("astroBoy_walk.dae", false);
	model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.85, 0);  // set intial position of the model
	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);  // animations will be played in a loop
	model.playAllAnimations();
	if (!bAnimate) {
		model.setPausedForAllAnimations(true);
	}

	bHelpText = true;

}

//--------------------------------------------------------------
void ofApp::update() {
	model.update();

	if (bAnimateMouse) {
		model.setPositionForAllAnimations(animationPosition);
	}

	mesh = model.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255);

	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // Sets and enables the blend mode for drawing

	ofEnableDepthTest();   // Turns on depth testing so rendering happens according to z-depth rather than draw order.

#ifndef TARGET_PROGRAMMABLE_GL
	glShadeModel(GL_SMOOTH); // Smooth shading, the default, causes the computed colors of vertices to be interpolated as the primitive is rasterized, typically assigning different colors to each resulting pixel fragment
#endif

	light.enable();  // enable lighting in the scene
	ofEnableSeparateSpecularLight();

	ofPushMatrix(); // ofPushMatrix saves the current coordinate system allowing us to develop specific movements in graphic models to play the animations.

	ofTranslate(model.getPosition().x + 100, model.getPosition().y, 0); // ofTranslate produces a translation by (x,y,z) vector of our coordinate system. The call of ofTranslate modifies graphics positions. Use ofPushMatrix and ofPopMatrix to save and restore the untranslated coordinate system.

	ofRotateDeg(-mouseX, 0, 1, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);

	model.drawFaces();  // This draws the mesh as faces, meaning that you'll have a collection of faces

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

	if (meshHelper.hasTexture()) {
		meshHelper.getTextureRef().bind();
	}
	material.begin();
	mesh.drawWireframe();
	material.end();
	if (meshHelper.hasTexture()) {
		meshHelper.getTextureRef().unbind();
	}
	ofPopMatrix();

	ofDisableDepthTest();
	light.disable();
	ofDisableLighting();
	ofDisableSeparateSpecularLight();

	// Displays helpful text regarding the scene
	if (bHelpText) {
		ofSetColor(255, 255, 255);
		stringstream ss;
		ss << "FPS: " << ofToString(ofGetFrameRate(), 0) << endl << endl;
		ss << "(keys 1-4): load models" << endl;
		ss << "num of animations in this model: " + ofToString(model.getAnimationCount());
		ss << endl << "(Spacebar): toggle animation" << endl;
		ss << "(LEFT MOUSE BUTTON DRAG in y-axis): control animation." << endl;
		/*ss << "(h): toggle help." << endl;*/
		ofDrawBitmapString(ss.str().c_str(), 20, 20);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	glm::vec3 modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.85, 0);
	switch (key) {
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
	/*case 'h':
		bHelpText = !bHelpText;
		break;*/
	default:
		break;
	}

	mesh = model.getMesh(0);

	model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	model.playAllAnimations();
	if (!bAnimate) {
		model.setPausedForAllAnimations(true);
	}
}
