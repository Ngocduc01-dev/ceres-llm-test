// FILE: u0774_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END
TEST(InitTest, TC1_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  int a0 = 0;
  b a1{};
  object.Init(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(InitTest, TC2_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  int a0 = 0;
  b a1{};
  object.Init(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(InitTest, TC3_CallsTarget) {
  SchurEliminatorForOneFBlock object{};
  int a0 = 0;
  b a1{};
  object.Init(a0, a1, nullptr);
}

