**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào. Chỉ tạo object của class con `FakeSparseCholesky` (kế thừa `SparseCholesky`) rồi huỷ nó, thông qua con trỏ lớp cha để destructor `~SparseCholesky()` được gọi | Không có |

**C. Nhánh không test**

Không có nhánh nào (hàm có 0 điểm rẽ nhánh, 0 nhánh). Không có vòng lặp và không có `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường START → END được chạy qua, nên coi là 100%).

**D. File test**

```cpp
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
```