// FILE: u0536_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, NullArray) {
  const double* x = nullptr;
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ZeroIterations) {
  const double x[1] = {1.5};
  const int64_t size = 0;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, OneIteration) {
  const double x[1] = {1.5};
  const int64_t size = 1;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, TwoIterations) {
  const double x[2] = {1.5, -2.25};
  const int64_t size = 2;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ThreeIterations) {
  const double x[3] = {1.5, -2.25, 3.75};
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, FourIterations) {
  const double x[4] = {1.5, -2.25, 3.75, 0.5};
  const int64_t size = 4;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, FiveIterations) {
  const double x[5] = {1.5, -2.25, 3.75, 0.5, 7.0};
  const int64_t size = 5;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, NonFiniteAtFirstElement) {
  const double x[3] = {std::numeric_limits<double>::quiet_NaN(), 1.5, 2.5};
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ImpossibleValueAtThirdElement) {
  const double x[3] = {1.5, -2.25, kImpossibleValue};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

}  // namespace internal
}  // namespace ceres
