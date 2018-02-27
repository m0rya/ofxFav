//
//  CurvedSurface.cpp
//  example-curvedSurface2Fav
//
//  Created by m0Rya on 2018/02/28.
//

#include "CurvedSurface.hpp"


CurvedSurface::CurvedSurface(){}

CurvedSurface::CurvedSurface(int _fineness, int _rangeValue){
    fineness = _fineness;
    rangeValue = _rangeValue;
    
    setMesh();
    
}

CurvedSurface::~CurvedSurface(){
    voxelScaleSlider.removeListener(this, &CurvedSurface::reloadVoxelScale);
    finenessSlider.removeListener(this, &CurvedSurface::reloadFineness);
}

void CurvedSurface::setPoint(){
    
    vec += 0.1;
    
    point.clear();
    
    for(int i=0; i<(fineness+1); i++){
        for(int j=0; j<(fineness+1); j++){
            
            float x = float(-rangeValue + j * 2.0 * rangeValue / fineness);
            float y = float(-rangeValue + i * 2.0 * rangeValue / fineness);
            
            float z = func5(x, y);
            
            //hoge
            x *= 100;
            y *= 100;
            z *= 100;
            
            point.push_back(ofVec3f(x, z, y));
            
        }
    }
}



void CurvedSurface::setTorusPoint(){
    mesh.clear();
    point.clear();
    
    for(int i=0; i<(fineness+1); i++){
        for(int j=0; j<(fineness+1); j++){
            double s = double(2.0*PI/fineness * i);
            double t = double(2.0*PI/fineness * j);
            
            
            //sphere
            /*
            float x = cos(s) * cos(t);
            float y = cos(s) * sin(t);
            float z = sin(s);
            */
            
            //turus
            float x = float(((3.0+vv) + cos(s)) * cos(t));
            float y = float(((3.0+jj) + cos(s)) * sin(t));
            float z = float(sin(s) + (0.5 + dd)*sin(5*t));
            
            
            /*
             x = float(((5+vv)-0.3*t + 1.2 * cos(s)) * cos(t));
             y = float(((5+jj)-0.3*t + 1.2 * cos(s)) * sin(t));
             z = float((1.2+dd) * sin(s) + 0.3 * t);
             */
            
            x *= 70;
            y *= 70;
            z *= 70;
            
            point.push_back(ofVec3f(x, y, z));
        }
    }
}


void CurvedSurface::setMesh(){
    mesh.clear();
    
    //setPoint();
    setTorusPoint();
    
    for(int i=0; i<(fineness+1); i++){
        for(int j=0; j<(fineness+1); j++){
            mesh.addVertex(point[i*(fineness+1) + j]);
            mesh.addNormal(ofVec3f(0, -1.0, 0));
            mesh.addColor(color);
        }
    }
    
    for(int i=0; i<fineness; i++){
        for(int j=0; j<fineness; j++){
            mesh.addIndex(i*(fineness+1) + j);
            mesh.addIndex(i*(fineness+1) + j + 1);
            mesh.addIndex((i+1) * (fineness+1) + j);
            
            mesh.addIndex(i*(fineness+1) + j + 1);
            mesh.addIndex((i+1)*(fineness+1) + j);
            mesh.addIndex((i+1) * (fineness+1) + j + 1);
        }
    }
    
    convert2Voxel();
}

void CurvedSurface::update(){
    if(vv > 10){
        vecVV = -1.0;
    }else if(vv< -10){
        vecVV = 1.0;
    }
    
    if(jj > 10){
        vecJJ= -1.0;
    }else if(jj < -10){
        vecJJ= 1.0;
    }
    
    if(dd > 3){
        vecDD= -1.0;
    }else if(dd < -3){
        vecDD= 1.0;
    }
    if(pp > 3){
        vecPP= -1.0;
    }else if(pp < -3){
        vecPP= 1.0;
    }
    
    vv += vecVV/2.0;
    jj += vecJJ/2.5;
    dd += vecDD/2.0;
    setMesh();
}


void CurvedSurface::convert2Voxel(){
    pointForVoxel.clear();
    
    for(int i=0; i<point.size(); i++){
        int newX = int(point[i].x/voxelScale)*voxelScale;
        int newY = int(point[i].y/voxelScale)*voxelScale;
        int newZ = int(point[i].z/voxelScale)*voxelScale;
        
        pointForVoxel.push_back(ofVec3f(newX, newY, newZ));
    }
}
void CurvedSurface::drawVoxel(){
    for(int i=0; i<pointForVoxel.size(); i++){
        ofDrawBox(pointForVoxel[i], voxelScale);
    }
}

void CurvedSurface::draw(){
    mesh.draw();
    //mesh.drawWireframe();
}

void CurvedSurface::drawWireframe(){
    mesh.drawWireframe();
}

void CurvedSurface::drawVertices(){
    mesh.drawVertices();
}


