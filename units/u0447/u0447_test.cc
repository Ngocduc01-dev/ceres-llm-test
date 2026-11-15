// FILE: u0447_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> 3 -> END (node 1: đúng)
TEST(Take1stOrderPartsApplyTest, JacobianNonNullTakesPart) {
  using JetT = ceres::Jet<double, 4>;
  Take1stOrderParts<std::integer_sequence<int, 2, 2>> obj;

  const int num_outputs = 2;
  JetT output[2];
  output[0].v[0] = 1.0;
  output[0].v[1] = 2.0;
  output[1].v[0] = 3.0;
  output[1].v[1] = 4.0;

  double jacobian0[4] = {0.0, 0.0, 0.0, 0.0};
  double* jacobians[2] = {jacobian0, nullptr};

  obj.Apply(num_outputs, output, jacobians);
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(Take1stOrderPartsApplyTest, JacobianNullSkipsPart) {
  using JetT = ceres::Jet<double, 4>;
  Take1stOrderParts<std::integer_sequence<int, 2, 2>> obj;

  const int num_outputs = 1;
  JetT output[1];
  output[0].v[0] = 1.0;
  output[0].v[1] = 2.0;

  double* jacobians[2] = {nullptr, nullptr};

  obj.Apply(num_outputs, output, jacobians);
}

}  // namespace internal
}  // namespace ceres
