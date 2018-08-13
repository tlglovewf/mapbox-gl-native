#pragma once

#include <mbgl/style/sources/smap_sources/smap_poi_source.hpp>
#include <mbgl/style/source_impl.hpp>

namespace mbgl {
namespace style {

class SMap_Poi_Source::Impl : public Source::Impl {
public:
    Impl(std::string id);
    Impl(const Impl&, Tileset);

    optional<Tileset> getTileset() const;

    optional<std::string> getAttribution() const final;

private:
    optional<Tileset> tileset;
};

} // namespace style
} // namespace mbgl
