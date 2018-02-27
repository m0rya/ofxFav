//
//  Metadata.hpp
//  FavExample
//
//  Created by m0Rya on 2018/02/14.
//

#ifndef Metadata_hpp
#define Metadata_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "FavSettings.h"

namespace FavLibrary{
    class Metadata{
    public:
        
        Metadata();
        Metadata(std::string identifier_, std::string title_, std::string author_, std::string license_);
        virtual ~Metadata();
        
        std::string getId();
        void setId(std::string identifier_);
        
        std::string getTitle();
        void setTitle(std::string title_);
        
        std::string getAuthor();
        void setAuthor(std::string author_);
        
        std::string getLicense();
        void setLicense(std::string license_);
        
        std::string getNote();
        void setNote(std::string note_);
        
    protected:
        std::string identifier;
        std::string title;
        std::string author;
        std::string license;
        std::string note;
    };
    
    class MetadataObject
    {
    public:
        MetadataObject();
        virtual ~MetadataObject();
        
        std::string getMetadataId();
        void setMetadataId(std::string id_);
        
        std::string getMetadataAuthor();
        void setMetadataAuthor(std::string aughor_);
        
        std::string getMetadataTitle();
        void setMetadataTitle(std::string title_);
        
        std::string getMetadataLicense();
        void setMetadataLicense(std::string license_);
        
        std::string getMetadataNote();
        void setMetadataNote(std::string note_);
        
    private:
        Metadata metadata;
    };
}

#endif /* Metadata_hpp */
