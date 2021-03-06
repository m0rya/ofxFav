//
//  Grid.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.hpp"


namespace FavLibrary
{
    
    class Unit : public Point3D
    {
        
    };
    
    class Dimension : public Point3D
    {
        
    };
    
    class Origin : public Point3D
    {
        
    };
    
    class Grid
    {
    public:
        Grid();
        ~Grid();
        
        Unit getUnit();
        void  setUnit(Point3D p);
        void  setUnit(double x, double y, double z);
        void  setUnitX(double x);
        void  setUnitY(double y);
        void  setUnitZ(double z);
        double getUnitX();
        double getUnitY();
        double getUnitZ();
        
        Dimension getDimension();
        void setDimension(Point3D p);
        void setDimension(double x, double y, double z);
        void setDimensionX(double x);
        void setDimensionY(double y);
        void setDimensionZ(double z);
        double getDimensionX();
        double getDimensionY();
        double getDimensionZ();
        
        Origin getOrigin();
        void setOrigin(Point3D p);
        void setOrigin(double x, double y, double z);
        void setOriginX(double x);
        void setOriginY(double y);
        void setOriginZ(double z);
        double getOriginX();
        double getOriginY();
        double getOriginZ();
        
    private:
        Unit unit;
        Dimension dimension;
        Origin origin;
    };
    
}

#endif /* Grid_hpp */
