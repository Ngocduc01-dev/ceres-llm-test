**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), chỉ có node 1 (khởi tạo các thành viên mặc định). CFG khớp với mã nguồn `= default`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (constructor mặc định không tham số) | Không có |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; coi như phủ toàn bộ, 100% với path P1 đi qua node 1).

**D. File test**

```cpp
// FILE: u0329_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LinearLeastSquaresProblemCtor, DefaultConstruct) {
  ceres::internal::LinearLeastSquaresProblem problem;
  (void)problem;
}
```