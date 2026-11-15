// FILE: u0480_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
TEST(Unit_u0480, UpperBound) { double state[1]={}; ceres::internal::ParameterBlock target(state,1,0); target.UpperBound(0); }
