**A. Test paths**

Unit không có điểm rẽ nhánh nào (tổng số nhánh = 0). CFG khớp với mã nguồn, nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng double 3 phần tử, mỗi phần tử trong [-5, 5]. `y`: mảng double 3 phần tử, mỗi phần tử trong [-5, 5]. Không có điều kiện đường đi ràng buộc thêm. | `x = {1.5, -2.0, 0.5}`, `y = {0.0, 1.0, -1.0}` |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, nên coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
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
```