// FILE: u1246_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1246, TC1_CallsTarget) {
  ceres::internal::ImplicitSchurComplement object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
