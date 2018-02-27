//
//  FavPrimitive.h
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef FavPrimitive_h
#define FavPrimitive_h

#include <string>
#include "../FavSettings.h"

namespace FavLibrary
{
    class FavPrimitive
    {
        
    public:
        FavPrimitive(unsigned int id_);
        FavPrimitive(std::string name_);
        FavPrimitive(unsigned int id_, std::string name_);
        
        unsigned int getId();
        void setId(unsigned int id_);
        
        std::string getName();
        void setName(std::string name_);
        
    protected:
        FavPrimitive();
        virtual ~FavPrimitive();
        
        unsigned int identifier;
        std::string name;
    };
}

#endif /* FavPrimitive_h */
