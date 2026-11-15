// FILE: u0406_test.cc
#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

// Chunk là struct lồng không public của SchurEliminator; mở quyền truy cập
// chỉ để test, không sửa mã nguồn Ceres.
#define private public
#define protected public
#include "ceres/schur_eliminator.h"
#undef private
#undef protected

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SchurEliminatorChunkTest, ConstructWithStart) {
  const int start = 37;  // chọn cố định trong khoảng [0, 100]
  ceres::internal::SchurEliminator<>::Chunk chunk(start);
  (void)chunk;
}
