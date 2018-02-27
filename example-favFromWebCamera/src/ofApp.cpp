#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    grabber.setDeviceID(0);
    grabber.initGrabber(videoWidth, videoHeight);
    
    
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    
    ofEnableDepthTest();
    cam.begin();
    
    ofPixels &pixels = grabber.getPixels();
    
    int grayScale = 0;
    int tmpDepth = 0;
    
    for(int i=0; i<videoWidth; i++){
        for(int j=0; j<videoHeight; j++){
            
            ofColor tmpColor = pixels.getColor(i,j);
            grayScale = 0.299 * tmpColor.r + 0.587 * tmpColor.g + 0.114 * tmpColor.b;
            tmpDepth = ofMap(grayScale, 200, 0, 0, voxelDepth);
            
            ofSetColor(tmpColor);
            
            int length = int(tmpDepth/voxelScale) < 10 ? int(tmpDepth/voxelScale) : 10;
            for(int k=0; k<length; k++){
                ofDrawBox(i*voxelScale-(videoWidth*voxelScale)/2, -j*voxelScale+(videoHeight*voxelScale)/2, tmpDepth-k*voxelScale, voxelScale);
            }
           
            
        }
    }
    
    cam.end();
    
    ofDisableDepthTest();
    ofSetColor(255);
    ofDrawBitmapString("Pressing SPACE-key export .fav file", 20, 20);

}


//--------------------------------------------------------------

void ofApp::writeFavFromWebCam(){
    
    
    
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_string_t idForFav;
    uuid_unparse_lower(uuid, idForFav);
    string id = "7dad652f-fa94-4f9c-a17b-357551438095";

    //favForWrite.setMetadataId(ofToString(idForFav));
    favForWrite.setMetadataId(id);
    favForWrite.setMetadataAuthor("m0Rya");
    favForWrite.setMetadataTitle("voxel from web camera");
    favForWrite.setMetadataLicense("No License");
    favForWrite.setMetadataNote("note");
    
    Geometry geometry1 = Geometry(1, "geometry1");
    geometry1.setScale(voxelScale, voxelScale, voxelScale);
    geometry1.setShape(FavLibrary::GeometryShape::cube);
    favForWrite.palette.addGeometry(geometry1);
    
    Material material1 = Material(1, "material1");
    material1.addMaterialName("solid_mat1");
    favForWrite.palette.addMaterial(material1);
    
    Voxel voxel1 = Voxel(1, "voxel1");
    voxel1.addMaterialInfo(material1.getId(), 1.0);
    voxel1.setGeometryInfo(GeometryInfo(geometry1.getId()));
    favForWrite.addVoxel(voxel1);
    
    
    Grid grid1 = Grid();
    grid1.setUnit(voxelScale, voxelScale, voxelScale);
    grid1.setOrigin(-videoWidth/2, -voxelDepth/2, -videoHeight/2);
    grid1.setDimension(videoWidth, int(voxelDepth/voxelScale), videoHeight);
    
    Structure structure1 = Structure();
    structure1.setBitPerVoxel(FavLibrary::BitPerVoxel::Bit8);
    structure1.setGridPointer(&grid1);
    structure1.initVoxelMap();
    
    structure1.initColorMap(FavLibrary::ColorMode::RGB);
    
    
    int grayScale = 0;
    int tmpDepth = 0;
    ofPixels &pixels =grabber.getPixels();
    
    for(int i=0; i<videoWidth; i++){
        for(int j=0; j<videoHeight; j++){
            
            ofColor tmpColor = pixels.getColor(i, videoHeight-j);
            grayScale = 0.299*tmpColor.r + 0.587*tmpColor.g + 0.114*tmpColor.b;
            tmpDepth = ofMap(grayScale, 200, 0, 0, voxelDepth);
            
            int length = int(tmpDepth/voxelScale) < 10 ? int(tmpDepth/voxelScale) : 10;
            
            tmpDepth /= voxelScale;
            for(int k=0; k<int(voxelDepth/voxelScale); k++){
                
                
                if( k < tmpDepth && k > (tmpDepth - 10)){
                    structure1.setVoxel(i, k, j, 1);
                    ColorRGB rgb = ColorRGB(tmpColor.r, tmpColor.g, tmpColor.b);
                    structure1.setColor(i, k, j, rgb);
                    
                }else{
                    structure1.setVoxel(i, k, j, 0);
                }
                
            }
            
        }
    }
    
    Object obj1 = Object(1, "object");
    obj1.grid = grid1;
    obj1.structure = structure1;
    
    favForWrite.addObject(obj1);
    favForWrite.write("m0rya.fav", FavLibrary::CompressionMode::base64);
    
    cout << "Succesfuly .fav file has been exported\n";
    
    
         
}
//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        
        writeFavFromWebCam();
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
