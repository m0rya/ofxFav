//
//  ofxFavPreview.cpp
//  FavExample
//
//  Created by m0Rya on 2018/02/21.
//

#include "ofxFavPreview.h"

/*
 ofxFavPreview::ofxFavPreview(ofxFav &_fav){
 fav = &_fav;
 }
 */

ofxFavPreview::ofxFavPreview(){}

ofxFavPreview::~ofxFavPreview(){
    reloadFavButton.removeListener(this, &ofxFavPreview::reloadFavButtonPressed);
    resetScaleButton.removeListener(this, &ofxFavPreview::resetScale);
    linkScale.removeListener(this, &ofxFavPreview::linkScaling);
    voxelScale.removeListener(this, &ofxFavPreview::scaling);


}


void ofxFavPreview::read(const char * path){
    fav->read(path);
}


void ofxFavPreview::setFav(ofxFav &_fav){
    fav = &_fav;
}


void ofxFavPreview::setup(){

    setupFavObject();
    setupGui();
    setupGeometry();

}


//read fav file, and prepare for drwawing

void ofxFavPreview::setupFavObject(){

    obj = fav->getObject(1);

    //prepare structure
    voxel_map.clear();
    color_map.clear();
    originVoxs.clear();

    voxel_map.resize(obj.grid.getDimensionX());
    color_map.resize(obj.grid.getDimensionX());

    int dimX = obj.grid.getDimensionX();
    int dimY = obj.grid.getDimensionY();
    int dimZ = obj.grid.getDimensionZ();


    for( int i=0; i < obj.grid.getDimensionX(); i++){
        voxel_map[i].resize(obj.grid.getDimensionY());
        color_map[i].resize(obj.grid.getDimensionY());

        for( int j=0; j < obj.grid.getDimensionY(); j++){
            voxel_map[i][j].resize(obj.grid.getDimensionZ());
            color_map[i][j].resize(obj.grid.getDimensionZ());
        }
    }

    for( int i=0; i < voxel_map.size(); i++){
        for( int j=0; j < voxel_map[i].size(); j++){
            for(int k=0; k < voxel_map[i][j].size(); k++){

                voxel_map[i][j][k] = obj.structure.getVoxel(i,j,k);
                if(obj.structure.getVoxel(i,j,k) > 0 ){
                   originVoxs.push_back(ofVec3f((i - dimX/2), int(k-dimZ/2), int(j-dimY/2)));
               }
                color_map[i][j][k] = ofColor(obj.structure.getColorRed(i,j,k), obj.structure.getColorGreen(i,j,k), obj.structure.getColorBlue(i,j,k));
            }
        }
    }

    /*
    for(int i=0; i<obj.grid.getDimensionX(); i++){
        for(int j=0; j<obj.grid.getDimensionY(); j++){
            for(int k=0; k<obj.grid.getDimensionZ(); k++){
                originVoxs.push_back(ofVec3f(int(i-dimX/2),int(k-dimZ/2),int(j-dimY/2)));
            }
        }
    }
    */

    unit = ofVec3f(obj.grid.getUnitX(), obj.grid.getUnitY(), obj.grid.getUnitZ());
    dimension = ofVec3f(obj.grid.getDimensionX(), obj.grid.getDimensionY(), obj.grid.getDimensionZ());
    origin = ofVec3f(obj.grid.getOriginX(), obj.grid.getOriginY(), obj.grid.getOriginZ());

}




vector<ofVec3f> ofxFavPreview::getOriginVoxs(){
    return originVoxs;
}


void ofxFavPreview::setupGeometry(){

    FavLibrary::Palette _palette = fav->palette;

    favGeometries.clear();
    favGeometries.resize(_palette.getNumberOfGeometries());


    for(int i=0; i<_palette.getNumberOfGeometries(); i++){

        favGeometries.push_back(ofFavGeometry());
        favGeometries[i].setGeometry(_palette.getGeometryById(i+1));
        favGeometries[i].setup();
    }

}



void ofxFavPreview::draw(){
    limitX = x_slider;
    limitY = y_slider;
    limitZ = z_slider;
    loadedModel.setScale(geoScale, geoScale, geoScale);


    for(int i=0; i<limitX; i++){
        for(int j=0; j<limitY; j++){
            for(int k=0; k<limitZ; k++){

                if (+voxel_map[i][j][k] > 0){
                    /*
                    int r = obj.structure.getColorRed(i,j,k);
                    int g = obj.structure.getColorGreen(i,j,k);
                    int b = obj.structure.getColorBlue(i,j,k);
                    ofSetColor(r,g,b);
                     */

                    ofSetColor(color_map[i][j][k]);

                    if(limitX != obj.grid.getDimensionX() && i == limitX-1){
                        ofSetColor(255, 0, 0);
                    }
                    if(limitY != obj.grid.getDimensionY() && j == limitY-1){
                        ofSetColor(0, 255, 0);
                    }
                    if(limitZ != obj.grid.getDimensionZ() && k == limitZ-1){
                        ofSetColor(0, 0, 255);
                    }

                    //favGeometries[+arr[i][j][k]].draw(ofVec3f(i-dimension.x/2, k-dimension.z/2, j-dimension.y/2));
                    if(userDefinedToggle == false){

                        favGeometries[+voxel_map[i][j][k]-1].draw(ofVec3f(i*unit.x - (dimension.x*unit.x)/2, k*unit.z - (dimension.z*unit.z)/2, j*unit.y - (dimension.y*unit.y)/2));

                    }else{


                        modelsFromFolder[selectionUserDefined.getCurrentSelectedId()].setPosition(i*unit.x-(dimension.x*unit.x)/2, k*unit.z-(dimension.z*unit.z)/2, j*unit.y - (dimension.y*unit.y)/2);
                        modelsFromFolder[selectionUserDefined.getCurrentSelectedId()].drawFaces();

                    }
                }
            }
        }
    }

}


