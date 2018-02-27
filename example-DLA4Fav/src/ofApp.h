#pragma once

#include "ofMain.h"
#include "ofxFav.h"
#include "ofxFavPreview.h"
#include <uuid/uuid.h>

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
    
    
    void setupDla();
    void simulateDla();
    void drawRandomWalker();
    void drawSticked();
    void exportFav();
    
    
    ofEasyCam cam;
    ofxFav fav;
    ofxFav favForWrite;
    ofxFavPreview favPreview;
    ofLight light;
    ofImage grabber;
    
    
    bool showGui = true;
    bool showRandomWalker;
    bool simulationStart = false;
    bool recording = false;
    
    int numSeeds = 10000;
    int dlaAreaSize = 30;
    int maxSpeed = 5;
    
    int startFrame = 0;
    
    ofVec3f dim;
    FavLibrary::Object obj;
    
    vector<ofVec3f> seeds;
    vector<ofVec3f> sticked;
    vector<ofVec3f> base;
    vector<int> stickedColorId;
    vector<int> toRemove;
    
    
    //for export fav
    vector<vector<vector<int>>> voxel_color_map;
    
		
};
