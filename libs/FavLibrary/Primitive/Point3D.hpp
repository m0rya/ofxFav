//
//  Point3D.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Point3D_hpp
#define Point3D_hpp

#include "../FavSettings.h"

namespace FavLibrary
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(double x, double y, double z);
        virtual ~Point3D();
        
        void set(Point3D p);
        
        double getX();
        double getY();
        double getZ();
        void set(double x_, double y_, double z_);
        void setX(double x_);
        void setY(double y_);
        void setZ(double z_);
        
    protected:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };
    
}
#endif /* Point3D_hpp */
