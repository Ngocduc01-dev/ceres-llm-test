// FILE: u0013_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

namespace {

// Lớp con cụ thể để tạo được object của ceres::CostFunction
class TestCostFunction : public ceres::CostFunction {
 public:
  explicit TestCostFunction(int num_residuals) {
    set_num_residuals(num_residuals);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CostFunctionNumResidualsTest, P1_ReturnNumResiduals) {
  TestCostFunction cost_function(3);  // giá trị cố định trong khoảng 1..5
  cost_function.num_residuals();      // không kiểm tra kết quả trả về
}
