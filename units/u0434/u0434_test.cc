// FILE: u0434_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có nhánh)
TEST(VisibilityBasedPreconditionerDestructorTest, P1_StartToEnd) {
  // 3 block cột kích thước 2: block 0 là điểm (e-block), block 1 và 2 là camera.
  CompressedRowBlockStructure bs;
  bs.cols.resize(3);
  for (int i = 0; i < 3; ++i) {
    bs.cols[i].size = 2;
    bs.cols[i].position = 2 * i;
  }

  // 1 row block gồm 3 cell, mỗi cell ứng với một block cột.
  bs.rows.resize(1);
  bs.rows[0].block.size = 2;
  bs.rows[0].block.position = 0;
  bs.rows[0].cells.resize(3);
  for (int i = 0; i < 3; ++i) {
    bs.rows[0].cells[i].block_id = i;
    bs.rows[0].cells[i].position = 4 * i;
  }

  ContextImpl context;
  Preconditioner::Options options;
  options.type = CLUSTER_JACOBI;
  options.elimination_groups.push_back(1);
  options.elimination_groups.push_back(2);
  options.context = &context;

  // Object ra khỏi phạm vi ở cuối khối này -> destructor được gọi đúng một lần.
  {
    VisibilityBasedPreconditioner preconditioner(bs, options);
  }
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
