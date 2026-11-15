// FILE: u0355_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0355, PathP1) { ceres::internal::BlockUntilFinished target(0); target.Block(); }
