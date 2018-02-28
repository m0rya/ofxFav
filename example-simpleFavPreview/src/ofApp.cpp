#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    light.enable();
    light.setPointLight();
    light.setScale(100);
    light.setPosition(-100 ,500, -100);
    
    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
    light.setDiffuseColor(ofFloatColor(0.5, 0.5, 1.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    
    //fav setup
    fav.read("fav/Sphere.fav");
    favPreview.setFav(fav);
    favPreview.setFavFolderPath("fav");
    favPreview.setUserDefinedFolderPath("user_defined");
    favPreview.setup();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    favPreview.update();
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(50);
    light.enable();
    ofEnableDepthTest();
    cam.begin();
    favPreview.draw();
    //favPreview.drawDimension();
    
    cam.end();
    light.disable();
    ofDisableDepthTest();
    favPreview.drawGUI();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
