// FILE: u0385_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0385, PathP1) { ceres::internal::IdentityPreconditioner target(1); double x[1]={0}, y[1]={0}; target.RightMultiplyAndAccumulate(x,y); }
