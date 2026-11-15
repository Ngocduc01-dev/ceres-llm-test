// FILE: u0683_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

class TestLinearOperator final : public ceres::internal::LinearOperator {
 public:
  void RightMultiplyAndAccumulate(const double*, double*) const override {}
  void LeftMultiplyAndAccumulate(const double*, double*) const override {}
  int num_rows() const override { return 1; }
  int num_cols() const override { return 1; }
};
// Path P1: START -> 1 -> END.
TEST(Unit_u0683, PathP1) {
  TestLinearOperator target;
  ceres::internal::Vector x = ceres::internal::Vector::Ones(1);
  ceres::internal::Vector y = ceres::internal::Vector::Zero(1);
  target.RightMultiplyAndAccumulate(x, y);
}
