// FILE: u0331_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

class Unit0331Solver final : public ceres::internal::LinearSolver {
 public:
  Summary Solve(LinearOperator*, const double*, const PerSolveOptions&, double*) override {
    return {};
  }
};

TEST(Unit_u0331, PathP1) {
  Unit0331Solver target;
  EXPECT_TRUE(target.Statistics().empty());
}
