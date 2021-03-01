#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h" // is used to load in 3D file types including 3ds, .obj, .dae etc. and provide access to their vertices, textures, materials, and animation.
#include "ofVboMesh.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void receiveMessage(ofMessage msg);
	
	ofxAssimpModelLoader model;  // permits loading to memory and processing 3D models in a convenient and unified format. In our case OBJ models.

	bool bHelpText;
	bool bAnimate;
	bool bAnimateMouse;
	float animationPosition;

	ofMesh mesh;   // An ofMesh represents a set of vertices in 3D spaces, and normals at those points, colors at those points, and texture coordinates at those points
	ofLight	light;  // ofLight is an openGL light for 3D rendering
};

#endif