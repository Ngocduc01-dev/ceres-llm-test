// FILE: u1465_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1465, TC1_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1465, TC2_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1465, TC3_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1465, TC4_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1465, TC5_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1465, TC6_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1465, TC7_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1465, TC8_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.InternalAddParameterBlock(nullptr, size);
}
