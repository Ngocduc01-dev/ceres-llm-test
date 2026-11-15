// FILE: u0340_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include <vector>
// Path P1: START -> 1 -> END.
TEST(Unit_u0340, PathP1) { ceres::SubsetManifold target(2, std::vector<int>{0}); target.AmbientSize(); }
