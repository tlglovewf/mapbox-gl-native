//
//  smap_poi_source.cpp
//  mbgl-core
//
//  Created by TuLigen on 2018/8/9.
//

#include <mbgl/style/sources/smap_sources/smap_poi_source.hpp>
#include <mbgl/style/sources/smap_sources/smap_poi_source_impl.hpp>
#include <mbgl/style/source_observer.hpp>
#include <mbgl/style/conversion/json.hpp>
#include <mbgl/style/conversion/tileset.hpp>
#include <mbgl/storage/file_source.hpp>
#include <mbgl/util/mapbox.hpp>
#include <mbgl/util/constants.hpp>

namespace mbgl {
    
    namespace style {
        
        SMap_Poi_Source::SMap_Poi_Source(std::string id, variant<std::string, Tileset> urlOrTileset_)
        : Source(makeMutable<Impl>(std::move(id))),
        urlOrTileset(std::move(urlOrTileset_)) {
        }
        
        SMap_Poi_Source::~SMap_Poi_Source() = default;
        
        const SMap_Poi_Source::Impl& SMap_Poi_Source::impl() const {
            return static_cast<const Impl&>(*baseImpl);
        }
        
        const variant<std::string, Tileset>& SMap_Poi_Source::getURLOrTileset() const {
            return urlOrTileset;
        }
        
        optional<std::string> SMap_Poi_Source::getURL() const {
            if (urlOrTileset.is<Tileset>()) {
                return {};
            }
            
            return urlOrTileset.get<std::string>();
        }
        
        void SMap_Poi_Source::loadDescription(FileSource& fileSource) {
            if (urlOrTileset.is<Tileset>()) {
                baseImpl = makeMutable<Impl>(impl(), urlOrTileset.get<Tileset>());
                loaded = true;
                return;
            }
            
            if (req) {
                return;
            }
            
            const std::string& url = urlOrTileset.get<std::string>();
            
            if(!util::mapbox::isMapboxURL(url))
            {
                printf("http vector_source url : %s\n",url.c_str());
                std::vector<std::string> urls;
                urls.push_back(url);
                Tileset tileset(urls);
                tileset.zoomRange.min = 1;
                tileset.zoomRange.max = 17;
                //        tileset.scheme = mbgl::Tileset::Scheme::TMS;
                baseImpl = makeMutable<Impl>(impl(), tileset);
                
                fileSource.supportsCacheOnlyRequests();
            }
            else
            {
                req = fileSource.request(Resource::source(url), [this, url](Response res) {
                    if (res.error) {
                        observer->onSourceError(*this, std::make_exception_ptr(std::runtime_error(res.error->message)));
                    } else if (res.notModified) {
                        return;
                    } else if (res.noContent) {
                        observer->onSourceError(*this, std::make_exception_ptr(std::runtime_error("unexpectedly empty TileJSON")));
                    } else {
                        conversion::Error error;
                        optional<Tileset> tileset = conversion::convertJSON<Tileset>(*res.data, error);
                        if (!tileset) {
                            observer->onSourceError(*this, std::make_exception_ptr(std::runtime_error(error.message)));
                            return;
                        }
                        
                        util::mapbox::canonicalizeTileset(*tileset, url, getType(), util::tileSize);
                        bool changed = impl().getTileset() != *tileset;
                        
                        baseImpl = makeMutable<Impl>(impl(), *tileset);
                        loaded = true;
                        
                        observer->onSourceLoaded(*this);
                        
                        if (changed) {
                            observer->onSourceChanged(*this);
                        }
                    }
                });
            }
        }
    }
}

