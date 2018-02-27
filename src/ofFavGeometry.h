//
//  ofFavGeometry.h
//  FavExample
//
//  Created by m0Rya on 2018/02/26.
//

#ifndef ofFavGeometry_h
#define ofFavGeometry_h

#include "ofxFav.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"


class ofFavGeometry{
    
public:
    
    void setGeometry(FavLibrary::Geometry _geometry){
        geometry = _geometry;
    }
    
    void setup(){
        
        originScale = ofVec3f(geometry.getScaleX(), geometry.getScaleY(), geometry.getScaleZ());

        if (geometry.getShape() == FavLibrary::GeometryShape::cube){
            //cube = ofBoxPrimitive(geometry.getScaleX(), geometry.getScaleY(), geometry.getScaleZ());
            cube = ofBoxPrimitive(originScale.x, originScale.y, originScale.z);
            model_id = 0;
            
        }else if (geometry.getShape() == FavLibrary::GeometryShape::sphere){
            //It needs debug
            //sphere = ofSpherePrimitive(geometry.getScaleX(), 4);
            sphere = ofSpherePrimitive(originScale.x, 4);
            model_id = 1;
            
        }else if (geometry.getShape() == FavLibrary::GeometryShape::user_defined){
            
            userDefinedModel.loadModel(geometry.getReference());
            userDefinedModel.setScale(originScale.x, originScale.y, originScale.z);
            //userDefinedModel.setScale(geometry.getScaleX() * baseScale, geometry.getScaleY() * baseScale, geometry.getScaleZ() * baseScale);
            
            model_id = 2;
        }
        
        
        ///Print out about geometry information///
        cout << "\n///Geometry Informatin///" << endl;
        cout << "   id      : " << geometry.getId() << endl;
        cout << "   name    : " << geometry.getName() << endl;
        
        cout << "   scale" << endl;
        cout << "         x : " << geometry.getScaleX() << endl;
        cout << "         y : " << geometry.getScaleY() << endl;
        cout << "         z : " << geometry.getScaleZ() << endl;
        
        cout << "   shape   : ";
        if(geometry.getShape() == FavLibrary::GeometryShape::cube){
            cout << "cube" << endl;
        }else if(geometry.getShape() == FavLibrary::GeometryShape::sphere){
            cout << "sphere" << endl;
        }else if(geometry.getShape() == FavLibrary::GeometryShape::user_defined){
            cout << "user_defined" << endl;
            cout << "refer  : " << geometry.getReference() << endl;
        }
        cout << "/////////////////////////\n" << endl;
        
        
        
        
    }
    
    
    void draw(ofVec3f position){
        
        if(model_id == 0){
            
            cube.setPosition(position);
            cube.draw();
            
        }else if(model_id == 1){
            
            sphere.setPosition(position);
            sphere.draw();
            
        }else if(model_id == 2){
            
            ofPushMatrix();
            ofRotate(-90, 1, 0, 0);
            ofRotate(180, 0, 0, 1);
            
            //kachoii!!
            /*
             ofRotate(i*10 , 1, 0, 0);
             ofRotate(k*10, 0, 1, 0);
             ofRotate(j*10, 0, 0, 1);
             */
            //#kachoii!
            
            
            userDefinedModel.setPosition(position.x, position.y, position.z);
            userDefinedModel.drawFaces();
            ofPopMatrix();
        }
    }
    
    void setScale(ofVec3f _scale){
        scale = _scale;
        
        if(model_id == 0){
            cube.set(originScale.x * scale.x, originScale.y * scale.y, originScale.z * scale.z);
        }else if(model_id == 1){
            //TODO
            sphere.set(originScale.x * scale.x, 4);
        }else if(model_id == 2){
            userDefinedModel.setScale(originScale.x * scale.x, originScale.y * scale.y, originScale.z * scale.z);
        }
        
    }
    
    
private:
    
    FavLibrary::Geometry geometry;
    //model_id : 0->cube, sphere : 1->stl, obj, etc...
    int model_id;
    ofBoxPrimitive cube;
    ofSpherePrimitive sphere;
    
    //as AssimpModelLoader, scale:0.002 may be 1x1x1, not sure
    double baseScale = 0.002;
    
    ofVec3f scale = ofVec3f(1., 1., 1.);
    ofVec3f originScale;
    
    ofxAssimpModelLoader userDefinedModel;
    ofxAssimpModelLoader loadedModel;
};

#endif /* ofFavGeometry_h */
