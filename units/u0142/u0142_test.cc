// FILE: u0142_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetFpclassifyTest, SinglePath) {
  Jet<double, 12> f;
  f.a = 3.5;
  (void)fpclassify(f);
}

}  // namespace internal
}  // namespace ceres
