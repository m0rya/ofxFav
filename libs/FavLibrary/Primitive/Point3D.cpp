//
//  Point3D.cpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#include "Point3D.hpp"

namespace FavLibrary
{
    
    Point3D::Point3D() {}
    Point3D::~Point3D() {}
    Point3D::Point3D(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    void Point3D::set(Point3D p)
    {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }
    
    double Point3D::getX() {
        return x;
    };
    
    double Point3D::getY() {
        return y;
    };
    
    double Point3D::getZ() {
        return z;
    };
    
    void Point3D::set(double x_, double y_, double z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    };
    void Point3D::setX(double x_) { x = x_; };
    void Point3D::setY(double y_) { y = y_; };
    void Point3D::setZ(double z_) { z = z_; };
}
