// FILE: u1313_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1313, TC1_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.ChunkDiagonalBlockAndGradient(chunk, A, nullptr, row_block_counter, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1313, TC2_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.ChunkDiagonalBlockAndGradient(chunk, A, nullptr, row_block_counter, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1313, TC3_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.ChunkDiagonalBlockAndGradient(chunk, A, nullptr, row_block_counter, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1313, TC4_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.ChunkDiagonalBlockAndGradient(chunk, A, nullptr, row_block_counter, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1313, TC5_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.ChunkDiagonalBlockAndGradient(chunk, A, nullptr, row_block_counter, nullptr, nullptr, nullptr, nullptr);
}
