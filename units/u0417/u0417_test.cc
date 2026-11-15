// FILE: u0417_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"
TEST(Unit_u0417, Destruction) { std::unique_ptr<ceres::internal::SubsetPreconditioner> target; }
