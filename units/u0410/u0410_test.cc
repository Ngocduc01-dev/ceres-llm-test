// FILE: u0410_test.cc
#include "gtest/gtest.h"
#include "ceres/scratch_evaluate_preparer.h"
TEST(Unit_u0410, Init) { ceres::internal::ScratchEvaluatePreparer target; target.Init(1); }
