// FILE: u1136_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END
TEST(ChunkOuterProductTest, TC1_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  Matrix & inverse_ete a2{};
  double a3[5] = {};
  BufferLayoutType & buffer_layout a4{};
  object.ChunkOuterProduct(a0, nullptr, a2, a3, a4, nullptr);
}

// P2: START -> 1 -> END
TEST(ChunkOuterProductTest, TC2_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  Matrix & inverse_ete a2{};
  double a3[5] = {};
  BufferLayoutType & buffer_layout a4{};
  object.ChunkOuterProduct(a0, nullptr, a2, a3, a4, nullptr);
}

// P3: START -> 1 -> END
TEST(ChunkOuterProductTest, TC3_CallsTarget) {
  SchurEliminator object{};
  int a0 = 0;
  Matrix & inverse_ete a2{};
  double a3[5] = {};
  BufferLayoutType & buffer_layout a4{};
  object.ChunkOuterProduct(a0, nullptr, a2, a3, a4, nullptr);
}

