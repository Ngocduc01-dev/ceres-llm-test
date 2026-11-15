// FILE: u0502_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {

// P1: node 1: sai (x == nullptr)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC1_NullPointer) {
  const int64_t size = 3;
  InvalidateArray(size, nullptr);
}

// P2: node 1: đúng, node 3: sai ngay (0 lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC2_ZeroIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 0;
  InvalidateArray(size, x);
}

// P3: node 1: đúng, node 3: đúng 1 lần rồi sai (1 lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC3_OneIteration) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 1;
  InvalidateArray(size, x);
}

// P4: node 1: đúng, node 3: đúng 2 lần rồi sai (2 lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC4_TwoIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 2;
  InvalidateArray(size, x);
}

// P5: node 1: đúng, node 3: đúng 3 lần rồi sai (số lần lặp ở giữa)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC5_MiddleIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 3;
  InvalidateArray(size, x);
}

// P6: node 1: đúng, node 3: đúng 4 lần rồi sai (n-1 lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC6_NMinusOneIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 4;
  InvalidateArray(size, x);
}

// P7: node 1: đúng, node 3: đúng 5 lần rồi sai (n lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(InvalidateArrayTest, TC7_NIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 5;
  InvalidateArray(size, x);
}

}  // namespace internal
}  // namespace ceres
