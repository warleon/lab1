#pragma once

#include "SpatialBase.h"

#include <list>
#include <limits>

namespace utec {
namespace spatial {

/**
 * BasicSpatial implementation
 */
template <typename Point>
class BasicSpatial : public SpatialBase<Point> {
 private:
  std::list<Point> points;
 public:
  BasicSpatial() {};
  void insert(const Point& new_point) override {
    points.push_back(new_point);
  }

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override {
    distance_t min= std::numeric_limits<distance_t>::max();
    distance_t current=min;
    Point sol;
    for(auto p=points.begin();p!=points.end();p++){
      current= reference.distance(*p);
      if(current<min){
        sol=*p;
        min=current;
      }
    }
    return sol;
  }
};

}  // namespace spatial
}  // namespace utec
