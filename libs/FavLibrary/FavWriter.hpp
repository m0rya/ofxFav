//
//  FavWriter.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/15.
//

#ifndef FavWriter_hpp
#define FavWriter_hpp

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include "./Object/Object.hpp"

#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/Base64.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

//using namespace xercesc;

namespace FavLibrary
{
    class Fav;
    
    class FavWriter {
        
    public:
        
        FavWriter(Fav* fav_);
        bool write(const char* file_path);
        bool write(const char* file_path, CompressionMode compression_mode_);
        
    private:
        
        xercesc::DOMElement* createElement(const char* name_);
        void appendCDATA (xercesc::DOMElement* parent_elem, const char* child_elem_name, XMLCh*      text);
        void appendCDATA (xercesc::DOMElement* parent_elem, const char* child_elem_name, const char* text);
        void appendCDATA (xercesc::DOMElement* parent_elem, const char* child_elem_name, std::string text);
        void appendText  (xercesc::DOMElement* parent_elem, const char* child_elem_name, const char* text);
        void appendText  (xercesc::DOMElement* parent_elem, const char* child_elem_name, std::string text);
        void setAttribute(xercesc::DOMElement* elem, const char* attr_name, const char* attr_value);
        void setAttribute(xercesc::DOMElement* elem, const char* attr_name, std::string attr_value);
        
        void writeMetadata (xercesc::DOMElement* parent_elem);
        void writePalette  (xercesc::DOMElement* parent_elem);
        void writeVoxel    (xercesc::DOMElement* parent_elem);
        void writeObject   (xercesc::DOMElement* parent_elem);
        void writeGrid     (xercesc::DOMElement* parent_elem, Grid* p_grid);
        void writeStructure(xercesc::DOMElement* parent_elem, Structure* p_structure);
        void writeVoxelMap (xercesc::DOMElement* parent_elem, Structure* p_structure);
        void writeColorMap (xercesc::DOMElement* parent_elem, Structure* p_structure);
        void writeColorMapRGB (xercesc::DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapRGBA(xercesc::DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapCMYK(xercesc::DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapGrayScale  (xercesc::DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapGrayScale16(xercesc::DOMElement *cmap_elem, Structure* p_structure);
        
        bool writeXML(const char* filePath);
        
        void str2bin(const unsigned char *str, unsigned char *hex, int len);
        void BytesFromHexString(unsigned char *data, const char *string);
        void deleteNewLine(std::string &targetStr);
        
        xercesc::DOMDocument *doc;
        Fav* fav;
        CompressionMode compression_mode;
    };
    
}

#endif /* FavWriter_hpp */
