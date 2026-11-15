// FILE: u0420_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"
TEST(Unit_u0420, Availability) { ceres::internal::SuiteSparse target; target.IsNestedDissectionAvailable(); }
