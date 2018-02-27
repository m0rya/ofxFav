#include "ofApp.h"

//CurvedSurface surface(200, 3);;


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    
    light.enable();
    light.setPointLight();
    light.setScale(100);
    light.setPosition(-100, 300, -100);
    
    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
    light.setDiffuseColor(ofFloatColor(0.5, 0.5, 1.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    
    ofSetFrameRate(24);
    
    surface.setColor(ofColor(255, 0, 0));
    surface.setMesh();
    surface.setupGui();
    
    surface.setFineness(200);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //surface.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    
    ofEnableDepthTest();
    light.enable();
    cam.begin();
    
    //surface.drawVertices();
    surface.drawVoxel();

    cam.end();
    
    
    ofDisableDepthTest();
    light.disable();
    surface.drawGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
        surface.exportFav();
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
