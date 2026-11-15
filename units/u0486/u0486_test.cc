// FILE: u0486_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver_utils.h"
TEST(Unit_u0486, SetSummaryFinalCost) { ceres::Solver::Summary summary; ceres::internal::SetSummaryFinalCost(&summary); }
