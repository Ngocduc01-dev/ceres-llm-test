// FILE: u1119_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng, node 3: sai (0 lần), node 7: sai (0 lần), node 13: đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, ZeroRows) {
  DynamicCompressedRowSparseMatrix m(0, 3, 0);
  m.Finalize(2);
}

// P2: node 3: đúng x1 rồi sai, node 7: đúng x1 rồi sai, node 9: đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, OneRowWithEntry) {
  DynamicCompressedRowSparseMatrix m(1, 3, 1);
  m.InsertEntry(0, 1, 1.5);
  m.Finalize(0);
}

// P3: node 3, 7: đúng x2 rồi sai; node 9: sai (hàng 0), đúng (hàng 1)
TEST(DynamicCompressedRowSparseMatrixFinalize, TwoRowsFirstEmpty) {
  DynamicCompressedRowSparseMatrix m(2, 4, 2);
  m.InsertEntry(1, 0, 2.0);
  m.InsertEntry(1, 3, 3.0);
  m.Finalize(3);
}

// P4: node 3, 7: đúng x3 rồi sai; node 9: đúng, sai, đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, ThreeRowsMiddleEmpty) {
  DynamicCompressedRowSparseMatrix m(3, 4, 2);
  m.InsertEntry(0, 2, 1.0);
  m.InsertEntry(2, 1, 4.0);
  m.Finalize(1);
}

// P5: node 3, 7: đúng x4 (n-1) rồi sai; node 9: đúng, sai, đúng, đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, FourRowsOneEmpty) {
  DynamicCompressedRowSparseMatrix m(4, 5, 3);
  m.InsertEntry(0, 0, 1.0);
  m.InsertEntry(2, 4, 2.0);
  m.InsertEntry(3, 1, 3.0);
  m.Finalize(5);
}

// P6: node 3, 7: đúng x5 (n) rồi sai; node 9: đúng ở cả 5 hàng
TEST(DynamicCompressedRowSparseMatrixFinalize, FiveRowsAllNonEmpty) {
  DynamicCompressedRowSparseMatrix m(5, 5, 5);
  for (int i = 0; i < 5; ++i) {
    m.InsertEntry(i, i, static_cast<double>(i + 1));
  }
  m.Finalize(4);
}

}  // namespace internal
}  // namespace ceres
