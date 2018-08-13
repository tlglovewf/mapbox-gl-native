#include <mbgl/style/sources/smap_sources/smap_poi_source_impl.hpp>

namespace mbgl {
namespace style {

SMap_Poi_Source::Impl::Impl(std::string id_)
    : Source::Impl(SourceType::Vector, std::move(id_)) {
}

SMap_Poi_Source::Impl::Impl(const Impl& other, Tileset tileset_)
    : Source::Impl(other),
      tileset(std::move(tileset_)) {
}

optional<Tileset> SMap_Poi_Source::Impl::getTileset() const {
    return tileset;
}

optional<std::string> SMap_Poi_Source::Impl::getAttribution() const {
    if (!tileset) {
        return {};
    }
    return tileset->attribution;
}

} // namespace style
} // namespace mbgl
