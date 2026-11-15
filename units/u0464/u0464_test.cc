// FILE: u0464_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {

// Path P1: node 2: sai (0 lần lặp)
TEST(MapValuesToContiguousRangeTest, ZeroIterations) {
  int array[1] = {7};
  MapValuesToContiguousRange(0, array);
}

// Path P2: node 2: đúng, sai (1 lần lặp)
TEST(MapValuesToContiguousRangeTest, OneIteration) {
  int array[1] = {3};
  MapValuesToContiguousRange(1, array);
}

// Path P3: node 2: đúng x2, sai (2 lần lặp)
TEST(MapValuesToContiguousRangeTest, TwoIterations) {
  int array[2] = {4, -2};
  MapValuesToContiguousRange(2, array);
}

// Path P4: node 2: đúng x3, sai (3 lần lặp, giá trị giữa)
TEST(MapValuesToContiguousRangeTest, ThreeIterations) {
  int array[3] = {2, 2, -1};
  MapValuesToContiguousRange(3, array);
}

// Path P5: node 2: đúng x4, sai (4 lần lặp, n-1)
TEST(MapValuesToContiguousRangeTest, FourIterations) {
  int array[4] = {5, 0, 5, -3};
  MapValuesToContiguousRange(4, array);
}

// Path P6: node 2: đúng x5, sai (5 lần lặp, n)
TEST(MapValuesToContiguousRangeTest, FiveIterations) {
  int array[5] = {1, -4, 1, 3, -4};
  MapValuesToContiguousRange(5, array);
}

}  // namespace internal
}  // namespace ceres
