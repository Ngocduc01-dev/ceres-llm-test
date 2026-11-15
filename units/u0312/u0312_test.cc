// FILE: u0312_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có nhánh)
TEST(ImplicitSchurComplementNumRows, TC1_P1_ReturnNumColsF) {
  // Ma trận khối: 2 hàng, 3 cột (cột 0 là khối E, cột 1-2 là khối F).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(1, 0));
  bs->cols.push_back(Block(1, 1));
  bs->cols.push_back(Block(1, 2));

  bs->rows.resize(2);
  bs->rows[0].block = Block(1, 0);
  bs->rows[0].cells.push_back(Cell(0, 0));
  bs->rows[0].cells.push_back(Cell(1, 1));

  bs->rows[1].block = Block(1, 1);
  bs->rows[1].cells.push_back(Cell(0, 2));
  bs->rows[1].cells.push_back(Cell(2, 3));

  BlockSparseMatrix A(bs);  // A sở hữu bs

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  const double b[2] = {1.0, 2.0};

  ImplicitSchurComplement isc(options);
  isc.Init(A, nullptr, b);

  // Không kiểm tra kết quả trả về.
  isc.num_rows();
}

}  // namespace internal
}  // namespace ceres
