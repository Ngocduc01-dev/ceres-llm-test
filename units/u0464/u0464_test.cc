// FILE: u0464_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, ZeroIterations) {
  int array[1] = {7};
  MapValuesToContiguousRange(0, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, OneIteration) {
  int array[1] = {3};
  MapValuesToContiguousRange(1, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, TwoIterations) {
  int array[2] = {4, -2};
  MapValuesToContiguousRange(2, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, ThreeIterations) {
  int array[3] = {2, 2, -1};
  MapValuesToContiguousRange(3, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, FourIterations) {
  int array[4] = {5, 0, 5, -3};
  MapValuesToContiguousRange(4, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, FiveIterations) {
  int array[5] = {1, -4, 1, 3, -4};
  MapValuesToContiguousRange(5, array);
}

}  // namespace internal
}  // namespace ceres
