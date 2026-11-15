// FILE: u1136_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1136, TC1_CallsTarget) {
  int thread_id{};
  Matrix inverse_ete{};
  BufferLayoutType buffer_layout{};
  ceres::internal::SchurEliminator object{};
  object.ChunkOuterProduct(thread_id, nullptr, inverse_ete, nullptr, buffer_layout, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1136, TC2_CallsTarget) {
  int thread_id{};
  Matrix inverse_ete{};
  BufferLayoutType buffer_layout{};
  ceres::internal::SchurEliminator object{};
  object.ChunkOuterProduct(thread_id, nullptr, inverse_ete, nullptr, buffer_layout, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1136, TC3_CallsTarget) {
  int thread_id{};
  Matrix inverse_ete{};
  BufferLayoutType buffer_layout{};
  ceres::internal::SchurEliminator object{};
  object.ChunkOuterProduct(thread_id, nullptr, inverse_ete, nullptr, buffer_layout, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1136, TC4_CallsTarget) {
  int thread_id{};
  Matrix inverse_ete{};
  BufferLayoutType buffer_layout{};
  ceres::internal::SchurEliminator object{};
  object.ChunkOuterProduct(thread_id, nullptr, inverse_ete, nullptr, buffer_layout, nullptr);
}
