//
//  ofxFav.cpp
//  FavExample
//
//  Created by m0Rya on 2018/02/25.
//

#include <stdio.h>

#include "ofxFav.h"
#include "FavLibrary/FavReader.hpp"
#include "FavLibrary/FavWriter.hpp"
#include "ofMain.h"


bool ofxFav::read(string file_path){

    ofDirectory dir("./");
    string _file_path = dir.getAbsolutePath();
    _file_path += "/";
    _file_path += file_path;

    FavLibrary::FavReader fav_reader(this);
    return fav_reader.read(_file_path.c_str());
}

bool ofxFav::write(string file_path, FavLibrary::CompressionMode compression_mode_) {

    ofDirectory dir("./");
    string _file_path = dir.getAbsolutePath();
    _file_path += "/";
    _file_path += file_path;
        
    FavLibrary::FavWriter fav_writer(this);
    return fav_writer.write(_file_path.c_str(), compression_mode_);


}
