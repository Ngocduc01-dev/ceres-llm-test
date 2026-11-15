**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (node 1 chỉ gồm các member initializer chạy tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào (constructor mặc định) | Không có |

**C. Nhánh không test**

Không có nhánh nào, vì hàm có 0 điểm rẽ nhánh và không có vòng lặp hay `CHECK`.

Ghi chú: CFG khớp với mã nguồn. Dòng 83 là `= default`, nên các member initializer là do trình biên dịch sinh ra.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên C2 coi như đạt 100% khi node 1 được chạy qua).

**D. File test**

```cpp
// FILE: u0388_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PreprocessedProblemConstructorTest, DefaultConstructor) {
  ceres::internal::PreprocessedProblem preprocessed_problem;
  (void)preprocessed_problem;
}
```