// FILE: u0414_test.cc
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cài đặt các hàm thuần ảo để có thể tạo object.
class FakeSparseCholesky : public SparseCholesky {
 public:
  CompressedRowSparseMatrix::StorageType StorageType() const final {
    return CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR;
  }

  LinearSolverTerminationType Factorize(CompressedRowSparseMatrix* lhs,
                                        std::string* message) final {
    return LinearSolverTerminationType::SUCCESS;
  }

  LinearSolverTerminationType Solve(const double* rhs,
                                    double* solution,
                                    std::string* message) final {
    return LinearSolverTerminationType::SUCCESS;
  }
};

}  // namespace

// P1: START -> END (không có điểm rẽ nhánh)
TEST(SparseCholeskyDestructorTest, DestroyObjectThroughBasePointer) {
  std::unique_ptr<SparseCholesky> obj = std::make_unique<FakeSparseCholesky>();
  // Huỷ object: gọi ~SparseCholesky() một lần, không kiểm tra kết quả.
  obj.reset();
}

}  // namespace internal
}  // namespace ceres
