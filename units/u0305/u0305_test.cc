// FILE: u0305_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

class Unit0305Function final : public ceres::FirstOrderFunction {
 public:
  int NumParameters() const override { return 2; }
  bool Evaluate(const double*, double* cost, double* gradient) const override {
    *cost = 0.0;
    if (gradient != nullptr) { gradient[0] = 0.0; gradient[1] = 0.0; }
    return true;
  }
};

TEST(Unit_u0305, PathP1) {
  ceres::GradientProblem target(new Unit0305Function);
  const double x[2] = {1.0, 2.0};
  const double delta[2] = {0.5, -1.0};
  double result[2] = {};
  EXPECT_TRUE(target.Plus(x, delta, result));
  EXPECT_DOUBLE_EQ(result[0], 1.5);
  EXPECT_DOUBLE_EQ(result[1], 1.0);
}
