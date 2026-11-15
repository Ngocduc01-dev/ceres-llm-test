**CFG**

- START → 1 → END
- Node 1: `Evaluate(x, f, nullptr);` (một lời gọi, không rẽ nhánh)
- Số điểm rẽ nhánh = 0, tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Dữ liệu lưới: 5 phần tử. `x` trong [0, 4]. `f` là mảng 1 phần tử | data = {1.0, 3.0, 2.0, 5.0, 4.0}; x = 1.7 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua.
- Các nhánh trong overload 3 tham số `Evaluate(x, f, dfdx)` mà unit này gọi tới thuộc unit khác nên không tính vào đây.
- C2 dự kiến = 0 / 0 (unit không có điểm rẽ nhánh, một test đi hết đường START → END).

**D. File test**

```cpp
// FILE: u0017_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CubicInterpolatorEvaluate, TC1_P1_SingleNode) {
  const double data[5] = {1.0, 3.0, 2.0, 5.0, 4.0};
  ceres::Grid1D<double, 1> grid(data, 0, 5);
  ceres::CubicInterpolator<ceres::Grid1D<double, 1>> interpolator(grid);

  const double x = 1.7;
  double f[1] = {0.0};
  interpolator.Evaluate(x, f);
}
```