// FILE: u0380_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cụ thể để tạo được object (Preconditioner có hàm thuần ảo).
class TestPreconditioner : public Preconditioner {
 public:
  bool Update(const LinearOperator& /*A*/, const double* /*D*/) override {
    return true;
  }

  void RightMultiplyAndAccumulate(const double* /*x*/,
                                  double* /*y*/) const override {}

  int num_rows() const override { return 0; }
};

}  // namespace

// Path P1: START -> END
TEST(PreconditionerDestructorTest, DestroyObject) {
  {
    TestPreconditioner obj;
  }  // ~Preconditioner() được gọi khi obj ra khỏi phạm vi
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
