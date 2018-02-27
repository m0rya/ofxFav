//
//  ofxFavPreview.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/21.
//

#ifndef ofxFavPreview_hpp
#define ofxFavPreview_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxFav.h"
#include "ofxGui.h"
#include "ofFavGeometry.h"
#include "ofxAssimpModelLoader.h"
#include "SelectionGui.hpp"


class ofxFavPreview{
    
public:

    ofxFavPreview();
    ~ofxFavPreview();
    
    void setFav(ofxFav &_fav);
    void read(const char *path);
    
    
    void setup();
    void setupFavObject();
    void update();
    /*
    void setLimitX(int _limitX);
    void setLimitY(int _limitY);
    void setLimitZ(int _limitZ);
    */
    
    void setupGui();
    void updateGui();
    void drawGUI();

    void draw();
    void drawDimension();
    
    
    
    
    vector<ofVec3f> getOriginVoxs();
    

    
    void reloadFavButtonPressed();
    
    void setFavFolderPath(string _path);
    void setUserDefinedFolderPath(string _path);
    
    FavLibrary::Object getFavObject();
    
    
    
private:
    
    ofxFav *fav;
    FavLibrary::Object obj;
    
    void setupGeometry();

    
    int limitX;
    int limitY;
    int limitZ;
    
    vector< vector < vector<char>>> voxel_map;
    vector< vector < vector<ofColor>>> color_map;
    
    vector<ofVec3f> originVoxs;
    
    ofxAssimpModelLoader loadedModel;
    ofMesh mesh;
    
    
    //gui
    ofxPanel gui;
    ofxLabel sliceLabel;
    ofxIntSlider x_slider;
    ofxIntSlider y_slider;
    ofxIntSlider z_slider;
    
    ofxButton reloadFavButton;
    ofxFloatSlider geoScale;
    
    ofxButton resetScaleButton;
    void resetScale();
    
    
    //gui scale group
    ofxLabel scaleGroupLabel;
    float scaleMax = 10;
    ofxToggle linkScaleToggle;
    ofParameter<ofVec3f> voxelScale;
    void scaling(ofVec3f & voxelScale);
    ofParameter<float> linkScale;
    void linkScaling(float & linkScale);
    
    
    //selected 3d data from folder
    string favFolderPath = "fav";
    ofxLabel selectionFavLabel;
    SelectionGui selectionFav;
    
    
    //Gui user defined
    ofxLabel userDefinedLabel;
    ofxToggle userDefinedToggle;
    ofxButton userDefinedButton;
    SelectionGui selectionUserDefined;
    
    
    
    vector<ofFavGeometry> favGeometries;
    ofVec3f unit;
    ofVec3f origin;
    ofVec3f dimension;
    
    
    //user defined voxel from folder
    string userDefinedFolderPath = "user_defined";
    vector<ofxAssimpModelLoader> modelsFromFolder;
    double modelScale = 0.002;
    
  
    
    
    
    
    
    
    
    
};

#endif /* ofxFavPreview_hpp */
