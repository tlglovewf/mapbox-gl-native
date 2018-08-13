//
//  smap_poi_source.hpp
//  mbgl-core
//
//  Created by TuLigen on 2018/8/9.
//
#pragma once

#include <mbgl/style/source.hpp>
#include <mbgl/util/tileset.hpp>
#include <mbgl/util/variant.hpp>


namespace mbgl {
    
 class AsyncRequest;
    
    namespace style {
        
        /*
         *  smap  poi source
         */
        class SMap_Poi_Source : public Source {
        public:
            SMap_Poi_Source(std::string id, variant<std::string, Tileset> urlOrTileset);
            ~SMap_Poi_Source() final;
            
            const variant<std::string, Tileset>& getURLOrTileset() const;
            optional<std::string> getURL() const;
            
            class Impl;
            const Impl& impl() const;
            
            void loadDescription(FileSource&) final;
            
        private:
            const variant<std::string, Tileset> urlOrTileset;
            std::unique_ptr<AsyncRequest> req;
        };
        
        template <>
        inline bool Source::is<SMap_Poi_Source>() const {
            return getType() == SourceType::SMap_Poi;
        }
    }
}
