// FILE: u0239_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellDefaultConstructor, TC1_DefaultConstruct) {
  Cell cell;
  (void)cell;
}

}  // namespace internal
}  // namespace ceres
