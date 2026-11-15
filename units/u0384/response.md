**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1 (khởi tạo lớp cơ sở `Preconditioner()` và thành viên `num_rows_`) chạy tuần tự |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_rows` là `int` bất kỳ, không có điều kiện ràng buộc; chọn trong khoảng 1 đến 5 | 3 (seed cố định = 0; chọn trong khoảng 1–5) |

**C. Nhánh không test**

Không có. Tổng số nhánh = 2 × 0 = 0, nên không có nhánh nào bị bỏ sót. Mã nguồn khớp với CFG (không có `CHECK`, không có vòng lặp).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của unit đều được chạy qua bởi TC1, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0384_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IdentityPreconditionerConstructorTest, TC1_P1_ConstructWithNumRows) {
  const int num_rows = 3;  // giá trị chọn trong khoảng [1, 5]
  IdentityPreconditioner preconditioner(num_rows);
  (void)preconditioner;
}

}  // namespace internal
}  // namespace ceres
```