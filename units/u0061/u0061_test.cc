// FILE: u0061_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/parameter_dims.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(ParameterDimsGetUnpackedParameters, TC1_P1_StartToEnd) {
  ParameterDims<false, 2, 2> obj;
  double values[4] = {0.37, -2.5, 4.1, 7.8};
  auto result = obj.GetUnpackedParameters(values);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
