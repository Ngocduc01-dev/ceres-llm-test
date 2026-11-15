// FILE: u0780_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"

// P1: START -> 1 -> END
TEST(InitTest, TC1_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  bool a1 = false;
  object.Init(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(InitTest, TC2_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  bool a1 = false;
  object.Init(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(InitTest, TC3_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  bool a1 = false;
  object.Init(a0, a1, nullptr);
}

