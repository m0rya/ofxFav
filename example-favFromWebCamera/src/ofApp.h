#pragma once

#include "ofMain.h"
#include <uuid/uuid.h>
#include "ofxFav.h"

using namespace FavLibrary;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void writeFavFromWebCam();
    
    ofxFav favForWrite;
    ofVideoGrabber grabber;
		
    ofEasyCam cam;
    
  
    int videoWidth = 120;
    int videoHeight = 90;
    int voxelScale = 5;

    int voxelDepth = 30 * voxelScale;
    
};
