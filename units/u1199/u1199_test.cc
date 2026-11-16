// FILE: u1199_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng, node 2: sai (0 hàng)
TEST(BlockSparseMatrixToTriplet, NoRows) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P2: node 2: đúng rồi sai, node 4: sai (hàng không có cell)
TEST(BlockSparseMatrixToTriplet, OneRowNoCells) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  bs->rows.emplace_back();
  bs->rows[0].block.size = 1;
  bs->rows[0].block.position = 0;
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P3: node 2, 4, 6, 8: đúng rồi sai (mỗi vòng lặp 1 lần)
TEST(BlockSparseMatrixToTriplet, OneRowOneCell1x1) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  bs->rows.emplace_back();
  bs->rows[0].block.size = 1;
  bs->rows[0].block.position = 0;
  bs->rows[0].cells.emplace_back(0, 0);
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P4: node 2, 4, 6, 8: đúng rồi sai (mỗi vòng lặp 2 lần)
TEST(BlockSparseMatrixToTriplet, TwoRowsMultipleCells) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 2;
  bs->cols[0].position = 0;
  bs->cols.emplace_back();
  bs->cols[1].size = 1;
  bs->cols[1].position = 2;

  bs->rows.emplace_back();
  bs->rows[0].block.size = 2;
  bs->rows[0].block.position = 0;
  bs->rows[0].cells.emplace_back(0, 0);  // 2x2 = 4 giá trị
  bs->rows[0].cells.emplace_back(1, 4);  // 2x1 = 2 giá trị

  bs->rows.emplace_back();
  bs->rows[1].block.size = 1;
  bs->rows[1].block.position = 2;
  bs->rows[1].cells.emplace_back(1, 6);  // 1x1 = 1 giá trị

  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

}  // namespace internal
}  // namespace ceres
