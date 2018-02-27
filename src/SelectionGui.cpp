//
//  SelectionGui.cpp
//  FavExample
//
//  Created by m0Rya on 2018/02/26.
//

#include "SelectionGui.hpp"

SelectionGui::SelectionGui(){
    
}


void SelectionGui::setup(string title, string folder_path){
    parameters.setName(title);
    
    ofDirectory dir("./" + folder_path);
    numSelection = dir.listDir();
    
    for(int i=0; i<numSelection; i++){
        
        ofParameter<bool> _bool;
        if(i == 0){
            parameters.add(_bool.set(dir.getName(i), true));
        }else{
            parameters.add(_bool.set(dir.getName(i), false));
        }
        
        datas.push_back(_bool);
        //cout << dir.getName(i) << endl;
    }
    
    //parameters.add(size.set("size", 10, 0, 100));
}

void SelectionGui::update(){
    
    for(int i=0; i<datas.size(); i++){
        if(currentSelected != i && datas[i] == true){
            datas[currentSelected].set(false);
            currentSelected = i;
            break;
        }
    }
}

string SelectionGui::getCurrentSelected(){
    
    return datas[currentSelected].getName();
}

string SelectionGui::getLoaded(int id){
    return datas[id].getName();
}

int SelectionGui::getNumSelection(){
    return numSelection;
}

int SelectionGui::getCurrentSelectedId(){
    return currentSelected;
}
