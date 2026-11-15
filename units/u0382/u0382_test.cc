// FILE: u0382_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cụ thể để tạo object, vì Preconditioner có hàm thuần ảo.
class TestPreconditioner : public Preconditioner {
 public:
  bool Update(const LinearOperator& A, const double* D) override {
    return true;
  }

  void RightMultiplyAndAccumulate(const double* x, double* y) const override {
    for (int i = 0; i < 3; ++i) {
      y[i] += x[i];
    }
  }

  int num_rows() const override { return 3; }
};

}  // namespace

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(PreconditionerLeftMultiplyAndAccumulate, P1_SingleStraightPath) {
  TestPreconditioner obj;
  const double x[3] = {1.5, -2.0, 0.5};
  double y[3] = {0.0, 1.0, -1.0};
  obj.LeftMultiplyAndAccumulate(x, y);
}

}  // namespace internal
}  // namespace ceres
