// FILE: u0403_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"
#include "ceres/cost_function.h"
#include <vector>
class TestCost_u0403 : public ceres::SizedCostFunction<1,1> { public: bool Evaluate(double const* const*, double*, double**) const override { return true; } };
// Path P1: START -> 1 -> END.
TEST(Unit_u0403, PathP1) { TestCost_u0403 cost; ceres::internal::ResidualBlock target(&cost, nullptr, {}, 0); target.set_index(1); }
