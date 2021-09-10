#include <gtest/gtest.h>

#include <iostream>

#include "Point.h"
#include "Validator.h"
#include "BasicSpatial.hpp"

using namespace utec::spatial;

template <typename T>
T genRandomNumber(T startRange, T endRange) {
  return startRange + (T)rand() / ((T)RAND_MAX / (T)(endRange - startRange));
}

TEST(SimpleTest, basicTest) {
  using data_t = int;
  using point_t = Point<data_t, 2>;

  Validator<point_t> validator;
  BasicSpatial<point_t> instancia;

  const std::size_t num_points = 10000;
  const std::size_t min = 0, max = 1000;

  auto cmp = [](point_t a, point_t b) {
    const int x = 0, y = 1;
    return (a.get(x) < b.get(x)) ||
           ((a.get(x) == b.get(x)) && (a.get(y) < b.get(y)));
  };

  std::set<point_t, decltype(cmp)> points(cmp);

  for (std::size_t I = 0; I < num_points; I++)
    points.insert(point_t(
        {genRandomNumber<int>(min, max), genRandomNumber<int>(min, max)}));

  for (auto& p : points) {
    validator.insert(p);
    instancia.insert(p);
  }

  point_t p({50, 50});

  auto reference_result = validator.nearest_neighbor(p);
  auto result = instancia.nearest_neighbor(p);
  
  EXPECT_EQ(reference_result, result);
}

int main(int argc, char** argv) {
  srand((unsigned)time(0));

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}