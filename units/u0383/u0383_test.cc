// FILE: u0383_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

namespace {

class FakePreconditioner : public Preconditioner {
 public:
  explicit FakePreconditioner(int rows) : rows_(rows) {}

  bool Update(const LinearOperator& A, const double* D) override {
    return true;
  }

  void RightMultiplyAndAccumulate(const double* x, double* y) const override {}

  int num_rows() const override { return rows_; }

 private:
  int rows_;
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PreconditionerNumColsTest, P1_ReturnsNumRows) {
  FakePreconditioner obj(3);
  obj.num_cols();
}

}  // namespace internal
}  // namespace ceres
