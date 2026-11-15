// FILE: u0537_test.cc
#include <cstdint>
#include <limits>

#include "ceres/array_utils.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng -> node 2 -> END
TEST(FindInvalidValueTest, TC1_NullPointer) {
  FindInvalidValue(3, nullptr);
}

// P2: node 1: sai, node 4: sai (0 lần lặp)
TEST(FindInvalidValueTest, TC2_ZeroIterations) {
  const double x[] = {7.0};
  FindInvalidValue(0, x);
}

// P3 (k=1): node 1: sai, node 4: đúng 1 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC3_OneIteration) {
  const double x[] = {2.5};
  FindInvalidValue(1, x);
}

// P3 (k=2): node 1: sai, node 4: đúng 2 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC4_TwoIterations) {
  const double x[] = {-3.0, 4.5};
  FindInvalidValue(2, x);
}

// P3 (k=3): node 1: sai, node 4: đúng 3 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC5_MiddleIterations) {
  const double x[] = {1.5, -6.0, 8.0};
  FindInvalidValue(3, x);
}

// P3 (k=4): node 1: sai, node 4: đúng 4 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC6_NMinusOneIterations) {
  const double x[] = {0.5, -1.0, 9.0, -7.5};
  FindInvalidValue(4, x);
}

// P3 (k=5): node 1: sai, node 4: đúng 5 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC7_NIterations) {
  const double x[] = {3.0, -2.0, 6.5, -4.0, 1.0};
  FindInvalidValue(5, x);
}

// P4: node 1: sai, node 4: đúng, node 5: đúng (NaN ở phần tử đầu)
TEST(FindInvalidValueTest, TC8_NaNAtFirstElement) {
  const double x[] = {std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0};
  FindInvalidValue(3, x);
}

// P5: node 1: sai, node 4: đúng, node 5: sai, sai, đúng (vô cực ở index 2)
TEST(FindInvalidValueTest, TC9_InfinityAtThirdElement) {
  const double x[] = {1.0, -2.0, std::numeric_limits<double>::infinity(), 5.0};
  FindInvalidValue(4, x);
}

// P6: node 1: sai, node 4: đúng, node 5: đúng ở lần 5 (x[i] == 1e302, tức kImpossibleValue)
TEST(FindInvalidValueTest, TC10_ImpossibleValueAtLastElement) {
  const double x[] = {1.0, 2.0, -3.0, 4.0, 1e302};
  FindInvalidValue(5, x);
}

}  // namespace internal
}  // namespace ceres
