//
//  Material.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Material_hpp
#define Material_hpp


#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <memory>
#include "../Metadata.hpp"
#include "../Primitive/FavPrimitive.hpp"


namespace FavLibrary
{
    enum class MaterialType {
        material_name = 0,
        product_info = 1,
        iso_standard = 2,
    };
    
    
    class MaterialSpec {
    public:
        virtual void dammy() {};
        MaterialSpec();
        ~MaterialSpec();
        
        MaterialType materialType;
    };
    
    
    class MaterialName : public MaterialSpec {
    public:
        
        MaterialName(std::string name_);
        std::string getMaterialName();
        void setMaterialName(std::string name_);
        
    private:
        std::string name;
    };
    
    
    class ProductInfo : public MaterialSpec {
    public:
        ProductInfo();
        ProductInfo(std::string manufacturer_, std::string product_name_, std::string url_);
        
        std::string getManufacturer();
        void setManufacturer(std::string manufacturer_);
        
        std::string getUrl();
        void setUrl(std::string url_);
        
        std::string getProductName();
        void setProductName(std::string product_name_);
        
    private:
        std::string manufacturer;
        std::string product_name;
        std::string url;
    };
    
    
    class IsoStandard : public MaterialSpec {
    public:
        IsoStandard();
        IsoStandard(std::string iso_id_, std::string iso_name_);
        std::string getIsoId();
        void setIsoId(std::string iso_id_);
        
        std::string getIsoName();
        void setIsoName(std::string iso_name_);
        
    private:
        std::string iso_id;
        std::string iso_name;
    };
    
    
    class Material : public FavPrimitive, public MetadataObject
    {
    public:
        Material();
        Material(unsigned int id_);
        Material(std::string name_);
        Material(unsigned int id_, std::string name_);
        ~Material();
        
        std::list<std::shared_ptr<MaterialSpec>> materials;
        
        bool hasMaterials();
        
        int getNumMaterials();
        
        void addMaterialName(std::string material_name_);
        void addMaterialName(MaterialName material_name_);
        
        void addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_);
        void addProductInfo(ProductInfo product_info_);
        
        void addIsoStandard(std::string iso_id_, std::string iso_name_);
        void addIsoStandard(IsoStandard iso_standard_);
        
    private:
    };
    
    
}

#endif /* Material_hpp */
