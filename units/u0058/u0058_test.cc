// FILE: u0058_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/jet_traits.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có nhánh rẽ)
TEST(AsScalarJetTest, P1_ReturnsScalarPartOfJet) {
  const Jet<double, 2> value(3.7);
  // Chỉ gọi hàm một lần, không kiểm tra kết quả trả về.
  (void)AsScalar(value);
}

}  // namespace internal
}  // namespace ceres
