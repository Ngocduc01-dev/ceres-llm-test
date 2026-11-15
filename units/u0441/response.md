**A. Test paths**

Chỉ có 1 điểm rẽ nhánh (node 2), nên tổng số nhánh là 2. Hàm không có vòng lặp và không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng (`dfdc != nullptr`) |
| P2 | START → 1 → 2 → END | node 2: sai (`dfdc == nullptr`) |

**B. Bộ test case**

Lưới dùng là `Grid2D<double>` kích thước 2×2 (4 phần tử). `GetValue` tự kẹp chỉ số về biên lưới, nên mọi (r, c) đều hợp lệ.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | r ∈ [0, 2), c ∈ [0, 2), `dfdc` ≠ nullptr | r = 0.6, c = 1.3, `dfdc` trỏ tới biến double |
| TC2 | P2 | r ∈ [0, 2), c ∈ [0, 2), `dfdc` = nullptr | r = 1.4, c = 0.7, `dfdc` = nullptr |

Dữ liệu lưới cố định: `{1.0, 2.0, 3.0, 4.0}`. Không dùng số ngẫu nhiên nên kết quả mỗi lần chạy giống nhau.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. `CHECK` không nằm trong hàm này.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0441_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(BiCubicInterpolatorEvaluate, DfdcNotNull) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double>> interpolator(grid);

  double f = 0.0;
  double dfdr = 0.0;
  double dfdc = 0.0;
  interpolator.Evaluate(0.6, 1.3, &f, &dfdr, &dfdc);
}

// Path P2: START -> 1 -> 2 (sai) -> END
TEST(BiCubicInterpolatorEvaluate, DfdcNull) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid2D<double> grid(data, 0, 2, 0, 2);
  ceres::BiCubicInterpolator<ceres::Grid2D<double>> interpolator(grid);

  double f = 0.0;
  double dfdr = 0.0;
  interpolator.Evaluate(1.4, 0.7, &f, &dfdr, nullptr);
}
```