void CurvedSurface::setFineness(int _fineness){
    fineness = _fineness;
}

void CurvedSurface::setRangeValue(int _rangeValue){
    rangeValue = _rangeValue;
}

void CurvedSurface::setColor(ofColor _color){
    color = _color;
}


//GUI

void CurvedSurface::setupGui(){
    
    gui.setup();
    voxelScaleSlider.addListener(this, &CurvedSurface::reloadVoxelScale);
    finenessSlider.addListener(this, &CurvedSurface::reloadFineness);
    
    gui.add(voxelScaleSlider.set("Voxel Scale", 10, 1, 20));
    gui.add(finenessSlider.set("Fineness", 200, 50, 500));
}


void CurvedSurface::reloadVoxelScale(int & voxelScaleSlider){
    voxelScale = voxelScaleSlider;
    convert2Voxel();
    
}

void CurvedSurface::reloadFineness(int & finenessSlider){
    fineness = finenessSlider;
    setMesh();
    
}

void CurvedSurface::drawGui(){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    gui.draw();
}


void CurvedSurface::exportFav(){
    cout << "Exporting .fav file" << endl;
    
    ofxFav favForWrite;
    
    //prepar before write fav
    ofVec3f min = pointForVoxel[0];
    ofVec3f max = pointForVoxel[0];
    for(int i=1; i<pointForVoxel.size(); i++){
        if(min.x > pointForVoxel[i].x) min.x = pointForVoxel[i].x;
        if(min.y > pointForVoxel[i].y) min.y = pointForVoxel[i].y;
        if(min.z > pointForVoxel[i].z) min.z = pointForVoxel[i].z;
        
        if(max.x < pointForVoxel[i].x) max.x = pointForVoxel[i].x;
        if(max.y < pointForVoxel[i].y) max.y = pointForVoxel[i].y;
        if(max.z < pointForVoxel[i].z) max.z = pointForVoxel[i].z;
    }
    
    ofVec3f dimension(int((max.x-min.x)/voxelScale), int((max.y-min.y)/voxelScale), int((max.z-min.z)/voxelScale));
    
    vector<vector<vector<int>>> voxel_map;
    
    voxel_map.resize(dimension.x+1);
    for(int i=0; i<voxel_map.size(); i++){
        voxel_map[i].resize(dimension.z+1);
        
        for(int j=0; j<voxel_map[i].size(); j++){
            voxel_map[i][j].resize(dimension.y+1);
        }
    }
    
    //init voxel_map
    for(int i=0; i<voxel_map.size(); i++){
        for(int j=0; j<voxel_map[i].size(); j++){
            for(int k=0; k<voxel_map[i][j].size(); k++){
                voxel_map[i][j][k] = 0;
            }
        }
    }
    
    
    for(int i=0; i<pointForVoxel.size(); i++){
        
        voxel_map[int((pointForVoxel[i].x - min.x)/voxelScale)][int((pointForVoxel[i].z - min.z)/voxelScale)][int((pointForVoxel[i].y-min.y)/voxelScale)] = 1;
        
    }
    
    
    
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_string_t idForFav;
    uuid_unparse_lower(uuid, idForFav);
    string id = idForFav;
    
    favForWrite.setMetadataId(id);
    favForWrite.setMetadataAuthor("m0Rya");
    favForWrite.setMetadataTitle("voxel from Curved Surface");
    favForWrite.setMetadataLicense("No License");
    favForWrite.setMetadataNote("note");
    
    FavLibrary::Geometry geometry1 = FavLibrary::Geometry(1, "geometry1");
    //geometry1.setScale(voxelScale, voxelScale, voxelScale);
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
    //grid1.setUnit(voxelScale, voxelScale, voxelScale);
    grid1.setUnit(1, 1, 1);
    grid1.setOrigin(-dimension.x/2, -dimension.z/2, -dimension.y/2);
    grid1.setDimension(dimension.x, dimension.z, dimension.y);
    
    FavLibrary::Structure structure1 = FavLibrary::Structure();
    structure1.setBitPerVoxel(FavLibrary::BitPerVoxel::Bit8);
    structure1.setGridPointer(&grid1);
    structure1.initVoxelMap();
    
    structure1.initColorMap(FavLibrary::ColorMode::RGB);
    
    for(int i=0; i<dimension.x; i++){
        for(int j=0; j<dimension.z; j++){
            for(int k=0; k<dimension.y; k++){
                if(voxel_map[i][j][k] > 0){
                    
                    structure1.setVoxel(i, j, k, 1);
                    structure1.setColor(i, j, k, FavLibrary::ColorRGB(255, 255, 255));
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
    favForWrite.write("voxelFromCurvedSurface.fav", FavLibrary::CompressionMode::base64);
    
    cout << "Succesfuly .fav file has been exported\n";
    
    
}


//--------------------------------------------------------------


