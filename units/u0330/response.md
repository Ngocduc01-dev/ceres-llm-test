**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (không có nhánh nào để phủ) |

Ghi chú: CFG khớp với mã nguồn (`= default`, không có câu lệnh nào).

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào. Destructor được gọi khi object của class con (kế thừa `LinearOperator`) ra khỏi phạm vi | Không có (không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào (hàm có 0 điểm rẽ nhánh).
`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi P1 duy nhất START → END được chạy qua, dự kiến chưa chạy thật).

**D. File test**

```cpp
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
```