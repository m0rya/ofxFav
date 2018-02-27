//
//  Object.cpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#include "Object.hpp"
#include "Structure.hpp"

namespace FavLibrary
{
    Object::Object() {};
    
    Object::Object(unsigned int id_)  : FavPrimitive(id_) {
        
        structure.setGridPointer(&grid);
        
    };
    
    Object::Object(std::string name_) : FavPrimitive(name_) {
        
        structure.setGridPointer(&grid);
        
    };
    
    Object::Object(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {
        
        structure.setGridPointer(&grid);
        
    };
    
    Object::~Object() {
    };
    
}
