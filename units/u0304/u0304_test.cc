// FILE: u0304_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

class Unit0304Function final : public ceres::FirstOrderFunction {
 public:
  int NumParameters() const override { return 2; }
  bool Evaluate(const double*, double* cost, double* gradient) const override {
    *cost = 0.0;
    if (gradient != nullptr) { gradient[0] = 0.0; gradient[1] = 0.0; }
    return true;
  }
};

TEST(Unit_u0304, PathP1) {
  ceres::GradientProblem target(new Unit0304Function);
  EXPECT_EQ(target.NumTangentParameters(), 2);
}
