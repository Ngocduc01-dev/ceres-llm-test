// FILE: u0536_test.cc
#include <cmath>
#include <cstdint>
#include <limits>

#include "ceres/array_utils.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: node 1: sai (x == nullptr)
TEST(IsArrayValidTest, NullArray) {
  const double* x = nullptr;
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P2: node 1: đúng, node 3: sai (0 lần lặp)
TEST(IsArrayValidTest, ZeroIterations) {
  const double x[1] = {1.5};
  const int64_t size = 0;
  IsArrayValid(size, x);
}

// Path P3: node 1: đúng, node 3: đúng rồi sai, node 4: sai (1 lần lặp)
TEST(IsArrayValidTest, OneIteration) {
  const double x[1] = {1.5};
  const int64_t size = 1;
  IsArrayValid(size, x);
}

// Path P4: như P3, 2 lần lặp
TEST(IsArrayValidTest, TwoIterations) {
  const double x[2] = {1.5, -2.25};
  const int64_t size = 2;
  IsArrayValid(size, x);
}

// Path P5: như P3, 3 lần lặp (số ở giữa)
TEST(IsArrayValidTest, ThreeIterations) {
  const double x[3] = {1.5, -2.25, 3.75};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P6: như P3, 4 lần lặp (n-1)
TEST(IsArrayValidTest, FourIterations) {
  const double x[4] = {1.5, -2.25, 3.75, 0.5};
  const int64_t size = 4;
  IsArrayValid(size, x);
}

// Path P7: như P3, 5 lần lặp (n)
TEST(IsArrayValidTest, FiveIterations) {
  const double x[5] = {1.5, -2.25, 3.75, 0.5, 7.0};
  const int64_t size = 5;
  IsArrayValid(size, x);
}

// Path P8: node 1: đúng, node 3: đúng, node 4: đúng (!isfinite), return false ở lần lặp 1
TEST(IsArrayValidTest, NonFiniteAtFirstElement) {
  const double x[3] = {std::numeric_limits<double>::quiet_NaN(), 1.5, 2.5};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P9: node 4: sai 2 lần rồi đúng (== kImpossibleValue), return false ở lần lặp 3
TEST(IsArrayValidTest, ImpossibleValueAtThirdElement) {
  const double x[3] = {1.5, -2.25, kImpossibleValue};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

}  // namespace internal
}  // namespace ceres
