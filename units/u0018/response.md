**A. Test paths**

CFG của unit:
- START → node 1 (`Evaluate(r, c, f, nullptr, nullptr);`) → END
- Không có điểm rẽ nhánh (không có `if`, `for`, `while`, `switch` hay `?:`), nên tổng số nhánh là 0.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Lưới 2×2 (4 phần tử); `r` ∈ [0, 1], `c` ∈ [0, 1]; `f` trỏ tới mảng 1 phần tử | data = {1, 2, 3, 4}, r = 0.4, c = 0.7 (chọn cố định) |

**C. Nhánh không test**

Không có. Hàm không chứa điểm rẽ nhánh nào.
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; test P1 chạy hết mọi câu lệnh của hàm).

**D. File test**

```cpp
// FILE: u0018_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BiCubicInterpolatorEvaluate, TC1_P1_SingleStatement) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double, 1> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double, 1>> interpolator(grid);

  const double r = 0.4;
  const double c = 0.7;
  double f[1] = {0.0};

  interpolator.Evaluate(r, c, f);
}
```