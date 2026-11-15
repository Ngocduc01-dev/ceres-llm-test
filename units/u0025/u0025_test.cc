// FILE: u0025_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

#include <utility>

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm rỗng, không có điểm rẽ nhánh)
TEST(Take1stOrderPartsApplyEmpty, P1_EmptyBodyNoBranch) {
  Take1stOrderParts<std::integer_sequence<int>, 0, 0> obj;

  double outputs[2] = {1.0, 2.0};
  double jac_data[2] = {0.5, 0.25};
  double* jacobians[1] = {jac_data};

  obj.Apply(3, outputs, jacobians);
}

}  // namespace internal
}  // namespace ceres
