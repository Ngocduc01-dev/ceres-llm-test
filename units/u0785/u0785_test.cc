// FILE: u0785_test.cc
#include "gtest/gtest.h"
#include "ceres/detect_structure.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(DetectStructureTest, TC1_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  ceres::internal::DetectStructure(a0, a1, a2, a3, a4);
}

// P2: START -> 1 -> END
TEST(DetectStructureTest, TC2_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  ceres::internal::DetectStructure(a0, a1, a2, a3, a4);
}

// P3: START -> 1 -> END
TEST(DetectStructureTest, TC3_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  int a1 = 0;
  int a2[5] = {};
  int a3[5] = {};
  int a4[5] = {};
  ceres::internal::DetectStructure(a0, a1, a2, a3, a4);
}

