// FILE: u0382_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0382, PathP1) { ceres::internal::IdentityPreconditioner target(1); double x[1]={0}, y[1]={0}; target.LeftMultiplyAndAccumulate(x,y); }
