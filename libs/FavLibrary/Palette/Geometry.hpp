//
//  Geometry.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.hpp"
#include "../Primitive/FavPrimitive.hpp"


namespace FavLibrary
{
    enum class GeometryShape
    {
        cube,
        sphere,
        user_defined,
        none,
    };
    
    class Scale : public Point3D
    {
    public:
        Scale();
        Scale(double x, double y, double z);
        virtual ~Scale();
        
        //    private:
        //        Scale* pScale;
    };
    
    
    class Geometry : public FavPrimitive
    {
    public:
        Geometry();
        Geometry(unsigned int id_);
        Geometry(std::string name_);
        Geometry(unsigned int id_, std::string name_);
        ~Geometry();
        
        GeometryShape getShape();
        void setShape(GeometryShape shape_);
        
        void setName(std::string name_);
        std::string getName();
        
        double getScaleX();
        double getScaleY();
        double getScaleZ();
        void setScaleX(double x_);
        void setScaleY(double y_);
        void setScaleZ(double z_);
        void setScale(double x_, double y_, double z_);
        
        std::string getReference();
        void setReference(std::string reference_);
        
        bool hasShape(){return has_shape;};
        bool hasScale(){return has_scale;};
        
    private:
        std::string reference;
        GeometryShape shape;// = GeometryShape::none;
        Scale scale;
        
        bool has_shape = false;
        bool has_scale = false;
        
        //        Geometry* pGeometry;
    };
    
    
    
}

#endif /* Geometry_hpp */
