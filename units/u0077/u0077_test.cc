// FILE: u0077_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetUnaryMinusTest, P1_NegateJet) {
  Jet<double, 10> f;
  f.a = 3.5;
  const double values[10] = {1.5, -2.0, 0.5, 4.0, -1.0,
                             2.5, -3.5, 0.0, 1.0, -0.5};
  for (int i = 0; i < 10; ++i) {
    f.v[i] = values[i];
  }

  Jet<double, 10> g = -f;
  (void)g;
}

}  // namespace internal
}  // namespace ceres
