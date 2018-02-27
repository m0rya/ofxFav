//
//  Vector3D.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <math.h>
#include "Point3D.hpp"


namespace FavLibrary
{
    class Vector3D : public Point3D
    {
    public:
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D();
        
        double GetLength();
        double GetDotProduct(Vector3D v);
        Vector3D* GetCrossProduct(Vector3D v);
        
        static double GetDotProduct(Vector3D v1, Vector3D v2);
        static Vector3D* GetCrossProduct(Vector3D v1, Vector3D v2);
        
    private:
    };
    
}
#endif /* Vector3D_hpp */
