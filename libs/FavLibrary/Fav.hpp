//
//  Fav.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Fav_hpp
#define Fav_hpp


 #include <string>
 #include <stdlib.h>
 #include <iostream>
 #include <map>
 #include <algorithm>
 
 
 #include "./Palette/Palette.hpp"
 #include "./Object/Object.hpp"
 #include "Voxel.hpp"
 #include "Metadata.hpp"
 
 namespace FavLibrary
 {
 class Fav : public MetadataObject
 {
 public:
 Fav();
 ~Fav();
 bool read (const char* file_path);
 bool write(const char* file_path, CompressionMode compression_mode_);
 
 std::vector<Voxel> getVoxels();
 Voxel getVoxel(unsigned int id_);
 void addVoxel(Voxel voxel_);
 void removeVoxel(unsigned int id_);
 bool existsVoxel(unsigned int id_);
 
 std::map<unsigned int, Object> getObjects();
 Object getObject(unsigned int id_);
 void addObject(Object object_);
 void removeObject(unsigned int id_);
 
 int getNumObjects();
 int getNumVoxels();
 
 Palette palette;
 
 private:
 std::string version;
 std::map<unsigned int, Voxel> voxels;
 std::map<unsigned int, Object> objects;
 };
 
 }
 



#endif /* Fav_hpp */
