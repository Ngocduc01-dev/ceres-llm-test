// FILE: u0539_test.cc
#include "ceres/is_close.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: node 2: đúng, node 4: đúng, node 7: đúng
TEST(IsCloseTest, NullErrorPointersAndOneInputIsZero) {
  const double x = 0.0;
  const double y = 3.7;
  const double relative_precision = 1e-3;
  bool result = IsClose(x, y, relative_precision, nullptr, nullptr);
  (void)result;
}

// Path P2: node 2: sai, node 4: sai, node 7: sai
TEST(IsCloseTest, NonNullErrorPointersAndNonZeroInputs) {
  const double x = 5.2;
  const double y = 8.4;
  const double relative_precision = 1e-3;
  double relative_error = 0.0;
  double absolute_error = 0.0;
  bool result =
      IsClose(x, y, relative_precision, &relative_error, &absolute_error);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
