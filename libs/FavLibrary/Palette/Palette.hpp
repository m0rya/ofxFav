//
//  Palette.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Palette_hpp
#define Palette_hpp

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include "Geometry.hpp"
#include "Material.hpp"


namespace FavLibrary
{
    
    class Palette {
        
    public:
        Palette();
        ~Palette();
        
        Geometry getGeometryById(unsigned int id_);
        void addGeometry(Geometry geometry_);
        void removeGeometry(unsigned int id_);
        
        Material getMaterialById(unsigned int id_);
        void addMaterial(Material material_);
        void removeMaterial(unsigned int id_);
        
        int getNumberOfGeometries();
        int getNumberOfMaterials();
        
    private:
        std::map<unsigned int, Geometry> geometries;
        std::map<unsigned int, Material> materials;
        std::vector<unsigned int> geometry_id_list;
        std::vector<unsigned int> material_id_list;
        
        unsigned int number_of_materials;
        unsigned int number_of_geometries;
        
        //        Palette* pPalette;
    };
}

#endif /* Palette_hpp */
