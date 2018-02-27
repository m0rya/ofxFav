#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableSmoothing();

    
    
    fav.read("fav/SquarePyramid.fav");
    //fav.read("fav/ChessKing_Color_reso1_v1.fav");
    favPreview.setFav(fav);
    favPreview.setup();
    
    
    
    light.enable();
    light.setPointLight();
    light.setScale(100);
    light.setPosition(-100, 300, -100);
    
    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
    light.setDiffuseColor(ofFloatColor(0.5, 0.5, 1.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    
    
    
    setupDla();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(simulationStart){
        simulateDla();
    }

}

//--------------------------------------------------------------

void ofApp::draw(){
    
    ofBackground(50);
    ofEnableDepthTest();
    
    cam.begin();
    if(recording){
        ofRotateY(ofGetFrameNum());
    }
    
    
    //base
    ofSetColor(77, 173, 161);
    for(int i=0; i<base.size(); i++){
        ofDrawBox(base[i].x, base[i].y, base[i].z, 1);
    }
    
    if(showRandomWalker){
        ofSetColor(223, 144, 124);
        drawRandomWalker();
    }
    
    ofSetColor(236, 208, 112);
    drawSticked();
    
    cam.end();
    
    ofDisableDepthTest();
    ofSetColor(131, 186, 214);
    ofDrawBitmapString("Num of RandomWalker : " + ofToString(seeds.size()), 20, 20);
    ofDrawBitmapString("Pressing 'ENTER' starts DLA simulation", 20, 50);
    ofDrawBitmapString("Pressing 'w' exports .fav file", 20, 70);
    ofDrawBitmapString("Pressing 'SPACE' toggle show RandomWalker", 20, 90);
    
    
    //recording
    if(simulationStart && recording){
        grabber.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        string numFrame = ofToString(ofGetFrameNum()-startFrame);
        while(numFrame.length() < 5){
            numFrame = "0" + numFrame;
        }
        
        string fileName = "dlaChess/dlaChess_" + numFrame + ".tif";
        grabber.save(fileName);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        showGui = !showGui;
        showRandomWalker = !showRandomWalker;
    }else if(key == OF_KEY_RETURN){
        simulationStart = true;
        startFrame = ofGetFrameNum();
    }else if(key == 'w'){
        exportFav();
    }
}


//--------------------------------------------------------------
void ofApp::setupDla(){
    
    obj = favPreview.getFavObject();
    dim = ofVec3f(obj.structure.getDimensionX(), obj.structure.getDimensionZ(), obj.structure.getDimensionY());

    
    seeds.clear();
    seeds.resize(numSeeds);
    FavLibrary::Object obj = favPreview.getFavObject();
    
    
    //for export .fav
    voxel_color_map.resize(int(dim.x + dlaAreaSize*2));
    for(int i=0; i<voxel_color_map.size(); i++){
        
        voxel_color_map[i].resize(int(dim.z + dlaAreaSize*2));
        
        for(int j=0; j<int(dim.z + dlaAreaSize*2); j++){
            
            voxel_color_map[i][j].resize(int(dim.y + dlaAreaSize*2));
            
            for(int k=0; k<int(dim.y + dlaAreaSize); k++){
                voxel_color_map[i][j][k] = 0;
            }
        }
    }
    
    
    int count = 0;
    while(count < numSeeds){
        int tmpX = int(ofRandom(dim.x + dlaAreaSize)) - (dim.x/2 + dlaAreaSize/2);
        int tmpY = int(ofRandom(dim.y + dlaAreaSize)) - (dim.y/2 + dlaAreaSize/2);
        int tmpZ = int(ofRandom(dim.z + dlaAreaSize)) - (dim.z/2 + dlaAreaSize/2);
        
        if( (tmpX > -dim.x/2 && tmpX < dim.x/2) && (tmpY > -dim.y/2 && tmpY < dim.y/2) && (tmpZ > -dim.z/2 && tmpZ < dim.z/2)){
            continue;
            
        }else{
            seeds[count] = ofVec3f(tmpX, tmpY, tmpZ);
            count++;
        }
        
    }
    
    base = favPreview.getOriginVoxs();
    for(int i=0; i<base.size(); i++){
        voxel_color_map[base[i].x+int(dim.x/2 + dlaAreaSize)] [base[i].z+int(dim.z/2 + dlaAreaSize)] [base[i].y+int(dim.y/2 + dlaAreaSize)] = 1;
    }
    
}

//--------------------------------------------------------------
void ofApp::simulateDla(){
    
    toRemove.clear();
    
    for(int i=0; i<seeds.size(); i++){
        float moveDist = seeds[i].distance(ofVec3f(0, 0, 0));
        moveDist = ofMap(moveDist, 0, dim.x/2+dlaAreaSize/2, 1, maxSpeed);
        
        bool alreadySticked = false;
        

        seeds[i].x += int(ofRandom(-(moveDist+0.9), moveDist+0.9));
        seeds[i].y += int(ofRandom(-(moveDist+0.9), moveDist+0.9));
        seeds[i].z += int(ofRandom(-(moveDist+0.9), moveDist+0.9));
        
        
        
        
        if(seeds[i].x < -(dim.x/2+dlaAreaSize)){
            seeds[i].x = int(-(dim.x/2+dlaAreaSize));
        }else if(seeds[i].x > (dim.x/2+dlaAreaSize)){
            seeds[i].x = int(dim.x/2+dlaAreaSize);
        }
        
        if(seeds[i].y < -(dim.y/2+dlaAreaSize)){
            seeds[i].y = int(-(dim.y/2+dlaAreaSize));
        }else if(seeds[i].y > (dim.y/2+dlaAreaSize)){
            seeds[i].y = int(dim.y/2+dlaAreaSize);
        }
        
        if(seeds[i].z < -(dim.z/2+dlaAreaSize)){
            seeds[i].z = int(-(dim.z/2+dlaAreaSize));
        }else if(seeds[i].z > (dim.z/2+dlaAreaSize)){
            seeds[i].z = int(dim.z/2+dlaAreaSize);
        }
        
        
        for(int j=0; j<sticked.size(); j++){
            //if(seeds[i].distance(sticked[j]) < 2){
            if(abs(seeds[i].x-sticked[j].x) < 2 && abs(seeds[i].y-sticked[j].y) < 2 && abs(seeds[i].z-sticked[j].z) < 2){
                sticked.push_back(seeds[i]);
                stickedColorId.push_back(ofGetFrameNum());
                
                
                voxel_color_map[seeds[i].x+int(dim.x/2 + dlaAreaSize)][seeds[i].z+int(dim.z/2 + dlaAreaSize)][seeds[i].y+int(dim.y/2 + dlaAreaSize)] = ofGetFrameNum();
                
                toRemove.push_back(i);
                alreadySticked = true;
                break;
            }
        }
        
        if(alreadySticked == false){
            for(int j=0; j<base.size(); j++){
                //if(seeds[i].distance(base[j]) < 2){
                if(abs(seeds[i].x-base[j].x) < 2 && abs(seeds[i].y-base[j].y) < 2 && abs(seeds[i].z-base[j].z) < 2){
                    
                    sticked.push_back(seeds[i]);
                    stickedColorId.push_back(ofGetFrameNum());
                    toRemove.push_back(i);
                    break;
                    
                }
            }
        }
        
    }
    
    for(int i=0; i<toRemove.size(); i++){
        seeds.erase(seeds.begin() + toRemove[i] - i);
    }
    
}
//--------------------------------------------------------------

void ofApp::drawRandomWalker(){
    
    for(int i=0; i<seeds.size(); i++){
        ofDrawBox(seeds[i].x, seeds[i].y, seeds[i].z, 1);
    }
}

//--------------------------------------------------------------


void ofApp::drawSticked(){
    for(int i=0; i<sticked.size(); i++){
        ofSetColor(ofColor::fromHsb(ofMap(stickedColorId[i]-startFrame, 0, ofGetFrameNum()-startFrame+ofGetFrameNum()/10, 200, 0), 255, 255));
        ofDrawBox(sticked[i].x, sticked[i].y, sticked[i].z, 1);
    }
}

//--------------------------------------------------------------

void ofApp::exportFav(){
    
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_string_t idForFav;
    uuid_unparse_lower(uuid, idForFav);
    //string id = "7dad652f-fa94-4f9c-a17b-357551438095";
    string id = idForFav;
    favForWrite.setMetadataId(id);
    favForWrite.setMetadataAuthor("m0Rya");
    favForWrite.setMetadataTitle("voxel from DLA");
    favForWrite.setMetadataLicense("No License");
    favForWrite.setMetadataNote("note");
    
    FavLibrary::Geometry geometry1 = FavLibrary::Geometry(1, "geometry1");
    geometry1.setScale(1, 1, 1);
    geometry1.setShape(FavLibrary::GeometryShape::cube);
    favForWrite.palette.addGeometry(geometry1);
    
    FavLibrary::Material material1 = FavLibrary::Material(1, "material1");
    material1.addMaterialName("solid_mat1");
    favForWrite.palette.addMaterial(material1);
    
    FavLibrary::Voxel voxel1 = FavLibrary::Voxel(1, "voxel1");
    voxel1.addMaterialInfo(material1.getId(), 1.0);
    voxel1.setGeometryInfo(FavLibrary::GeometryInfo(geometry1.getId()));
    favForWrite.addVoxel(voxel1);
    
    
    FavLibrary::Grid grid1 = FavLibrary::Grid();
    grid1.setUnit(1, 1, 1);
    grid1.setOrigin(int(-(dim.x + dlaAreaSize)/2), int(-(dim.z + dlaAreaSize)/2), int(-(dim.y + dlaAreaSize/2)));
    grid1.setDimension(dim.x+dlaAreaSize*2, dim.z+dlaAreaSize*2, dim.y+dlaAreaSize*2);
    
    FavLibrary::Structure structure1 = FavLibrary::Structure();
    structure1.setBitPerVoxel(FavLibrary::BitPerVoxel::Bit8);
    structure1.setGridPointer(&grid1);
    structure1.initVoxelMap();
    
    structure1.initColorMap(FavLibrary::ColorMode::RGB);
    
    
    
    structure1.setVoxel(0,0,0,1);
    FavLibrary::ColorRGB rgb = FavLibrary::ColorRGB(0, 0, 0);
    structure1.setColor(0, 0,0,rgb);
    
    for(int i=0; i<voxel_color_map.size(); i++){
        for(int j=0; j<voxel_color_map[i].size(); j++){
            for(int k=0; k<voxel_color_map[i][j].size(); k++){
                
                if(voxel_color_map[i][j][k] > 0){
                    
                    structure1.setVoxel(i, j, k, 1);
                    int tmpColorId = voxel_color_map[i][j][k];
                    if(tmpColorId != 1){
                        ofColor tmpColor = ofColor::fromHsb(ofMap(tmpColorId-startFrame, 0, ofGetFrameNum()-startFrame+ofGetFrameNum()/10, 200, 0), 255, 255);
                        FavLibrary::ColorRGB rgb = FavLibrary::ColorRGB(tmpColor.r, tmpColor.g, tmpColor.b);
                        structure1.setColor(i, j, k, rgb);
                    }else{
                        
                        structure1.setColor(i, j, k, FavLibrary::ColorRGB(77, 173, 161));
                    }
                    
                }else{
                    structure1.setVoxel(i, j, k, 0);
                }
                
            }
        }
    }
    
   
    FavLibrary::Object obj1 = FavLibrary::Object(1, "object");
    obj1.grid = grid1;
    obj1.structure = structure1;
    
    favForWrite.addObject(obj1);
    favForWrite.write("voxelByDLA.fav", FavLibrary::CompressionMode::base64);
    
    cout << "Succesfuly .fav file has been exported\n";
    
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
