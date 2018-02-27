//
//  ofxFav.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/20.
//

#ifndef ofxFav_hpp
#define ofxFav_hpp

#include "FavLibrary/Fav.hpp"



class ofxFav : public FavLibrary::Fav{
    
public:
    bool read(std::string file_path);
    bool write(std::string file_path, FavLibrary::CompressionMode compression_mode_);

};




#endif /* ofxFav_hpp */
