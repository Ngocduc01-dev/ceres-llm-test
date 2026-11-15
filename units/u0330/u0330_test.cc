// FILE: u0330_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con tối thiểu để tạo được object của LinearOperator (lớp có hàm thuần ảo).
class TestLinearOperator : public LinearOperator {
 public:
  void RightMultiplyAndAccumulate(const double* x, double* y) const final {}
  void LeftMultiplyAndAccumulate(const double* x, double* y) const final {}
  int num_rows() const final { return 0; }
  int num_cols() const final { return 0; }
};

}  // namespace

// P1: START -> END (destructor ~LinearOperator() = default, không có nhánh)
TEST(LinearOperatorDestructorTest, TC1_DestroyDerivedObjectThroughBasePointer) {
  LinearOperator* op = new TestLinearOperator();
  delete op;  // gọi ~LinearOperator() qua con trỏ lớp cơ sở (destructor ảo)
}

}  // namespace internal
}  // namespace ceres
