// FILE: u0315_test.cc
#include "gtest/gtest.h"
#include "ceres/inner_product_computer.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductTermTest, ConstructorTC1) {
  InnerProductComputer::ProductTerm term(3, 1, 4);
  (void)term;
}

}  // namespace internal
}  // namespace ceres
