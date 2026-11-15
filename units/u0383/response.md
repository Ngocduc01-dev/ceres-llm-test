**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_rows()` của class con trả về số nguyên từ 1 đến 5 (hàm `num_cols()` không có tham số) | 3 (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ sót, và không có `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường đi duy nhất P1 được chạy qua node 1, tức là phủ 100% câu lệnh).

**D. File test**

```cpp
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
```