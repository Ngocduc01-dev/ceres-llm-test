// FILE: u0402_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"
#include "ceres/cost_function.h"
#include <vector>
class TestCost_u0402 : public ceres::SizedCostFunction<1,1> { public: bool Evaluate(double const* const*, double*, double**) const override { return true; } };
// Path P1: START -> 1 -> END.
TEST(Unit_u0402, PathP1) { TestCost_u0402 cost; ceres::internal::ResidualBlock target(&cost, nullptr, {}, 0); target.index(); }
