**A. Test paths**

Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_rows` là số nguyên từ 1 đến 5 (không có điều kiện ràng buộc, chọn khoảng nhỏ) | `num_rows = 3` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều được chạy qua bởi TC1, tức đạt C1 = 100%).

**D. File test**

```cpp
// FILE: u0386_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IdentityPreconditionerNumRowsTest, TC1_ReturnNumRows) {
  IdentityPreconditioner preconditioner(3);
  preconditioner.num_rows();
}

}  // namespace internal
}  // namespace ceres
```