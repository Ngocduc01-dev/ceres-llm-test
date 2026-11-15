// FILE: u0330_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

class Unit0330Operator final : public ceres::internal::LinearOperator {
 public:
  ~Unit0330Operator() override = default;
  void RightMultiplyAndAccumulate(const double*, double*) const override {}
  void LeftMultiplyAndAccumulate(const double*, double*) const override {}
  int num_rows() const override { return 0; }
  int num_cols() const override { return 0; }
};

TEST(Unit_u0330, PathP1) {
  { Unit0330Operator target; }
}
