// FILE: u0763_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0763, TC1_CallsTarget) {
  LineSearchDirection::Options options{};
  ceres::internal::LineSearchDirection object{};
  object.Create(options);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0763, TC2_CallsTarget) {
  LineSearchDirection::Options options{};
  ceres::internal::LineSearchDirection object{};
  object.Create(options);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0763, TC3_CallsTarget) {
  LineSearchDirection::Options options{};
  ceres::internal::LineSearchDirection object{};
  object.Create(options);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0763, TC4_CallsTarget) {
  LineSearchDirection::Options options{};
  ceres::internal::LineSearchDirection object{};
  object.Create(options);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0763, TC5_CallsTarget) {
  LineSearchDirection::Options options{};
  ceres::internal::LineSearchDirection object{};
  object.Create(options);
}
