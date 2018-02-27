//
//  SelectionGui.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/26.
//

#ifndef SelectionGui_hpp
#define SelectionGui_hpp

#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofMain.h"



class SelectionGui{
    
public:
    SelectionGui();
    
    void setup(string title, string folder_path);
    void update();
    
    ofParameterGroup parameters;
    vector<ofParameter<bool>> datas;
    int numSelection;
    int currentSelected = 0;
    
    
    int getNumSelection();
    string getCurrentSelected();
    string getLoaded(int id);
    int getCurrentSelectedId();
    
    /*
    ofParameter<bool> hoge;
    ofParameter<float> size;
    ofParameter<int> number;
    ofParameter<ofVec2f> position;
    ofParameter<ofColor> color;
     */
    
    
};
#endif /* SelectionGui_hpp */
