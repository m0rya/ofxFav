//
//  Color.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Color_hpp
#define Color_hpp


#include "../Metadata.hpp"
#include "FavPrimitive.hpp"

namespace FavLibrary
{
    enum class ColorMode
    {
        Grayscale,
        Grayscale16,
        RGB,
        RGBA,
        CMYK,
    };
    
    class IColor
    {
    public:
        IColor();
        virtual ~IColor();
        
        ColorMode colorMode;
        
    protected:
    };
    
    class ColorRGB : public IColor
    {
    public:
        ColorRGB();
        ColorRGB(unsigned char r_, unsigned char g_, unsigned char b_){r = r_; g = g_; b = b_;};
        virtual ~ColorRGB();
        
        ColorMode colorMode = ColorMode::RGB;//ここconstにするとcompile errorが出てた。要確認
        
        unsigned char getR();
        void setR(unsigned char r);
        
        unsigned char getG();
        void setG(unsigned char g);
        
        unsigned char getB();
        void setB(unsigned char b);
        
        void setColorRBG(unsigned char r, unsigned char g, unsigned char b);
        
    protected:
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
    
    class ColorRGBA : public ColorRGB
    {
    public:
        ColorRGBA();
        ColorRGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_){r = r_; g = g_; b = b_; a=a_;};
        virtual ~ColorRGBA();
        
        ColorMode colorMode = ColorMode::RGBA;
        
        unsigned char getA();
        void setA(unsigned char a);
        
        void setColorRBGA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        
    private:
        unsigned char a;
    };
    
    class ColorGrayscale : public IColor
    {
    public:
        ColorGrayscale();
        virtual ~ColorGrayscale();
        
        ColorMode colorMode = ColorMode::Grayscale;
        
        unsigned char getGray();
        void setGray(unsigned char gray);
        
    protected:
        unsigned char gray;
    };
    
    class ColorGrayscale16 : public ColorGrayscale
    {
    public:
        ColorGrayscale16();
        virtual ~ColorGrayscale16();
        
        ColorMode colorMode = ColorMode::Grayscale16;
        
        unsigned short getGray();
        void setGray(unsigned short gray);
        
    private:
        unsigned short gray;
    };
    
    class ColorCMYK : public IColor
    {
    public:
        ColorCMYK();
        ColorCMYK(unsigned char c_, unsigned char m_, unsigned char y_, unsigned char k_){c = c_; m = m_; y = y_; k = k_;};
        virtual ~ColorCMYK();
        
        ColorMode colorMode = ColorMode::CMYK;
        
        unsigned char getC();
        void setC(unsigned char c);
        
        unsigned char getM();
        void setM(unsigned char m);
        
        unsigned char getY();
        void setY(unsigned char y);
        
        unsigned char getK();
        void setK(unsigned char k);
        
        void setColorCMYK(unsigned char c, unsigned char m, unsigned char y, unsigned char k);
        
    private:
        unsigned char c;
        unsigned char m;
        unsigned char y;
        unsigned char k;
    };
    
}


#endif /* Color_hpp */
