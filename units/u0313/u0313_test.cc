// FILE: u0313_test.cc
#include <memory>
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ImplicitSchurComplementNumColsTest, P1_ReturnNumColsF) {
  // Ma trận khối: 1 hàng khối (cỡ 2), khối E (cột 0, cỡ 2), khối F (cột 2, cỡ 2).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(2, 0));  // khối E
  bs->cols.push_back(Block(2, 2));  // khối F

  bs->rows.resize(1);
  bs->rows[0].block = Block(2, 0);
  bs->rows[0].cells.push_back(Cell(0, 0));  // cell E, offset 0
  bs->rows[0].cells.push_back(Cell(1, 4));  // cell F, offset 4

  BlockSparseMatrix A(bs);  // A nhận quyền sở hữu bs

  // Giá trị cố định nhờ seed 42, nằm trong [1, 5].
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(1.0, 5.0);
  double* values = A.mutable_values();
  for (int i = 0; i < A.num_nonzeros(); ++i) {
    values[i] = dist(gen);
  }

  std::vector<double> D(A.num_cols(), 1.0);
  std::vector<double> b(A.num_rows(), 1.0);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);  // 1 khối E

  ImplicitSchurComplement isc(options);
  isc.Init(A, D.data(), b.data());

  // Gọi unit một lần, không kiểm tra kết quả.
  isc.num_cols();
}

}  // namespace internal
}  // namespace ceres
