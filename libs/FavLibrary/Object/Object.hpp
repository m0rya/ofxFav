//
//  Object.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Object_hpp
#define Object_hpp


#include <string>
#include "Structure.hpp"
#include "Grid.hpp"
#include "../Metadata.hpp"
#include "../Primitive/FavPrimitive.hpp"


namespace FavLibrary
{
    
    class Object : public FavPrimitive, public MetadataObject
    {
    public:
        Object();
        Object(unsigned int id_);
        Object(std::string name_);
        Object(unsigned int id_, std::string name_);
        ~Object();
        
        Grid grid;
        Structure structure;
    };
    
}

#endif /* Object_hpp */
