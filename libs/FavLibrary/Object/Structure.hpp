//
//  Structure.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Structure_hpp
#define Structure_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../Primitive/Point3D.hpp"
#include "../Primitive/Color.hpp"
#include "Grid.hpp"


namespace FavLibrary
{
    
    enum class BitPerVoxel {
        Bit4 = 4,
        Bit8 = 8,
        Bit16 = 16,
    };
    
    enum class Compression {
        None,
        Zlib,
        Base64,
    };
    
    //    template<typename tVoxelMapType>
    //    class IDll VoxelMap {
    //
    //    public:
    //        VoxelMap(int size);
    //        ~VoxelMap();
    //        void init();
    //        void setVoxel(int index_, int value_);
    //        tVoxelMapType getVoxel(int index_);
    //
    //    private:
    //        unsigned int number_of_voxels;
    //        tVoxelMapType* data;
    //    };
    
    class Structure {
    public:
        Structure(){};
        ~Structure();
        
        void setGridPointer(Grid* grid_){grid = grid_;};
        //void setCompression(Compression compression_);
        //Compression getCompression();
        
        void initVoxelMap();
        void setBitPerVoxel(BitPerVoxel bit_per_voxel_);
        void setVoxel(int index_, int value_);
        void setVoxel(Point3D p_, int value_);
        void setVoxel(int x_, int y_, int z_, int value_);
        BitPerVoxel getBitPerVoxel() { return bit_per_voxel; };
        int getVoxel(int index_);
        int getVoxel(Point3D p_);
        int getVoxel(int x_, int y_, int z_);
        
        void initColorMap();
        void initColorMap(ColorMode color_mode_);
        void setColorMode(ColorMode color_mode_);
        void setColor(Point3D p_, class ColorRGB color_);
        void setColor(Point3D p_, class ColorRGBA color_);
        void setColor(Point3D p_, class ColorCMYK color_);
        void setColor(Point3D p_, class ColorGrayScale color_);
        void setColor(Point3D p_, class ColorGrayScale16 color_);
        void setColor(int x_, int y_, int z_, class ColorRGB color_);
        void setColor(int x_, int y_, int z_, class ColorRGBA color_);
        void setColor(int x_, int y_, int z_, class ColorCMYK color_);
        void setColor(int x_, int y_, int z_, class ColorGrayscale color_);
        void setColor(int x_, int y_, int z_, class ColorGrayscale16 color_);
        void setColor(int x_, int y_, int z_, int r_, int g_, int b_);
        void setColorRGB (Point3D p_, int r_, int g_, int b_);
        void setColorRGBA(Point3D p_, int r_, int g_, int b_, int a_);
        void setColorCMYK(Point3D p_, int c_, int m_, int cy_, int k_);
        void setColorGrayScale(Point3D p_, int k);
        void setColorGrayScale16(Point3D p_, int k);
        void setColorAlpha(Point3D p_, int a_);
        void setColorRGB (int x_, int y_, int z_, int r_, int g_, int b_);
        void setColorRGBA(int x_, int y_, int z_, int r_, int g_, int b_, int a_);
        void setColorCMYK(int x_, int y_, int z_, int c_, int m_, int cy_, int k_);
        void setColorRed  (int x_, int y_, int z_, int r_);
        void setColorGreen(int x_, int y_, int z_, int g_);
        void setColorBlue (int x_, int y_, int z_, int b_);
        void setColorAlpha(int x_, int y_, int z_, int a_);
        void setColorCyan    (int x_, int y_, int z_, int c_);
        void setColorMagenta (int x_, int y_, int z_, int m_);
        void setColorYellow  (int x_, int y_, int z_, int cy_);
        void setColorKeyPlate(int x_, int y_, int z_, int k_);
        void setColor(int x_, int y_, int z_, int gray_);
        
        ColorRGB  getColorRGB (int x_, int y_, int z_);
        ColorRGBA getColorRGBA(int x_, int y_, int z_);
        ColorCMYK getColorCMYK(int x_, int y_, int z_);
        int getColorRed  (Point3D p_);
        int getColorGreen(Point3D p_);
        int getColorBlue (Point3D p_);
        int getColorAlpha(Point3D p_);
        int getColorCyan    (Point3D p_);
        int getColorMagenta (Point3D p_);
        int getColorYellow  (Point3D p_);
        int getColorKeyPlate(Point3D p_);
        int getColorGrayScale  (Point3D p_);
        int getColorGrayScale16(Point3D p_);
        int getColorRed  (int x_, int y_, int z_);
        int getColorGreen(int x_, int y_, int z_);
        int getColorBlue (int x_, int y_, int z_);
        int getColorAlpha(int x_, int y_, int z_);
        int getColorCyan    (int x_, int y_, int z_);
        int getColorMagenta (int x_, int y_, int z_);
        int getColorYellow  (int x_, int y_, int z_);
        int getColorKeyPlate(int x_, int y_, int z_);
        int getColorGrayScale  (int x_, int y_, int z_);
        int getColorGrayScale16(int x_, int y_, int z_);
        
        ColorMode getColorMode() { return color_mode; };
        
        int getDimensionX(){ return grid->getDimensionX(); };
        int getDimensionY(){ return grid->getDimensionY(); };
        int getDimensionZ(){ return grid->getDimensionZ(); };
        
        //TODO: Link map is under development
        //        void initLinkMap();
        //        unsigned int getLink(Point3D p1_, Point3D p2_);
        //        unsigned int getLink(int x1_, int y1_, int z1_, int x2_, int y2_, int z2_);
        //        int getNeighbors(){ return neighbours; };
        
    private:
        
        void convertVoxelMapToVoxelMap16Bit();
        void convertVoxelMap16BitToVoxelMap();
        void convertColorMapToRGB();
        //        void convertColorMapToRGBA();
        void convertColorMapToCMYK();
        void convertColorMapToGrayscale();
        void convertColorMapToGrayscale16();
        void convertRgbToCmyk();
        void convertRgbToGrayscale();
        void convertRgbToGrayscale16();
        void convertCmykToRgb();
        void convertCmykToGrayscale();
        void convertCmykToGrayscale16();
        void convertGrayscaleToRgb();
        void convertGrayscaleToCmyk();
        void convertGrayscaleToGrayscale16();
        void convertGrayscale16ToRgb();
        void convertGrayscale16ToCmyk();
        void convertGrayscale16ToGrayscale();
        
        int getIndex(int x, int y, int z); //returns the index of the array from xyz indices
        
        BitPerVoxel bit_per_voxel;
        ColorMode color_mode;
        //Compression compression;
        int number_of_voxels;
        bool has_color;
        
        std::vector<unsigned char>  voxel_map; //default voxel map
        std::vector<unsigned short> voxel_map_16bit;// for 16bit voxel map
        std::vector<unsigned char>  alpha_map;
        std::vector<unsigned char>  color_map;
        std::vector<unsigned short> color_map_16bit;
        
        Grid* grid;
        
        //TODO: Link map is under development
        //        float* link_map;
        //        int neighbours;
    };
    
}

#endif /* Structure_hpp */
