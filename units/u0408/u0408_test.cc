// FILE: u0408_test.cc
#include <memory>

#include "gtest/gtest.h"
#include "ceres/schur_jacobi_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(SchurJacobiPreconditionerDestructorTest, P1_StartToEnd) {
  // Cấu trúc khối: 2 khối cột (kích thước 2), 1 hàng khối có 2 cell.
  CompressedRowBlockStructure bs;
  bs.cols.resize(2);
  bs.cols[0].size = 2;
  bs.cols[0].position = 0;
  bs.cols[1].size = 2;
  bs.cols[1].position = 2;

  bs.rows.resize(1);
  bs.rows[0].block.size = 2;
  bs.rows[0].block.position = 0;
  bs.rows[0].cells.push_back(Cell(0, 0));
  bs.rows[0].cells.push_back(Cell(1, 4));

  Preconditioner::Options options;
  options.elimination_groups.push_back(1);
  options.elimination_groups.push_back(1);
  options.num_threads = 1;

  auto preconditioner =
      std::make_unique<SchurJacobiPreconditioner>(bs, options);

  // Gọi destructor đúng một lần; không kiểm tra kết quả.
  preconditioner.reset();
}

}  // namespace internal
}  // namespace ceres