void ofxFavPreview::drawDimension(){
    ofBoxPrimitive box_dim;

    box_dim.setWidth(obj.structure.getDimensionX());
    box_dim.setDepth(obj.structure.getDimensionY());
    box_dim.setHeight(obj.structure.getDimensionZ());


    ofSetColor(255, 255, 0);
    box_dim.drawWireframe();


}



void ofxFavPreview::update(){
    selectionUserDefined.update();
    selectionFav.update();
}


void ofxFavPreview::setFavFolderPath(string _path){
    favFolderPath = _path;
}

void ofxFavPreview::setUserDefinedFolderPath(string _path){
    userDefinedFolderPath = _path;
}

FavLibrary::Object ofxFavPreview::getFavObject(){
  return fav->getObject(1);
}
/////GUI//////

void ofxFavPreview::setupGui(){
    gui.setup();
    //gui.setBackgroundColor(255);

    reloadFavButton.addListener(this, &ofxFavPreview::reloadFavButtonPressed);
    resetScaleButton.addListener(this, &ofxFavPreview::resetScale);
    linkScale.addListener(this, &ofxFavPreview::linkScaling);
    voxelScale.addListener(this, &ofxFavPreview::scaling);


    //Slice
    gui.add(sliceLabel.setup("Slice",""));
    sliceLabel.setBackgroundColor(ofColor(223, 144, 124));
    gui.add(x_slider.setup("X", obj.grid.getDimensionX(), 0, obj.grid.getDimensionX()));
    gui.add(y_slider.setup("Y", obj.grid.getDimensionY(), 0, obj.grid.getDimensionY()));
    gui.add(z_slider.setup("Z", obj.grid.getDimensionZ(), 0, obj.grid.getDimensionZ()));

    //Scale Group
    gui.add(scaleGroupLabel.setup("Scale voxel", ""));
    scaleGroupLabel.setBackgroundColor(ofColor(226, 198, 102));
    gui.add(resetScaleButton.setup("Reset Scale"));
    gui.add(linkScaleToggle.setup("Linking Scale Toggle", true));
    gui.add(linkScale.set("Link Scale", 1.0, 0.0, scaleMax));
    gui.add(voxelScale.set("voxel scale", ofVec3f(1.0, 1.0, 1.0), ofVec3f(0.0, 0.0, 0.0), ofVec3f(scaleMax, scaleMax, scaleMax)));


    //Selection .fav Group
    gui.add(selectionFavLabel.setup("Selection .fav file", ""));
    selectionFavLabel.setBackgroundColor(ofColor(131, 186, 214));
    gui.add(reloadFavButton.setup("Reload fav"));

    selectionFav.setup("Fav Folder", favFolderPath);
    gui.add(selectionFav.parameters);


    //Selection Voxel
    gui.add(userDefinedLabel.setup("Selection voxel", ""));
    userDefinedLabel.setBackgroundColor(ofColor(77, 173, 161));
    gui.add(userDefinedToggle.setup("Use user defined", false));
    gui.add(userDefinedButton.setup("Reload voxel"));


    //load user defined data from folder
    selectionUserDefined.setup("User Defined Folder", userDefinedFolderPath);
    for(int i=0; i<selectionUserDefined.getNumSelection(); i++){
        ofxAssimpModelLoader tmpModel;
        tmpModel.loadModel(userDefinedFolderPath + "/" + selectionUserDefined.getLoaded(i));
        tmpModel.setScale(modelScale, modelScale, modelScale);
        modelsFromFolder.push_back(tmpModel);
    }

    gui.add(selectionUserDefined.parameters);

}

void ofxFavPreview::updateGui(){

    x_slider.setMax(obj.grid.getDimensionX());
    y_slider.setMax(obj.grid.getDimensionY());
    z_slider.setMax(obj.grid.getDimensionZ());

    x_slider = obj.grid.getDimensionX();
    y_slider = obj.grid.getDimensionY();
    z_slider = obj.grid.getDimensionZ();
}


void ofxFavPreview::reloadFavButtonPressed(){

    ofxFav newFav;
    string new_path = favFolderPath + "/" + selectionFav.getCurrentSelected();

    newFav.read(new_path);
    fav = &newFav;

    this->setupGeometry();
    this->setupFavObject();
    this->updateGui();

}

void ofxFavPreview::resetScale(){
    voxelScale = ofVec3f(1.0, 1.0, 1.0);
    linkScale = 1.0;
}

void ofxFavPreview::scaling(ofVec3f & voxelScale){

    if(linkScaleToggle == false){

        if(userDefinedToggle == false){

            for(int i=0; i<favGeometries.size(); i++){
            favGeometries[i].setScale(voxelScale);
            }

        }else{

            for(int i=0; i<selectionUserDefined.getNumSelection(); i++){
                modelsFromFolder[i].setScale(modelScale*voxelScale.x, modelScale*voxelScale.y, modelScale*voxelScale.z);

            }
        }
    }

}

void ofxFavPreview::linkScaling(float & linkScale){

    if(linkScaleToggle == true){

        if(userDefinedToggle == false){

            for(int i=0; i<favGeometries.size(); i++){
                favGeometries[i].setScale(ofVec3f(linkScale, linkScale, linkScale));
            }

        }else{

            for(int i=0; i<selectionUserDefined.getNumSelection(); i++){
                modelsFromFolder[i].setScale(modelScale*linkScale, modelScale*linkScale, modelScale*linkScale);
            }
        }
    }
}



void ofxFavPreview::drawGUI(){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    gui.draw();
}
