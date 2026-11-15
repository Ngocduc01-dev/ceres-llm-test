// FILE: u0031_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(FixedArrayDataTest, DataReturnsPointerP1) {
  FixedArray<Jet<double, 4>, 37> array(3);
  Jet<double, 4>* p = array.data();
  (void)p;
}

}  // namespace internal
}  // namespace ceres
