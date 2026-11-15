// FILE: u0060_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/parameter_dims.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterDimsGetDimTest, TC1_P1_SingleBlockDimZero) {
  ParameterDims<false, 2> obj;
  int dim = 0;  // khoảng hợp lệ [0, 0]
  (void)obj.GetDim(dim);
}

}  // namespace internal
}  // namespace ceres
