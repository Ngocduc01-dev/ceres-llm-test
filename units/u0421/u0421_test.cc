// FILE: u0421_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"
TEST(Unit_u0421, Free) { ceres::internal::SuiteSparse target; target.Free(nullptr); }
