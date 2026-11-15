// FILE: u0479_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
TEST(Unit_u0479, GetState) { double state[2]={1,2}, out[2]={}; ceres::internal::ParameterBlock target(state,2,0); target.GetState(out); }
