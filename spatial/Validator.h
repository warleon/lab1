#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "SpatialBase.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

namespace utec {
namespace spatial {

typedef bg::model::point<int, 2, bg::cs::cartesian> index_point;
typedef index_point value;

/**
 * Validator implementation
 */
template <typename Point>
class Validator : public SpatialBase<Point> {
 private:
  bgi::rtree<value, bgi::linear<16, 4>> rtree;

 public:
  Validator();
  void insert(const Point& new_point) override;
  Point nearest_neighbor(const Point& reference) override;
};

}  // namespace spatial
}  // namespace utec

#include "Validator.inl"
