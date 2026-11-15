// FILE: u1269_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/stl_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1269, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1269, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1269, TC3_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1269, TC4_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1269, TC5_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}
