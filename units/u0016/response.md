**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Grid: mảng 5 phần tử, chỉ số 0..4. `x` thuộc [1, 2) nên n = 1 và các chỉ số 0, 1, 2, 3 đều nằm trong grid. | `data = {0.5, 1.5, 2.5, 3.5, 4.5}`, `x = 1.37` (giá trị cố định, không dùng sinh số ngẫu nhiên). |

**C. Nhánh không test**

Không có nhánh nào, vì hàm không có điểm rẽ nhánh và cũng không có vòng lặp hay `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, nên mọi nhánh đều được phủ). Test duy nhất đi qua toàn bộ node 1.

**D. File test**

```cpp
// FILE: u0016_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CubicInterpolatorEvaluate, TC1_P1_SinglePath) {
  const double data[5] = {0.5, 1.5, 2.5, 3.5, 4.5};
  ceres::Grid1D<double> grid(data, 0, 5);
  ceres::CubicInterpolator<ceres::Grid1D<double>> interpolator(grid);

  const double x = 1.37;
  double f = 0.0;
  double dfdx = 0.0;
  interpolator.Evaluate(x, &f, &dfdx);
}
```